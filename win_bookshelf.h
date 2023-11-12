#ifndef BOOKSHELF_H
#define BOOKSHELF_H

#include <QWidget>
#include"setting.h"
#include<QHash>
#include<QString>
#include<QCommandLinkButton>

#include<QVBoxLayout>

class Win_Bookshelf : public QWidget
{
    Q_OBJECT
public:
    explicit Win_Bookshelf(QWidget *parent = nullptr);
    ~Win_Bookshelf(void);
    void add_book(Book*book);
    void delete_books(void);
    void renew_bookshelf(void);
signals:
    void return_chosen_book(QString book_name);

private:
    QVBoxLayout *main_layout;
    QHash<QString,QCommandLinkButton*> command_book_list;
public slots:

    void choose_book_on_shelf(Setting *set);

};

#endif // BOOKSHELF_H
