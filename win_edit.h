#ifndef WINEDIT_H
#define WINEDIT_H

#include <QTabWidget>
#include <QVector>
#include <QHash>
#include<QTextEdit>
#include"book.h"

class Win_Edit : public QTabWidget
{
    Q_OBJECT
public:
    explicit Win_Edit(Book*book,QWidget *parent = nullptr);
    void add_tab(int chapter_index,QString data);
    QString get_txt();
    QString get_html();
    void set_txt(QString data);
    void set_html(QString data);
    void set_font(const QFont &font);
    void save_all();
    QTextEdit*TextEdit_widget(int index);
    QTextEdit*current_page(void);
    void clear();
signals:
    void book_changed();
    void txt_selection_changed(QString);
private slots:
    void close_tab(int index);

private:
    void set_saved_flag();
    void set_font();
    void emit_selection();
    QHash<int,bool> is_changed;
    QFont font;
    QHash<int,QTextEdit*> open_text_edit;//窗口序号：窗口指针
    QHash<QTextEdit*,int> opened_chapter;//窗口指针：章节序号
    Book*book;
};

#endif // WINEDIT_H
