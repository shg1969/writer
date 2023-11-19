#include "win_preview.h"
#include "book.h"
//#include "setting.h"
#include<QComboBox>
#include<QTextBrowser>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QSpacerItem>
#include<QLabel>
#include<QString>
#include<QTextCodec>


Win_Preview::Win_Preview(QWidget *parent) : QDialog(parent)
{
    /****************************窗体界面****************************/
    setWindowTitle("文字预览：选择编码方式");
    resize(600,600);
    main_layout=new QVBoxLayout;

    label_encoding=new QLabel("编码方式:",this);
    label_book_name=new QLabel("书名:");

    ComboBox_celect_coding=new QComboBox(this);
    ComboBox_celect_coding->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    layout_set_encoding=new QHBoxLayout();
    layout_set_encoding->addWidget(label_encoding);
    layout_set_encoding->addWidget(ComboBox_celect_coding);

    browser=new QTextBrowser(this);

    ok=new QPushButton("确定",this);
    cancel=new QPushButton("取消",this);
    btn_layout=new QHBoxLayout();
    btn_layout->addSpacing(30);
    btn_layout->addWidget(ok);
    ok->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    btn_layout->addSpacing(30);
    btn_layout->addWidget(cancel);
    cancel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    btn_layout->addSpacing(30);

    main_layout->addWidget(label_book_name);
    main_layout->addItem(layout_set_encoding);
    main_layout->addWidget(browser);
    main_layout->addItem(btn_layout);

    this->setLayout(main_layout);

    /****************************窗口配置****************************/
    //编码方式选择的下拉框
    QList<QByteArray> codecs{"UTF-8","UTF-16","UTF-32","GB18030","GB2312","GBK","Big5"};
    encoding_type=codecs[0];//默认编码方式
    QString s;
    for(auto i:codecs)
    {
        ComboBox_celect_coding->addItem(QString(i));
    }

    //窗体设置为模态显示
    setWindowModality(Qt::ApplicationModal); //设置阻塞类型
    setAttribute(Qt::WA_ShowModal, true);    //属性设置 true:模态 false:非模态

    /****************************信号和槽****************************/
    //按照用户的选择，更改显示的编码方式
    connect(ComboBox_celect_coding,&QComboBox::currentTextChanged,this,&Win_Preview::encoding_Changed);
    connect(cancel,&QPushButton::clicked,this,&Win_Preview::hide);
    //只要按了确认，就发射关于编码类型的 “广播”
    connect(this->ok,&QPushButton::clicked,[&](){
        this->close();
        emit sent_encoding_type(encoding_type);
    });

    this->hide();
}
Win_Preview::~Win_Preview()
{
    delete main_layout;
    delete btn_layout;
    delete layout_set_encoding;
    delete layout_set_encoding;
}

QString Win_Preview::get_encoding_type() const
{
    return encoding_type;
}

void Win_Preview::set_showing_book_name(QString name)
{
    label_book_name->setText("书名："+name);
}

//配置预览对象
void Win_Preview::show_win(QString txt)
{
    preview_txt.clear();
    //取前1024*8字节来预览
    auto length=1024*8<txt.length()?1024*8:txt.length();
    preview_txt=txt.left(length);
    browser->setText(preview_txt);
    this->show();
}

void Win_Preview::encoding_Changed(const QString &encoding)
{
    if(encoding_type==encoding)return;
    encoding_type=encoding;
    //解码
    codec = QTextCodec::codecForName(encoding.toUtf8());
    QString string = codec->toUnicode(preview_txt.toUtf8());//如果本来就是UTF-8会导致程序崩溃
    //预览
    browser->setText(string);
}
