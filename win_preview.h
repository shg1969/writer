#ifndef PREVIEW_TXT_H
#define PREVIEW_TXT_H

#include <QDialog>
#include<QComboBox>
#include<QTextBrowser>
#include<QTextCodec>
#include<QPushButton>
#include<QByteArray>
#include<QList>
#include<QLabel>
#include<QHBoxLayout>
class Win_Preview : public QDialog
{
    Q_OBJECT
public:
    //提供预览窗口
    explicit Win_Preview(QWidget *parent=nullptr);
    void show_win(QString txt);
    ~Win_Preview();
    QString get_encoding_type() const;
    void set_showing_book_name(QString name);

signals:
    void sent_encoding_type(QString new_coding);
private:
    QVBoxLayout *main_layout;
    QTextBrowser *browser;
    QComboBox *ComboBox_celect_coding;
    QPushButton *ok;
    QPushButton *cancel;
    QLabel *label_encoding;
    QLabel *label_book_name;
    QHBoxLayout *layout_set_encoding;
    QHBoxLayout *btn_layout;

    QString encoding_type;//编码方式名称
    QString preview_txt;//预览文段
    QTextCodec *codec;//文字编码转换
private slots:
    void encoding_Changed(const QString &text);
};

#endif // PREVIEW_TXT_H
