#ifndef BOOKSHELF_H
#define BOOKSHELF_H

#include <QWidget>
#include"setting.h"
#include<QHash>
#include<QString>
#include<QCommandLinkButton>

#include<QVBoxLayout>

class Bookshelf : public QWidget
{
    Q_OBJECT
public:
    explicit Bookshelf(QWidget *parent = nullptr);
signals:
    void return_chosen_book(QString book_name);

private:
    QVBoxLayout *main_layout;
    QHash<QString,QCommandLinkButton*> command_book_list;
public slots:
    void choose_book(Setting *set);

};

#endif // BOOKSHELF_H
