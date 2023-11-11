#ifndef BOOK_H
#define BOOK_H

#include<QString>
#include<QHash>
#include<QStringList>
#include<QByteArray>
#include<QDir>
#include<QVector>

class Book
{
public:
    Book();
    Book(QString book_name);
    //**************书籍操作*****************
    //创建书籍
    Book* create_book(void);
    //往书架导入新书籍
    Book* load_book(QString book_name,QString *unicode_txt);
    //打开书架上的书籍
    Book* open_book(Book *book);
    //保存书籍
    void save_book(void);
    //删除书籍
    void delete_book(QString book_name);

    //***************章节操作***************
    void add_chapter(QString chapter_name,QString chapter_content);
    void delete_chapter(QString chapter_name);
    void edit_chapter(QString chapter_name);
    void save_chapter(QString chapter_name);

    QString get_txt(void);
    QString get_book_name(void){return book_name;}
    //**********static************
    static QString get_bookname_from_path(QString book_dir);

private:
    QString book_name;//书名
    int chapter_num;//章节数
    QVector<QString> contents;//目录列表
    QHash<QString,QString> chapter;//书的章节，以目录名为索引，以正文为内容
//    int word_num;//书的字数
//    int history_pos;//阅读位置记录
};

#endif // BOOK_H
