#ifndef OPTION_H
#define OPTION_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <QFile>
#include <QDialog>
#include<QPushButton>
#include<QLabel>
#include<QComboBox>
#include<QLineEdit>
#include<QFormLayout>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QTextCodec>

#include "setting.h"
#include <QTextStream>

class Win_Option : public QDialog
{
    Q_OBJECT
public:
    explicit Win_Option(Setting *set,QDialog *parent = nullptr);
    ~Win_Option(void);
private:
    QVBoxLayout *main_layout;
    QFormLayout *set_item_layout;
    QHBoxLayout *H_layout_1;
    QHBoxLayout *H_layout_2;
    QHBoxLayout *btn_layout;

    QPushButton *browse_shelf_dir;
    QPushButton *browse_database_dir;
    QComboBox *coding_type;

    QLineEdit *edit_shelf_dir;
    QLineEdit *edit_database_dir;

    QPushButton *ok;
    QPushButton *cancel;

signals:


};


#endif // OPTION_H
