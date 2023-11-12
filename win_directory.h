#ifndef WIN_DIRECTORY_H
#define WIN_DIRECTORY_H

#include <QDockWidget>
#include <QFormLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStringList>

class Win_Directory : public QDockWidget
{
    Q_OBJECT
public:
    explicit Win_Directory(QStringList directory,QWidget *parent = nullptr);
signals:
    void click_on_directory(QString);
private:
    QFormLayout *layout_main;
    QListWidget *listView_directory;
private slots:
    void select_directory(QListWidgetItem *item);
};

#endif // WIN_DIRECTORY_H
