#include"setting.h"
#include <QDir>

Setting::Setting(void)
{
    QDir dir("./");
    dir.mkdir("my_bookshelf");
    //如果配置文件不存在
    if(!QFile::exists(setting_conf))
    {
        //初始化数据
        bookshelf.clear();
        recent_book.clear();
        database_dir="./database";
        coding_type="UTF-8";

        bookshelf_dir="./my_bookshelf/";
        renew_setting();
    }
    //如果配置文件存在
    else
    {
        read_conf();
    }
}
void Setting::renew_setting(void)
{
    QFile conf_file(setting_conf);
    //创建配置文件
    conf_file.open(QFile::WriteOnly);
    QTextStream out(&conf_file);

    //书架信息
    int size=bookshelf.size();
    out<<size;
    for(auto i:bookshelf)
    {
        out<<i<<endl;
    }

    //最近打开
    size=recent_book.size();
    out<<size;
    for(auto i:recent_book)
    {
        out<<i<<endl;
    }

    //数据库信息
    out<<database_dir<<endl;

}
void Setting::read_conf(void)
{
    QFile conf_file(setting_conf);
    //创建配置文件
    conf_file.open(QFile::ReadOnly);
    QTextStream In(&conf_file);
    QString temp;
    int size=0;
    In>>size;
    for(int i=0;i<size;i++)
    {
        In>>temp;
        bookshelf.push_back(temp);
    }
    In>>size;
    for(int i=0;i<size;i++)
    {
        In>>temp;
        recent_book.push_back(temp);
    }
    In>>database_dir;
}
