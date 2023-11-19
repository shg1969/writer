#ifndef BOOK_H
#define BOOK_H
#include <QObject>
#include<QString>
#include<QHash>
#include<QStringList>
#include<QByteArray>
#include<QDir>
#include<QVector>
#include<QStringList>
#include<QLineEdit>
#include<QPlainTextEdit>
#include"win_preview.h"

#define TOP_DIR             "C:/Users/lei/Desktop/books/"
#define BOOK_SHELF_DIR      "C:/Users/lei/Desktop/books/bookshelf/"
#define BOOK_DATA_DIR       "C:/Users/lei/Desktop/books/data/"
#define TXT_LIB             "C:/Users/lei/Desktop/读书/txt/"

class Create_new_Book;

class Chapter{
public:
    Chapter();
    Chapter(int index,QString name="",QString doc="");
    void clear();   //清空

    int getIndex() const;
    QString getName() const;
    QString getDoc() const;

    //设置
    void setName(const QString &value);
    void setDoc(const QString &value);

private:
    int index;      //该章节在书中的序号
    QString name;   //章节名
    QString doc;    //章节内容
};
class Content:public QVector<Chapter>
{
public:
    void push_back(QString name="",QString doc="");
};
class Note
{
public:

private:

};

class Book:public QObject
{
    Q_OBJECT
public:
    //**************书籍操作*****************
    //新建书籍
    Book(QObject *parent = Q_NULLPTR);
    ~Book();

    //书籍操作
    void create();
    //导入新书籍，并将其数据格式化保存到.bk文件或导入bk文件
    void init_from_file();
    void init_from_book(QString book="");
    //保存书籍到文件
    bool save();
    //删除书籍：包括书架和数据文件
    bool remove();
    void clear();

    //***************章节操作***************
    void add_chapter(QString chapter_name,QString chapter_content="");
    void delete_chapter(int index);
    void edit_chapter_name(int index,QString New);
    void save_chapter(int chapter_index,QString txt);

    //***************书籍信息***************
    //获取全文
    QString     get_txt(void);
    //书名
    QString     get_book_name(void);
    void        set_book_name(QString new_name);
    //章名及内容
    Content     get_contents() const;
    QString      get_chapter_txt(int chapter_index);
    //简介
    QString     get_description() const;
    void        set_description(const QString &value);
    //章节数
    int         get_chapter_num() const;

    //摘录
    void add_note(const QString &key,const QString &s);
    void delete_note(const QString &key,int index);
    void edit_note(const QString &keykey,int index);
    void search_on_key(const QString &key);
    void search_on_src(const QString &key);


signals:
    void ready(Content content);
    void book_created(void);
private:
    Create_new_Book     *win_create;
    Win_Preview         *win_preview;
    QString             encoding;
    QString             unicode_txt;
    QString             book_dir;       //书籍目录
    QString             book_name;      //书名
    QString             description;    //简介
    int                 chapter_num;    //章节数
    Content             contents;       //目录列表
    QString get_book_name_from_path(QString path);
    QHash<QString,QStringList>note;
//    QHash<QString,int>  chapter_index;
//    int word_num;//书的字数
//    int history_pos;//阅读位置记录
private slots:
    void receive_encoding(QString encoding);
    void receive_new_book_info(QString book_name,QString description);
};
class Create_new_Book:public QDialog
{
    Q_OBJECT
public:
    Create_new_Book(QWidget *parent = Q_NULLPTR);
    void clear();
signals:
    void input_finish(QString book_name,QString description);
private:
    QLineEdit *edit_name;
    QPlainTextEdit *edit_description;
};
QStringList book_name_to_file_name(QStringList book_names);//以_代替空格，用数字前标区分同名章节
QStringList file_name_to_book_name(QStringList file_names);
#endif // BOOK_H
