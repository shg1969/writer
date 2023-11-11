#ifndef SETTING_H
#define SETTING_H

#include <QString>
#include <QVector>
#include <QFile>

#include "book.h"
#include <QTextStream>

const QString setting_conf="./conf";
class Setting
{
public:
    Setting(void);
    void renew_setting_file(void);//更新配置文件
    void read_conf(void);//从配置文件读取配置信息
    void set(QString bookshelf_dir,QString database_dir,QString coding_type,Book *current_book);
    QString get_bookshelf_dir(void){return bookshelf_dir;}
    QVector<QString> get_bookshelf(void){return bookshelf;}
    QVector<QString> get_recent_book(void){return recent_book;}
    QString get_database_dir(void){return database_dir;}
    QString get_coding_type(void){return coding_type;}
    Book* get_current_book(void){return current_book;}
private:
    QString bookshelf_dir;//书架目录
    QVector<QString> bookshelf;//书架书籍列表
    QVector<QString> recent_book;//最近打开列表
    QString database_dir;//数据目录
    QString coding_type;//编码方式
    Book *current_book;//当前打开的书籍
};
#endif // SETTING_H
