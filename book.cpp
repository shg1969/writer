#include "book.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include<QDir>
#include<QPair>
#include <QIODevice>
#include <QString>
#include <QFileDialog>
#include <QTextCodec>
#include "win_preview.h"
//#include"setting.h"

/******************构造函数*******************/
Book::Book(QObject *parent):QObject(parent)
{
    if(!QDir(TOP_DIR).exists())
        QDir(TOP_DIR).mkpath(TOP_DIR);
    if(!QDir(BOOK_SHELF_DIR).exists())
        QDir(TOP_DIR).mkpath("./bookshelf");
    if(!QDir(BOOK_DATA_DIR).exists())
        QDir(TOP_DIR).mkpath("./data");
    if(!QDir(BOOK_DATA_DIR).exists())
        QDir(TOP_DIR).mkpath("./data");

    win_create=new Create_new_Book(Q_NULLPTR);
    win_preview=new Win_Preview(Q_NULLPTR);
    this->book_name="temp";
    chapter_num=0;
    //导入书籍
    connect(win_preview,&Win_Preview::sent_encoding_type,this,&Book::receive_encoding);
    connect(win_create,&Create_new_Book::input_finish,this,&Book::receive_new_book_info);
}

Book::~Book()
{
    delete win_create;
    delete win_preview;
}


void Book::create()
{
    win_create->show();
    win_create->exec();
}
void Book::init_from_file()
{
    clear();
    book_dir=QFileDialog::getOpenFileName(Q_NULLPTR,"打开文本文件",TXT_LIB,"TXT files (*.txt)");
    if(!book_dir.size())return;
    book_name=get_book_name_from_path(book_dir);
    chapter_num=0;

    QFile file(book_dir);
    file.open(QIODevice::ReadOnly);
    unicode_txt=file.readAll();
    win_preview->show_win(unicode_txt.toUtf8());
    win_preview->set_showing_book_name(book_name);
    file.close();
}

void Book::init_from_book(QString book)
{
    QString dir=BOOK_SHELF_DIR+book+".conf";
    //录入目录
    if(!book.length())
        dir=QFileDialog::getOpenFileName(Q_NULLPTR,"打开BOOK文件",BOOK_SHELF_DIR,"BOOK files (*.conf)");

    QFile book_conf(dir);
    book_conf.open(QIODevice::ReadOnly);
    QTextStream In(&book_conf);
    //输入书籍目录
    In>>book_dir;
    //输入书名
    In>>book_name;
    //输入章节数
    In>>chapter_num;
    //输入目录
    QString temp,txt;
    for(int i=0;i<chapter_num;i++)
    {
        In>>temp;

        //录入章节正文
        QFile doc(book_dir+QString::number(i)+".txt");
        if(!doc.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(Q_NULLPTR,"读取章节","文件读取失败");
            return ;
        }
        txt=doc.readAll();
        contents.push_back(temp,txt);
        doc.close();
    }
    book_conf.close();
}

bool Book::save()
{
    if(book_name=="temp")
    {
        book_name=QFileDialog::getSaveFileName(Q_NULLPTR,"保存新书",BOOK_SHELF_DIR,"BOOK files (*.conf)");
        if(!book_name.size())return 0;
        book_name=get_book_name_from_path(book_name);
    }
    if(!contents.count())return 0;
    //创建文件夹
    QDir(QString(BOOK_DATA_DIR)).mkdir(book_name);
    book_dir=QString(BOOK_DATA_DIR)+book_name+"/";

    QFile conf_file(BOOK_SHELF_DIR+book_name+".conf");

    if(!conf_file.open(QFile::WriteOnly))return 0;
    QTextStream out(&conf_file);
    //输出书籍目录
    out<<book_dir<<endl;
    //输出书名
    out<<book_name<<endl;
    //输出章节数
    out<<chapter_num<<endl;
    //输出目录
    for(auto i:contents)
    {
        out<<i.getName()<<endl;

        QFile doc(book_dir+QString::number(i.getIndex())+".txt");
        if(!doc.open(QFile::WriteOnly))return 0;
        auto s=i.getDoc().toUtf8();
        doc.write(s);
        doc.close();
    }
    conf_file.close();

    return 1;
}
bool Book::remove()
{
    if(!QFile::remove(BOOK_SHELF_DIR+book_name+".conf"))
    {
//        QMessageBox::about(Q_NULLPTR,"错误","删除conf文件出错");
//        return 0;
    }
    for(auto i:QDir(book_dir).entryList())
    {
//        if(!QFile::remove(i))
//        {
//            QMessageBox::about(Q_NULLPTR,"错误","删除文件出错");
//            return 0;
//        }
    }
    if(!QDir(book_dir).rmpath(book_dir))
    {
//        QMessageBox::about(Q_NULLPTR,"错误","删除data文件出错");
//        return 0;
    }
    return 1;
}

void Book::clear()
{
    set_book_name("temp");
    chapter_num=0;
    contents.clear();
    description.clear();
    this->encoding.clear();
    this->unicode_txt.clear();
}

