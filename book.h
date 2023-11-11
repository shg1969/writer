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
    //书籍一律采用Unicode存储
public:

    QString book_name;//书名

    Book();
    Book(QString book_name);
    void load_book(QString book_name);
    Book* create_book(QString book_name,QString *unicode_txt);
    void save_book(void);
    void add_chapter(QString chapter_name,QString chapter_content);
    void delete_chapter(QString chapter_name);
    void edit_chapter(QString chapter_name);
    void save_chapter(QString chapter_name);
    QString get_raw(void);
    static QString get_bookname_from_path(QString book_dir);
private:
    int chapter_num;//章节数
    QVector<QString> contents;//目录列表
    QHash<QString,QString> chapter;//书的章节，以目录名为索引，以正文为内容

//    int word_num;//书的字数

};

#endif // BOOK_H
