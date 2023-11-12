#include "win_directory.h"
#include <QPushButton>
#include <QListWidgetItem>

Win_Directory::Win_Directory(QStringList directory,QWidget *parent) : QDockWidget(parent)
{
    setWindowTitle("书籍目录");
    layout_main=new QFormLayout();

    listView_directory=new QListWidget(this);

    setWidget(listView_directory);

    for(auto &i:directory)
    {
        QListWidgetItem *a=new QListWidgetItem(i,listView_directory);
        listView_directory->scrollToItem(a);
    }

    //***************信号和槽******************
    connect(listView_directory,&QListWidget::itemClicked,this,&Win_Directory::select_directory);
}

void Win_Directory::select_directory(QListWidgetItem *item)
{
    emit click_on_directory(item->text());
}


