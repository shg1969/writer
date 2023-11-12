#ifndef READ_WIN_H
#define READ_WIN_H

#include <QDockWidget>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QListWidget>
#include <QCheckBox>
#include <QGroupBox>
#include <QListWidgetItem>
#include <QTextBrowser>
#include <QHash>
#include <QString>
#include <QVector>

class Win_Read : public QDockWidget
{
    Q_OBJECT
public:
    explicit Win_Read(QWidget *parent = nullptr);
    ~Win_Read();
public slots:
    void auto_set_key_focus(QString content);
private:
    QString selected_in_txt;
    QHash<QString,QVector<QString>> lib_recent_added;
    QGroupBox *all;
    QVBoxLayout *layout_main;

    QHBoxLayout *layout_key;
    QCheckBox *checkBox_auto_focus;
    QLabel *label_key;
    QLineEdit *edit_key;

    QHBoxLayout *layout_recent;
    QLabel *label_recent_added;
    QPushButton *clear_recent_record;
    QListWidget *listView_recent_added;
    QLabel *label_content;
    QTextBrowser *content_browse;

signals:
private slots:
    void show_select_item(QListWidgetItem *item);

};

#endif // READ_WIN_H
