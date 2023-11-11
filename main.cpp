/*模块说明
 * main()主函数
 * MainWindow主窗口，包含设置参数、打开的文件，模式（阅读、写作）
 * 设置窗口
 * 预览窗口
*/

#include "mainwindow.h"
#include <QApplication>
#include "preview_txt.h"
#include "bookshelf.h"
#include "setting.h"
#include "book.h"
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
