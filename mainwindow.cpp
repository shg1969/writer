#define __TEST

#include "mainwindow.h"
#include "preview_txt.h"
#include "setting.h"
#include<QDebug>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QDebug>
#include<QPlainTextEdit>
#include<QString>
#include<QFileDialog>
#include<QDockWidget>
#include<QApplication>
#include <QMessageBox>
#include <QDesktopWidget>
#include "bookshelf.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /****************************窗体界面****************************/
    //整体布局
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
    resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
    move((availableGeometry.width() - width()) / 2,
            (availableGeometry.height() - height()) / 2);
    //菜单栏
    QMenuBar *menubar=new QMenuBar(this);
    setMenuBar(menubar);

    auto file_menu=menubar->addMenu("文件");
    auto about_menu=menubar->addMenu("关于");

    auto create_book=file_menu->addAction("导入书籍");
    auto open_book=file_menu->addAction("打开书籍");
    auto close_book=file_menu->addAction("关闭书籍");

//    auto about_Qt=about_menu->addAction("关于Qt");
//    auto about_author=about_menu->addAction("关于作者");

    //编辑窗口
    QDockWidget *dock_edit=new QDockWidget("编辑窗口",this);
    edit_win=new QPlainTextEdit(dock_edit);
    dock_edit->setWidget(edit_win);
    setCentralWidget(dock_edit);

    /****************************窗口配置****************************/
    bookshelf_win=new Bookshelf(this);
    preview_win=new Preview_txt(Q_NULLPTR);
    //编辑窗口
    QString s;
    for(auto i:setting.bookshelf)
    {
        s+=i;
    }
    for(auto i:setting.recent_book)
    {
        s+=i;
    }
    s+=setting.database_dir;
    edit_win->appendPlainText(s);


    /****************************信号和槽****************************/
    //新导入书籍
    connect(create_book,&QAction::triggered,this,&MainWindow::load_new_book);
    //新导入书籍
    connect(open_book,&QAction::triggered,this,&MainWindow::open_book);
    //新导入书籍
    connect(close_book,&QAction::triggered,this,&MainWindow::close_book);

    //处理预览窗口返回的信息
    connect(preview_win,&Preview_txt::sent_encoding_type,this,&MainWindow::accept_coding_type);

    /****************************调试内容****************************/

}

MainWindow::~MainWindow()
{
    delete preview_win;
}

void MainWindow::load_new_book(void)
{
    QString filename= QFileDialog::getOpenFileName(this, "打开文件",setting.bookshelf_dir,"文本文件 (*.txt)");
    QFile file(filename);
    //如果文件打开失败
    if(!file.open(QFile::ReadOnly))
        QMessageBox error(QMessageBox::Warning,"错误","打开文件失败！！！");
    else//文件打开成功
    {
        //读取文件，放到reading_txt，预览，选择编码方式
        preview_win->preview_conf(filename,file.readAll());
    }
}
void MainWindow::open_book(void)
{

}
void MainWindow::close_book(void)
{

}

void MainWindow::accept_coding_type(QString coding)
{
    setting.coding_type=coding;
    //重新设置编辑窗口的编码，更新显示文本
    auto s=book.book_name;

}
