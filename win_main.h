#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "win_preview.h"
#include "win_read.h"
#include "win_edit.h"
#include "win_directory.h"
#include <QMainWindow>
#include<QPlainTextEdit>
#include <QToolBar>
#include <QFontComboBox>
#include <QComboBox>
#include<QCheckBox>

#define TEMP_FILE_NAME "temp"

class Win_Main : public QMainWindow
{
    Q_OBJECT

public:
    Win_Main(QWidget *parent = nullptr);
    ~Win_Main();

signals:
    void txt_selection_Changed(QString);

private slots:
    void slot_load_book(void);
    void slot_open_book();
    void slot_save_book(void);
    void slot_save_book_as();
    void slot_close_book(void);
    void slot_delete_book(void);

    void slot_open_chapter(int index);

    void textSize(const QString &p);
    void change_txt_font(const QFont &font);
    void change_theme(int state);

private:
    void clear(void);
    void ask_save(void);
    void set_window_title(bool is_changed,QString keep_old="");
    Win_Edit        *edit_txt;
    Win_Read        *win_record;
    Win_Directory   *win_directory;
    QByteArray      byte_txt;
    Book            book;
    QString         new_book_name;
    bool            is_book_changed;

    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    const QString bright_theme_style_sheet=
            "QLabel,QCheckBox,QFontComboBox{color: white;background: rgb(25, 25, 25)}"
            "QListView,QMainWindow,QDockWidget{color: white; background: rgb(25, 25, 25)}"
            "QMenuBar,QToolBar{color: rgb(205, 205, 205); background: rgb(75, 75, 75)}"
            "QPushButton{ color: rgb(186, 140, 14); background-color: rgb(100, 100, 100) }"
            "QCheckBox,QComboBox,QSpinBox,QFontComboBox,QTabBar{color: white;background-color: rgb(100, 100, 100)}"
            "QTextEdit,QLineEdit,QTabWidget{color: rgb(205, 205, 205); background-color: rgb(50, 50, 50)}"
            "QComboBox::drop-down { background-color: rgb(100, 100, 100) }"
            "QCheckBox::indicator:unchecked {color: rgb(75, 75, 75);}";
};
#endif // MAINWINDOW_H