//***************章节操作***************
void Book::add_chapter(QString chapter_name,QString chapter_content)
{
    //增加目录
    contents.push_back(chapter_name,chapter_content);
    //添加章节
    chapter_num++;//章节数加一
}
void Book::delete_chapter(int index)
{
    contents.remove(index);
}
void Book::edit_chapter_name(int index,QString New)
{
    for(auto&i:contents)
    {
        if(i.getIndex()==index)
        {
            i.setName(New);
            return;
        }
    }
}
void Book::save_chapter(int chapter_index,QString txt)
{
    for(auto&i:contents)
    {
        if(i.getIndex()==chapter_index)
        {
            i.setDoc(txt);
            return;
        }
    }
}

//获取全文
QString Book::get_txt(void)
{
    QString txt;
    for(auto i:contents)
    {
        txt+="\n\n\n"+i.getName();
        txt+=i.getDoc()+"\n";
    }
    return txt;
}
//书名
QString Book::get_book_name()
{
    return book_name;
}
void Book::set_book_name(QString new_name)
{
    book_name=new_name;
}
//章名及内容
Content Book::get_contents() const
{
    return contents;
}

QString Book::get_chapter_txt(int index)
{
    return contents[index].getDoc();
}

//简介
QString Book::get_description() const
{
    return description;
}
void Book::set_description(const QString &value)
{
    description = value;
}
//章节数
int Book::get_chapter_num() const
{
    return chapter_num;
}

QString Book::get_book_name_from_path(QString path)
{
    QString res;
    res=path.left(path.indexOf("."));
    res=res.right(res.size()-1-res.lastIndexOf("/"));
    return res;
}

void Book::receive_encoding(QString encoding)
{
    encoding=win_preview->get_encoding_type();
    auto codec = QTextCodec::codecForName(encoding.toUtf8());
    unicode_txt= codec->toUnicode(unicode_txt.toUtf8());//如果本来就是UTF-8会导致程序崩溃

    QString para="",doc="";//段落，全章
    QString last_chapter_name="第0章";//分章录入
    const int max_length=QString("第九千九百九十九章").length()*5;
    for(int i=0;i<unicode_txt.length();i++)
    {
        //读取一段
        if(unicode_txt[i]!='\n')
        {
            para+=unicode_txt[i];
        }
        else//段落末尾，unicode_txt[i]=='\n'
        {
            //如果这一段是章节名称
            if(para.size()<max_length&&para[0]=="第"&&(para.contains("章")||para.contains("节"))&&para.indexOf("章")<8)
            {
                add_chapter(last_chapter_name,doc);
                doc.clear();
                last_chapter_name=para;
                para.clear();
            }
            else//不是章节名，只是普通段
            {
                doc+=para+'\n';
                //将下一段开头的空格过滤
                do{
                    i++;
                }
                while(unicode_txt[i]==' ');
                i--;
                para.clear();
            }
        }
    }
    add_chapter(last_chapter_name,doc);

    save();
    init_from_book(book_name);
    emit ready(get_contents());
}

void Book::receive_new_book_info(QString book_name, QString description)
{
    if(book_name.size()||description.size())
    {
        clear();
        this->book_name=book_name;
        this->description=description;
        emit book_created();
    }
}



Create_new_Book::Create_new_Book(QWidget *parent):QDialog(parent)
{
    setModal(1);
    auto layout_V=new QVBoxLayout();
    auto layout_name=new QHBoxLayout();
    auto layout_btn=new QHBoxLayout();
    setLayout(layout_V);

    auto tips_book_name=new QLabel("书名",this);
    edit_name=new QLineEdit(this);
    layout_V->addLayout(layout_name);
    layout_name->addWidget(tips_book_name);
    layout_name->addWidget(edit_name);

    auto label_description=new QLabel("简介：",this);
    edit_description=new QPlainTextEdit(this);
    layout_V->addWidget(label_description);
    layout_V->addWidget(edit_description);

    auto ok=new QPushButton("确认",this);
    auto cancel=new QPushButton("取消",this);
    layout_btn->addWidget(ok);
    layout_btn->addWidget(cancel);
    layout_V->addLayout(layout_btn);

    connect(ok,&QPushButton::clicked,[&](){
        hide();
        emit input_finish(edit_name->text(),edit_description->toPlainText());
    });
    connect(cancel,&QPushButton::clicked,[&](){
        hide();
    });
}

void Create_new_Book::clear()
{
    edit_name->clear();
    edit_description->clear();
}

Chapter::Chapter(int index, QString name, QString doc)
{
    this->doc=doc;
    this->index=index;
    this->name=name;
}

Chapter::Chapter()
{
    index=0;
}

void Chapter::clear()
{
    index=0;
    name.clear();
    doc.clear();
}

int Chapter::getIndex() const
{
    return index;
}

QString Chapter::getName() const
{
    return name;
}

QString Chapter::getDoc() const
{
    return doc;
}

void Chapter::setName(const QString &value)
{
    name = value;
}

void Chapter::setDoc(const QString &value)
{
    doc = value;
}

void Content::push_back(QString name, QString doc)
{
    QVector<Chapter>::push_back(Chapter(size(),name,doc));
}

