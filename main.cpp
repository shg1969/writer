#include "win_main.h"
#include <QApplication>

//#define __TEST
#ifdef __TEST
#include "win_preview.h"
#include "win_bookshelf.h"
#include "win_option.h"
//#include "setting.h"
#include "book.h"
#include "win_read.h"
#include "win_directory.h"
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//  Setting *s=new Setting;
    Book *book=new Book;
    Win_Directory w(book);
    w.show();
    return a.exec();
}
#endif

#ifndef __TEST
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Win_Main w;
    w.show();
    return a.exec();
}
#endif
