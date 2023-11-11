#include "win_bookshelf.h"
#include<QDebug>
#include<QCommandLinkButton>

Win_Bookshelf::Win_Bookshelf(QWidget *parent) : QWidget(parent)
{
    /****************************窗体界面****************************/
    resize(300,400);
    main_layout=new QVBoxLayout(this);
    setLayout(main_layout);

    this->hide();
}
void Win_Bookshelf::choose_book_on_shelf(Setting *set)
{
    for(auto&i:set->get_bookshelf())
    {
        auto temp=new QCommandLinkButton(i,this);
        if(command_book_list.contains(i))return;

        command_book_list[i]=temp;
        main_layout->addWidget(temp);
        connect(temp,&QCommandLinkButton::clicked,[&](){
            emit return_chosen_book(i);
            qDebug()<<i;
        });
    }
    show();
}
