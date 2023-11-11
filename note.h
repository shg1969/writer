#ifndef NOTE_H
#define NOTE_H

#include <QWidget>
#include <QDockWidget>
#include <QString>
#include <QHash>
#include <QString>
#include <QString>
#include <QString>
#include <QString>


class Note : public QWidget
{
    Q_OBJECT
public:
    explicit Note(QWidget *parent = nullptr);
    void load_lib();
    void renew_lib();

    void add_note();
    void delete_note();
    void modify_note();
    void search_noote();

signals:

private:
    QDockWidget *dock_main;
    QHash<QString,QString>excerpt;


};

#endif // NOTE_H
