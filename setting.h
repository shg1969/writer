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
    QString bookshelf_dir;//书架目录
    QVector<QString> bookshelf;//书架书籍列表
    QVector<QString> recent_book;//最近打开列表
    QString database_dir;//数据库目录
    QString coding_type;
    Book current_book;

    void renew_setting(void);//更新配置文件
    void read_conf(void);//从配置文件读取配置信息
};
#endif // SETTING_H
