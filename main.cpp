#include "mainwindow.h"
#include <QApplication>

#define __TEST
#ifdef __TEST
#include "preview_txt.h"
#include "bookshelf.h"
#include "setting.h"
#include "book.h"
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    return a.exec();
}
#endif

#ifndef __TEST
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
#endif
