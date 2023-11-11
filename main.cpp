#include "win_main.h"
#include <QApplication>

//#define __TEST
#ifdef __TEST
#include "win_preview.h"
#include "win_bookshelf.h"
#include "win_option.h"
#include "setting.h"
#include "book.h"
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Setting *s=new Setting;
    Win_Option option(s);
    option.show();
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
