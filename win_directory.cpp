#include "win_directory.h"
#include <QPushButton>
#include <QListWidgetItem>
#include <QDialog>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>

Win_Directory::Win_Directory(Book *book,QWidget *parent) : QDockWidget(parent)
{
    /*****************************初始化*****************************/
    this->book=book;
    setWindowTitle("书籍目录");
    setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    setFloating(0);
    /*****************************界面*****************************/
    auto layout_main=new QVBoxLayout();
    layout_main->setMargin(1);
    auto layout_add_chapter=new QFormLayout();
    auto group=new QGroupBox(this);

    auto label_add_chapter=new QLabel("增加章节",this);
    //增加章节窗口
    line_edit_add_chapter=new QLineEdit(this);
    layout_add_chapter->addRow(label_add_chapter,line_edit_add_chapter);
    layout_main->addLayout(layout_add_chapter);

    listView_directory=new QListWidget(this);
    layout_main->addWidget(listView_directory);

    group->setLayout(layout_main);
    setWidget(group);
    for(auto &chapter:book->get_contents())
    {
        auto s=chapter.getName();
        QListWidgetItem *a=new QListWidgetItem(s,listView_directory);
        listView_directory->scrollToItem(a);
        item_list_index[a]=chapter.getIndex();
    }

    //***************信号和槽******************
    //选择章节
    connect(listView_directory,&QListWidget::itemClicked,this,&Win_Directory::select_directory);
    //增加章节
    connect(line_edit_add_chapter,&QLineEdit::returnPressed,[&](){
        add_directory();
    });
}

Win_Directory::~Win_Directory()
{
}

void Win_Directory::add_directory()
{
    auto added=line_edit_add_chapter->text();
    book->add_chapter(added);

    QListWidgetItem *item=new QListWidgetItem(added);
    item_list_index[item]=book->get_contents().rbegin()->getIndex();

    listView_directory->addItem(item);
    listView_directory->setCurrentItem(item);
    emit dir_changed();

    line_edit_add_chapter->clear();
}

void Win_Directory::renew_directory(Content content)
{
    clear();
    for(auto i:content)
    {
        QListWidgetItem *a=new QListWidgetItem(i.getName(),listView_directory);
        item_list_index[a]=i.getIndex();
    }
}

void Win_Directory::clear()
{
    listView_directory->clear();
    line_edit_add_chapter->clear();
    item_list_index.clear();
}

void Win_Directory::select_directory(QListWidgetItem *item)
{
    auto i=item_list_index[item];
    emit click_on_directory(i);
}
