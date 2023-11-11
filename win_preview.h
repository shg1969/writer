#ifndef PREVIEW_TXT_H
#define PREVIEW_TXT_H

#include <QWidget>
#include<QComboBox>
#include<QTextBrowser>
#include<QTextCodec>
#include<QPushButton>
#include<QByteArray>
#include "book.h"
#include<QList>
#include<QLabel>
#include<QHBoxLayout>
class Win_Preview : public QWidget
{
    Q_OBJECT
public:
    //提供预览窗口
    explicit Win_Preview(QWidget *parent);
    void preview_show(QString book_name,QByteArray txt);
signals:
    void sent_encoding_type(QString new_coding);
private:
    QTextBrowser *browser;
    QComboBox *ComboBox_celect_coding;
    QPushButton *ok;
    QPushButton *cancel;
    QLabel *label_encoding;
    QLabel *label_book_name;
    QHBoxLayout *layout_set_encoding;

    QString encoding_type;//编码方式名称
    QByteArray preview_txt;//预览文段
    QTextCodec *codec;//文字编码转换
private slots:
    void encoding_Changed(const QString &text);
};

#endif // PREVIEW_TXT_H
