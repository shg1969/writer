#include "win_main.h"
#include "win_preview.h"

#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QPlainTextEdit>
#include <QString>
#include <QFileDialog>
#include <QDockWidget>
#include <QApplication>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QColorDialog>


Win_Main::Win_Main(QWidget *parent)
    : QMainWindow(parent)
{
    is_book_changed=0;
    /****************************整体布局****************************/
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
    resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
    move((availableGeometry.width() - width()) / 2,(availableGeometry.height() - height()) / 2);

    /****************************工具栏****************************/
    QToolBar *tb = addToolBar(tr("Format Actions"));
    //字体大小
    auto comboSize = new QComboBox(tb);
    tb->addWidget(new QLabel("字体大小：",tb));
    tb->addWidget(comboSize);
    tb->addSeparator();
    //字体类型
    tb->addWidget(new QLabel("字体类型",tb));
    QFontComboBox* font_select=new QFontComboBox(tb);
    tb->addWidget(font_select);
    connect(font_select,&QFontComboBox::currentFontChanged,this,&Win_Main::change_txt_font);
    //夜间模式
    tb->addSeparator();
    auto checkbox=new QCheckBox("夜间模式",tb);
    tb->addWidget(checkbox);
    connect(checkbox,&QCheckBox::stateChanged,this,&Win_Main::change_theme);
    //字体颜色和背景色
    auto btn_font_color=new QPushButton("字体颜色",tb);
    tb->addWidget(btn_font_color);
    connect(btn_font_color,&QPushButton::clicked,[&](){
        auto c=QColorDialog::getColor();
        edit_txt->current_page()->setTextColor(c);
        edit_txt->set_txt(edit_txt->get_txt());
    });
    auto btn_back_color=new QPushButton("背景颜色",tb);
    tb->addWidget(btn_back_color);
    connect(btn_back_color,&QPushButton::clicked,[&](){
        int r=0,g=0,b=0;
        auto color=QColorDialog::getColor();
        color.getRgb(&r,&g,&b);
        QString str="background-color:rgb("
                +QString::number(r)+","
                +QString::number(g)+","
                +QString::number(b)+")}";
        edit_txt->current_page()->setStyleSheet(str);
    });
    //相关配置
    const QList<int> standardSizes = QFontDatabase::standardSizes();
    foreach (int size, standardSizes)
        comboSize->addItem(QString::number(size));
    comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));
    //信号和槽
    connect(comboSize, QOverload<const QString &>::of(&QComboBox::activated), this, &Win_Main::textSize);

    /****************************菜单栏****************************/
    QMenuBar *menubar=menuBar();
    //菜单
    auto menu_file=menubar->addMenu("文件");
    auto menu_win=menubar->addMenu("窗口");
//    auto menu_edit=menubar->addMenu("编辑");
    auto menu_about=menubar->addMenu("关于");
    //文件
    auto act_create_book=menu_file->addAction("创建书籍");
    auto act_load_book=menu_file->addAction("导入书籍");
    auto act_open_book=menu_file->addAction("打开书籍");
    auto act_save_book=menu_file->addAction("保存书籍");
    auto act_save_book_as=menu_file->addAction("另存书籍");
    auto act_close_book=menu_file->addAction("关闭书籍");
    auto act_delete_book=menu_file->addAction("删除书籍");
    //窗口
    auto act_open_read_dock=menu_win->addAction("阅读摘录");
    auto act_show_directory_dock=menu_win->addAction("目录窗口");
    //编辑

    //关于
    auto act_about_Qt=menu_about->addAction("关于Qt");
    auto act_about_author=menu_about->addAction("关于作者");

    /****************************窗口配置****************************/
    set_window_title(1,book.get_book_name());
    //编辑窗口
    edit_txt=new Win_Edit(&book,this);
    connect(edit_txt,&Win_Edit::book_changed,[&](){set_window_title(1,"");});
    setCentralWidget(edit_txt);
    //浮动窗口
    win_directory=new Win_Directory(&book,this);
    connect(win_directory,&Win_Directory::dir_changed,[&](){set_window_title(1,"");});

    win_record=new Win_Read(this);
    win_record->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    win_directory->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea,win_directory);
    addDockWidget(Qt::RightDockWidgetArea,win_record);

    /****************************信号和槽****************************/
    //创建书籍
    connect(act_create_book,&QAction::triggered,[&](){book.create();});
    connect(&book,&Book::book_created,[&](){
        win_directory->renew_directory(book.get_contents());
        edit_txt->clear();
        set_window_title(1,book.get_book_name());
    });
    //导入书籍
    connect(act_load_book,&QAction::triggered,this,&Win_Main::slot_load_book);
    //打开书籍
    connect(act_open_book,&QAction::triggered,this,&Win_Main::slot_open_book);
    //另存书籍
    connect(act_save_book_as,&QAction::triggered,this,&Win_Main::slot_save_book_as);
    //保存书籍
    connect(act_save_book,&QAction::triggered,this,&Win_Main::slot_save_book);
    //关闭书籍
    connect(act_close_book,&QAction::triggered,this,&Win_Main::slot_close_book);
    //删除书籍
    connect(act_delete_book,&QAction::triggered,this,&Win_Main::slot_delete_book);

    //显示目录窗口
    connect(act_show_directory_dock,&QAction::triggered,[&](){win_directory->show();});
    //显示阅读模式下的浮动窗口
    connect(act_open_read_dock,&QAction::triggered,[&](){win_record->show();});
    //更新当前打开的章节
    connect(win_directory,&Win_Directory::click_on_directory,this,&Win_Main::slot_open_chapter);
    //自动聚焦
    connect(edit_txt,&Win_Edit::txt_selection_changed,win_record,&Win_Read::auto_set_key_focus);



    //关于Qt
    connect(act_about_Qt,&QAction::triggered,[&](){QMessageBox::aboutQt(this);});
    //关于作者
    connect(act_about_author,&QAction::triggered,[&](){QMessageBox::about(this,"作者信息","作者：\t雷\n邮箱：\tshg1969@outlook.com\n");});

    /****************************调试内容****************************/

}

