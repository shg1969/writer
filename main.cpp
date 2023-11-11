/*模块说明
 * main()主函数
 * MainWindow主窗口，包含设置参数、打开的文件，模式（阅读、写作）
 * 设置窗口
 * 预览窗口
*/


#include "mainwindow.h"

#include <QApplication>
#define __TEST
#ifdef __TEST
#include "preview_txt.h"
#include "bookshelf.h"
#include "setting.h"
#include "book.h"
#include<QDebug>
#endif
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    auto s=Book::get_bookname_from_path("C:/123/34/67");
    Bookshelf b(Q_NULLPTR);
    Setting set;
    set.bookshelf.push_back("你好！");
    set.bookshelf.push_back("你好！shijie");
    b.choose_book(&set);
//    qDebug()<<s;
    return a.exec();
}
