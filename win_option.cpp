#include "win_option.h"
#include<QFileDialog>
Win_Option::Win_Option(Setting *set,QDialog *parent) : QDialog(parent)
{
    setWindowTitle("设置");
    resize(600,600);
    main_layout=new QVBoxLayout;
    set_item_layout=new QFormLayout(this);
    btn_layout=new QHBoxLayout(this);
    H_layout_1=new QHBoxLayout(this);
    H_layout_2=new QHBoxLayout(this);

    browse_shelf_dir=new QPushButton("浏览",this);
    browse_database_dir=new QPushButton("浏览",this);
    coding_type=new QComboBox(this);

    edit_shelf_dir=new QLineEdit(this);
    edit_database_dir=new QLineEdit(this);

    H_layout_1->addWidget(edit_shelf_dir);
    H_layout_1->addWidget(browse_shelf_dir);
    H_layout_2->addWidget(edit_database_dir);
    H_layout_2->addWidget(browse_database_dir);

    ok=new QPushButton("确认",this);
    cancel=new QPushButton("取消",this);
    btn_layout->addWidget(ok);
    btn_layout->addWidget(cancel);

    set_item_layout->addRow("书架目录",H_layout_1);
    set_item_layout->addRow("数据目录", H_layout_2);
    set_item_layout->addRow("编码方式", coding_type);

    main_layout->addLayout(set_item_layout,5);
    main_layout->addLayout(btn_layout,1);
    this->setLayout(main_layout);

    setModal(1);

    //编码方式选择的下拉框
    auto codecs=QTextCodec::availableCodecs();
    QString s;
    for(auto i:codecs)
    {
        coding_type->addItem(QString(i));
    }


    //***************信号和槽***********
    connect(browse_shelf_dir,&QPushButton::clicked,[&](){
        edit_shelf_dir->setText(QFileDialog::getExistingDirectory(this,"选择书架目录"));
    });
    connect(browse_database_dir,&QPushButton::clicked,[&](){
        edit_database_dir->setText(QFileDialog::getExistingDirectory(this,"选择数据库目录"));
    });
    connect(cancel,&QPushButton::clicked,this,&Win_Option::close);
    connect(ok,&QPushButton::clicked,[&](){
        set->set(edit_shelf_dir->text(),edit_database_dir->text(),coding_type->currentText());
    });
}

Win_Option::~Win_Option()
{
    delete main_layout;
}
