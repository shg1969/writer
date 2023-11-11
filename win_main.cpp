//#define __TEST

#include "win_main.h"
#include "win_preview.h"
#include "setting.h"
#include<QDebug>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QDebug>
#include<QPlainTextEdit>
#include<QString>
#include<QFileDialog>
#include<QDockWidget>
#include<QApplication>
#include <QMessageBox>
#include <QDesktopWidget>
#include "win_bookshelf.h"

Win_Main::Win_Main(QWidget *parent)
    : QMainWindow(parent)
{
    /****************************窗体界面****************************/
    //整体布局
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
    resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
    move((availableGeometry.width() - width()) / 2,
            (availableGeometry.height() - height()) / 2);
    //菜单栏
    QMenuBar *menubar=new QMenuBar(this);
    setMenuBar(menubar);

    auto file_menu=menubar->addMenu("文件");
    auto win_menu=menubar->addMenu("窗口");
    auto about_menu=menubar->addMenu("关于");

    auto create_book=file_menu->addAction("导入书籍");
    auto open_book=file_menu->addAction("打开书籍");
    auto close_book=file_menu->addAction("关闭书籍");

    auto open_read_dock=win_menu->addAction("阅读摘录");

    auto about_Qt=about_menu->addAction("关于Qt");
    auto about_author=about_menu->addAction("关于作者");

    /****************************窗口配置****************************/
    bookshelf_win=new Win_Bookshelf(Q_NULLPTR);
    preview_win=new Win_Preview(Q_NULLPTR);
    //编辑窗口
    edit_txt=new QPlainTextEdit(this);
    setCentralWidget(edit_txt);

    //浮动窗口
    record_win=new Win_Read(this);
    record_win->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    record_win->hide();
    /****************************信号和槽****************************/
    //新导入书籍
    connect(create_book,&QAction::triggered,this,&Win_Main::load_new_book);
    //新导入书籍
    connect(open_book,&QAction::triggered,this,&Win_Main::open_book);
    //新导入书籍
    connect(close_book,&QAction::triggered,this,&Win_Main::close_book);

    //阅读模式下的浮动窗口
    connect(open_read_dock,&QAction::triggered,[&](){
        record_win->setFloating(1);
        record_win->show();
    });
    connect(edit_txt,&QPlainTextEdit::selectionChanged,[&](){
        emit txt_selection_Changed(edit_txt->textCursor().selectedText());
    });
    connect(this,&Win_Main::txt_selection_Changed,record_win,&Win_Read::auto_set_key_focus);
    //处理预览窗口返回的信息
    connect(preview_win,&Win_Preview::sent_encoding_type,this,&Win_Main::accept_coding_type);
    //关于Qt
    connect(about_Qt,&QAction::triggered,[&](){
        QMessageBox::aboutQt(this);
    });
    //关于作者
    connect(about_author,&QAction::triggered,[&](){
        QMessageBox::about(this,"作者信息",
                           "作者：\t雷\n"
                           "邮箱：\tshg1969@outlook.com\n");
    });

    /****************************调试内容****************************/
#ifdef __TEST
    connect(edit_win,&QPlainTextEdit::textChanged,[&](){
        QByteArray s=QString("你好啊").toUtf8();
        preview_win->preview_conf("遮天",s);
    });
#endif
}

Win_Main::~Win_Main()
{
    delete bookshelf_win;
    delete preview_win;
}

void Win_Main::load_new_book(void)
{
    QString filename= QFileDialog::getOpenFileName(this, "打开文件",setting.get_bookshelf_dir(),"文本文件 (*.txt)");
    QFile file(filename);
    //如果文件打开失败
    if(!file.open(QFile::ReadOnly))
        QMessageBox error(QMessageBox::Warning,"错误","打开文件失败！！！");
    else//文件打开成功
    {
        //读取文件，放到reading_txt，预览，选择编码方式
        preview_win->preview_show(filename,file.readAll());
    }
    auto s=Book::get_bookname_from_path(filename);
    this->setWindowTitle(s);
}
void Win_Main::open_book(void)
{
//    auto s=Book::get_bookname_from_path(filename);
//    this->setWindowTitle(s);
}
void Win_Main::close_book(void)
{

//    this->setWindowTitle("");
}

void Win_Main::accept_coding_type(QString coding)
{
    setting.set("","",coding);
    //重新设置编辑窗口的编码，更新显示文本
    auto s=book.get_book_name();
}
