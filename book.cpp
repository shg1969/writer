#include "book.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include<QDir>
#include<QPair>
#include <QIODevice>
#include"setting.h"
Book::Book()
{
    book_name="";//书名
    chapter_num=0;
}
Book::Book(QString book_name)
{
    this->book_name=book_name;
    chapter_num=0;
}
QString Book::get_txt(void)
{
    QString txt;
    for(auto i:contents)
        txt+=i+"\n"+chapter[i]+"\n";
    return txt;
}
void Book::add_chapter(QString chapter_name,QString chapter_content)
{
    chapter_num++;//章节数加一
    //增加目录
    contents.push_back(chapter_name);
    //添加章节
    chapter[chapter_name]=chapter_content;
}
void Book::delete_chapter(QString chapter_name)
{
    chapter.remove(chapter_name);
}
Book* Book::load_book(QString book_name,QString *unicode_txt)
{
     Book *book=new Book(book_name);
     QString para="",doc="";
     QString last_chapter_name="第0章";
     //分章录入
     int max_length=QString("第九千九百九十九章").size();
     for(int i=0;i<unicode_txt->length();i++)
     {
         //将空格过滤
         if(unicode_txt[i]==' ')continue;
         //段落内
         if(unicode_txt[i]!='\n')
         {
             para+=unicode_txt[i];
         }
         else//段落末尾，unicode_txt[i]=='\n'
         {
             //如果这一段是章节名称
             if(para.size()<max_length&&para.contains("第")&&para.contains("章"))
             {
                 add_chapter(last_chapter_name,doc);
                 doc.clear();
                 last_chapter_name=para;
                 para.clear();
             }
             else//不是章节名，只是普通段
             {
                 doc+=para+'\n';
                 para.clear();
             }
         }
     }
     add_chapter(last_chapter_name,doc);
     return book;
}
//void Book::load_book(QString book_dir)
//{
//    if(!QFile::exists(book_dir))
//    {
//        QMessageBox::warning(Q_NULLPTR,"打开文件失败","该书籍不存在");
//        return ;
//    }
//    QFile book(book_dir);
//    QTextStream In(&book);
//    QString temp,temp_txt;
//    //书名
//    this->book_name=book_dir;
//    //章节数
//    In>>chapter_num;
//    //目录
//    for(int i=0;i<chapter_num;i++)
//    {
//        In>>temp;
//        contents.push_back(temp);
//    }
//    //分章录入
//    for(int i=0;i<chapter_num;i++)
//    {

//        do{
//            //读取一段字符
//            In>>temp;
//            temp_txt+=temp+"\n";
//        }while(temp!="Next_CHAPTER");

//        //找到章节名,将上一章录入
//        chapter[contents[i]]=temp_txt;
//        temp_txt.clear();
//    }
//    book.close();
//}
void Book::save_book(void)
{
    QFile file(book_name);
    file.open(QFile::WriteOnly);
    QTextStream out(&file);
    //输出章节数
    int count=chapter_num;
    out<<chapter_num<<endl;
    //输出目录
    for(auto i:chapter)
    {
        out<<i<<endl;
        count--;
        if(!count)break;
    }
    //输出正文
    count=chapter_num;
    for(auto i:contents)
    {
        out<<"Next_CHAPTER"<<endl;
        out<<i<<endl;
        count--;
        if(!count)break;
    }

    file.close();
}

QString Book::get_bookname_from_path(QString book_dir)
{
    QString s;
    for(auto i=book_dir.size()-1;i>=0;i--)
    {
        if(book_dir[i]=='/')break;
        else s.push_front(book_dir[i]);
    }
    return s;
}
