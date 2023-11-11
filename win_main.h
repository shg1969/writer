#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "win_bookshelf.h"
#include "win_preview.h"
#include "win_read.h"
#include "setting.h"
#include <QMainWindow>
#include<QPlainTextEdit>

class Win_Main : public QMainWindow
{
    Q_OBJECT

public:
    Win_Main(QWidget *parent = nullptr);
    ~Win_Main();
signals:
    void txt_selection_Changed(QString);

private:
    QPlainTextEdit *edit_txt;
    Win_Preview *preview_win;
    Win_Bookshelf *bookshelf_win;
    Win_Read*record_win;
    Setting setting;
    Book book;


private slots:
    void accept_coding_type(QString coding);
    void load_new_book(void);
    void open_book(void);
    void close_book(void);
};
#endif // MAINWINDOW_H