Win_Main::~Win_Main()
{
//    delete win_bookshelf;
}

void Win_Main::clear()
{
    win_directory->clear();
    edit_txt->clear();
    book.clear();
}

void Win_Main::ask_save()
{
    auto res=QMessageBox::question(Q_NULLPTR,"保存确认","确认保存？",QMessageBox::Ok|QMessageBox::Cancel);
    if(res!=QMessageBox::Ok)
        return ;
    else
        slot_save_book();
}

void Win_Main::set_window_title(bool is_changed,QString keep_old)
{
    if(!keep_old.size())
        keep_old=windowTitle();
    int pos=keep_old.lastIndexOf("*");
    if(pos>-1&&pos<keep_old.size())
        keep_old=keep_old.left(pos);

    is_book_changed = is_changed;
    if(is_changed)
        setWindowTitle(keep_old+"*");
    else
        setWindowTitle(keep_old);
}

void Win_Main::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}
//改变光标所在位置的字符或所选字符的格式
void Win_Main::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    //获取光标
    QTextCursor cursor = edit_txt->current_page()->textCursor();
    //如果光标没选中文本
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);//选中“”单词块”（连续的字母）
    //光标选中了文本,改变光标所选字符的格式，设置后续输入字符的格式
    cursor.mergeCharFormat(format);
    edit_txt->current_page()->mergeCurrentCharFormat(format);
    auto a=QString(edit_txt->get_txt());
    edit_txt->set_txt(a);
}

void Win_Main::change_txt_font(const QFont &font)
{
    edit_txt->set_font(font);
    auto s=edit_txt->get_txt();
    edit_txt->set_txt(s);
}

void Win_Main::change_theme(int state)
{
    if(state)
    {
        this->setStyleSheet(this->bright_theme_style_sheet);
    }
    else
    {
        this->setStyleSheet("");
    }
}

void Win_Main::slot_load_book()
{
    clear();
    //读取 txt
    book.init_from_file();
    set_window_title(1,book.get_book_name());
    connect(&book,&Book::ready,win_directory,&Win_Directory::renew_directory);
}

void Win_Main::slot_open_book()
{
    clear();
    book.init_from_book();
    win_directory->renew_directory(book.get_contents());
    set_window_title(0,book.get_book_name());
}
void Win_Main::slot_save_book()
{
    if(!is_book_changed)
    {
        QMessageBox::warning(this,"保存书籍","该书未经更改");
        return;
    }

    //将编辑过的保存到内存
    edit_txt->save_all();
    //将内存的数据保存到文件
    if(book.save())
        set_window_title(0);
}
void Win_Main::slot_save_book_as()
{
    auto book_name=QFileDialog::getSaveFileName(this,"保存新书",BOOK_SHELF_DIR,"TXT files (*.txt)");
    auto txt=book.get_txt();
    QFile f(book_name);
    f.open(QIODevice::WriteOnly);
    f.write(txt.toUtf8());
    f.close();
}
void Win_Main::slot_close_book(void)
{
    QString book_name;
    if(this->is_book_changed)
        ask_save();
    clear();
    set_window_title(1,"temp");
}

void Win_Main::slot_delete_book()
{
    auto res=QMessageBox::question(Q_NULLPTR,"删除确认","确认删除？",QMessageBox::Ok|QMessageBox::Cancel);
    if(res!=QMessageBox::Ok)
        return;
    book.remove();
    clear();
}

void Win_Main::slot_open_chapter(int index)
{
    //打开目标章节
    edit_txt->add_tab(index,book.get_chapter_txt(index));
}

