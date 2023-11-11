#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "bookshelf.h"
#include "preview_txt.h"
#include "setting.h"
#include <QMainWindow>
#include<QPlainTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPlainTextEdit *edit_win;
    Preview_txt *preview_win;
    Bookshelf *bookshelf_win;
    Setting setting;
    Book book;


private slots:
    void accept_coding_type(QString coding);
    void load_new_book(void);
    void open_book(void);
    void close_book(void);
};
#endif // MAINWINDOW_H
