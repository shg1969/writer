#include "bookshelf.h"
#include<qDebug>
#include<QCommandLinkButton>

Bookshelf::Bookshelf(QWidget *parent) : QWidget(parent)
{
    /****************************窗体界面****************************/
    resize(300,400);
    main_layout=new QVBoxLayout(this);
    setLayout(main_layout);
}
void Bookshelf::choose_book(Setting *set)
{
    for(auto&i:set->bookshelf)
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
