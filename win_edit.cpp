#include "win_edit.h"
#include "book.h"
#include<QTextEdit>

Win_Edit::Win_Edit(Book*book,QWidget *parent) : QTabWidget(parent)
{
    this->book=book;
    setWindowFlag(Qt::FramelessWindowHint);
    setTabsClosable(1);
    setMovable(1);

    connect(this,&QTabWidget::tabCloseRequested,this,&Win_Edit::close_tab);
    connect(this,&Win_Edit::currentChanged,[&](){set_font();});
}

void Win_Edit::add_tab(int chapter_index, QString data)
{
    if(open_text_edit.contains(chapter_index))
    {
        setCurrentWidget(open_text_edit[chapter_index]);
        current_page()->setFocus();
        return;
    }
    auto new_edit=new QTextEdit(this);
    open_text_edit[chapter_index]=new_edit;
    opened_chapter[new_edit]=chapter_index;

    QString chapter_name=book->get_contents()[chapter_index].getName();
    int index=QTabWidget::addTab(new_edit,chapter_name);
    is_changed[index]=0;

    new_edit->setText(data);
    new_edit->setFocus();
    setCurrentWidget(open_text_edit[chapter_index]);
    connect(new_edit,&QTextEdit::textChanged,[&](){
        if(!is_changed[index])//如果是保存后首次改动
        {
            is_changed[index]=1;

            auto s=tabText(currentIndex());
            if(!s.contains("*"))
            {
                s+="*";
                setTabText(currentIndex(),s);
            }
            emit this->book_changed();
        }
    });

    connect(new_edit,&QTextEdit::selectionChanged,this,&Win_Edit::emit_selection);

    if(count()==1)
    {
        this->show();
        return;
    }
}

QString Win_Edit::get_txt()
{
    return dynamic_cast<QTextEdit*>(currentWidget())->toPlainText();
}

QString Win_Edit::get_html()
{
    return dynamic_cast<QTextEdit*>(currentWidget())->toHtml();
}

void Win_Edit::set_txt(QString data)
{
    dynamic_cast<QTextEdit*>(currentWidget())->setText(data);
}

void Win_Edit::set_html(QString data)
{
    dynamic_cast<QTextEdit*>(currentWidget())->setHtml(data);
}

void Win_Edit::set_font(const QFont &font)
{
    this->font=font;
    current_page()->setFont(font);
}

void Win_Edit::save_all()
{
    for(int i=0;i<count();i++)
    {
        auto w=open_text_edit[i];//各个窗口
        auto s=book->get_contents()[opened_chapter[w]].getName();//窗口名
        book->save_chapter(opened_chapter[w],dynamic_cast<QTextEdit*>(widget(i))->toPlainText());
    }
    set_saved_flag();
}

QTextEdit *Win_Edit::TextEdit_widget(int index)
{
    return dynamic_cast<QTextEdit*>(QTabWidget::widget(index));
}

QTextEdit *Win_Edit::current_page()
{
    return dynamic_cast<QTextEdit*>(currentWidget());
}

void Win_Edit::clear()
{
    QTabWidget::clear();
    open_text_edit.clear();
    is_changed.clear();
}


void Win_Edit::close_tab(int index)
{
    QString s=this->tabText(index);
    if(s.contains("*"))s=s.left(s.size()-1);

    if(count()==1)
    {
        int p=opened_chapter[current_page()];
        opened_chapter.remove(current_page());
        open_text_edit.remove(p);
        current_page()->clear();
    }
    removeTab(index);
}

void Win_Edit::set_saved_flag()
{
    for(auto &i:is_changed)
    {
        i=0;
    }
    QString s;
    for(int i=0;i<count();i++)
    {
        s=tabText(i);
        setTabText(i,s.left(s.length()-1));
    }
}

void Win_Edit::set_font()
{
    if(count())
        current_page()->setFont(font);
}

void Win_Edit::emit_selection()
{
    auto s=current_page()->textCursor().selectedText();
    emit txt_selection_changed(s);
}
