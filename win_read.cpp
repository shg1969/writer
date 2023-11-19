#include "win_read.h"

Win_Read::Win_Read(QWidget *parent) : QDockWidget(parent)
{
    setWindowTitle("语段摘录");
    this->setWindowFlags(Qt::FramelessWindowHint);
    //由于基类是QDockWidget，要容纳多个部件，就要增加一个容器类容纳部件
    all=new QGroupBox(this);
    layout_key=new QHBoxLayout();
    layout_recent=new QHBoxLayout();
    layout_main=new QVBoxLayout;
    layout_main->setMargin(1);

    checkBox_auto_focus=new QCheckBox(" 选中文本后自动聚焦",this);
    label_key=new QLabel("关键字:",this);
    edit_key=new QLineEdit(this);
    layout_key->addWidget(label_key);
    layout_key->addWidget(edit_key);
    layout_main->addWidget(checkBox_auto_focus);
    layout_main->addLayout(layout_key);

    label_recent_added=new QLabel("最近添加:",this);
    clear_recent_record=new QPushButton("隐藏以下记录",this);
    layout_recent->addWidget(label_recent_added);
    layout_recent->addWidget(clear_recent_record);
    listView_recent_added = new QListWidget(this);
    layout_main->addLayout(layout_recent);
    layout_main->addWidget(listView_recent_added);

    label_content=new QLabel("文段内容",this);
    content_browse=new QTextBrowser(this);
    content_browse->setPlaceholderText("请选择最近添加项");
    layout_main->addWidget(label_content);
    layout_main->addWidget(content_browse);

    all->setLayout(layout_main);
    setWidget(all);

    //****************信号和槽*************
    connect(edit_key,&QLineEdit::returnPressed,[&](){
        QListWidgetItem *a=new QListWidgetItem(edit_key->text(),listView_recent_added);
        listView_recent_added->scrollToItem(a);
        if(!lib_recent_added.contains(edit_key->text()))
            lib_recent_added[edit_key->text()]=QVector<QString>{selected_in_txt};
        else
            lib_recent_added[edit_key->text()].push_back(selected_in_txt);
    });
    connect(clear_recent_record,&QPushButton::clicked,[&](){
        listView_recent_added->clear();
    });
    //在最近输入记录中选择一项，则在content_browse显示内容
    connect(listView_recent_added,&QListWidget::itemClicked,this,&Win_Read::show_select_item);
    //**************数据**********
}
Win_Read::~Win_Read()
{
    delete layout_main;
    delete layout_key;
    delete layout_recent;
}
void Win_Read::auto_set_key_focus(QString content)
{
    if(checkBox_auto_focus->isChecked())
    {
        edit_key->clear();
        edit_key->setFocus();
        selected_in_txt=content;
    }
}

void Win_Read::show_select_item(QListWidgetItem *item)
{
    content_browse->clear();
    for(auto&s:lib_recent_added[item->text()])
    content_browse->append(s);
}
