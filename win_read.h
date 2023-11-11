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
//#include <QHBoxLayout>

class Win_Read : public QWidget
{
    Q_OBJECT
public:
    explicit Win_Read(QWidget *parent = nullptr);
private:
    QDockWidget *dock_main;
    QVBoxLayout *layout_main;
    QLabel *key;
    QLineEdit *edit_key;


signals:

};

#endif // READ_WIN_H
