#ifndef WIN_DIRECTORY_H
#define WIN_DIRECTORY_H

#include <QDockWidget>
#include <QFormLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStringList>
#include <QDialog>
#include <QHash>
#include <QString>
#include "book.h"
class Win_Add_Chapter;

class Win_Directory : public QDockWidget
{
    Q_OBJECT
public:
    explicit Win_Directory(Book *book,QWidget *parent = nullptr);
    ~Win_Directory(void);

    void clear();
signals:
    void click_on_directory(int index);
    void dir_changed();
private:
    void add_directory();

    QListWidget             *listView_directory;
    QLineEdit               *line_edit_add_chapter;
    QHash<QListWidgetItem*,int> item_list_index;
    Book                    *book;

public slots:
    void renew_directory(Content content);
private slots:
    void select_directory(QListWidgetItem *item);
};

#endif // WIN_DIRECTORY_H
