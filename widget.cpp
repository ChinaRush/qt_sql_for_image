#include "widget.h"
#include "ui_widget.h"

#include "imagemodel.h"
#include "imagecontrol.h"
#include <QFile>
#include <QMessageBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->page = 1;

    this->imgList = new QListWidget;
    imgList->setViewMode(QListView::IconMode);
    imgList->setSpacing(4);

    imgList->setResizeMode(QListWidget::Adjust);
    imgList->setStyleSheet("border:none;font-size:15px");
    imgList->setIconSize(QSize(230,230));

    QList<QString> ImageList;
    QList<QString> nameList;


    char **qres2;
    qres2=ImageControl::getInstance()->getImagePath(page);
    //用List存视频路径，跳过表头，自增2存一次
    for(int i=ImageModel::col;i<(ImageModel::row+1)*ImageModel::col;i+=2)
    {
       ImageList<<qres2[i];
    }
    //用List存视频名称，跳过表头，自增2存一次
    for(int i=ImageModel::col+1;i<(ImageModel::row+1)*ImageModel::col;i+=2)
    {
       nameList<<qres2[i];
    }
    //将得到的list添加到QListWidgetItem单元项里面
    for (int i=0;i<ImageList.size();i++)
    {
       //定义QListWidgetItem对象
       QListWidgetItem *imageItem = new QListWidgetItem;
       //为单元项设置属性
       //设置
       imageItem->setIcon(QIcon(ImageList[i]));
       imageItem->setText(nameList.at(i));
       //重新设置单元项图片的宽度和高度
       imageItem->setSizeHint(QSize(220,220));
       //将单元项添加到QListWidget中
       imgList->addItem(imageItem);
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::imagelist()
{
    this->imgList->deleteLater();
    this->imgList =new QListWidget();


       //设置QListWidget的显示模式
       imgList-> setViewMode (QListView::IconMode);
       //设置QListWidget中单元项的间距
       imgList-> setSpacing(4);
       //设置自动适应布局调整(Adjust适应， Fixed不适应)，默认不适应
       imgList-> setResizeMode (QListWidget::Adjust) ;
       //设置不能移动
       imgList-> setMovement (QListWidget::Static) ;
       imgList->setStyleSheet("border:none;font-size:15px");
       imgList->setIconSize(QSize(230,230));


       QList<QString> ImageList;
       QList<QString> nameList;
       char **qres2;
       qres2=ImageControl::getInstance()->getImagePath(this->page);
       for(int i=ImageModel::col;i<(ImageModel::row+1)*ImageModel::col;i+=2)
       {
           ImageList<<qres2[i];

       }
       for(int i=ImageModel::col+1;i<(ImageModel::row+1)*ImageModel::col;i+=2)
       {
           nameList<<qres2[i];
       }

       for (int i=0;i<ImageList.size();i++)
       {
           //定义QListWidgetItem对象
           QListWidgetItem *imageItem = new QListWidgetItem;
           //为单元项设置属性
           //设置
           imageItem->setIcon(QIcon(ImageList[i]));
           imageItem->setText(nameList.at(i));
           //重新设置单元项图片的宽度和高度
           imageItem->setSizeHint(QSize(220,220));
           //将单元项添加到QListWidget中
           imgList->addItem(imageItem);
       }
       //重新添加到布局里面

       connect(imgList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(click_image(QListWidgetItem *)));
}

void Widget::get_alarm()
{
    this->toimage();
    if(page == 1)
    {
        this->page ++;
    }
    else
    {
        this->page --;
    }
}

void Widget::toimage()
{
    imagelist();
}

void Widget::click_image(QListWidgetItem *item)
{
    int size = 0;
    char **qres=ImageControl::getInstance()->getimage(item->text());
    QFile myfile(qres[1]);
    //获取图片大小
    if(myfile.open(QIODevice::ReadOnly))
    {
       size = myfile.size();
       myfile.close();
    }
    //获取图片宽高
    this->image_file.load(qres[1]);
    ui->name_label->setText("图片名称："+item->text());
    ui->size_label->setText("图片大小："+QString::number(size/1024)+" KB");
    ui->resolution_label->setText("照片尺寸："+QString::number(image_file.height())
                                       +" X "+QString::number(image_file.width()));

    //获得图片路径，加载出图片放大窗口
//    this->ImageWidget=new Image_Widegt(qres[1]);
//    this->ImageWidget->show();

}


void Widget::next()
{
    this->page++;
        char **qres3;
        QList<QString> ImageList;
        qres3=ImageControl::getInstance()->getImagePath(this->page);
        for(int i=ImageModel::col;i<(ImageModel::row+1)*ImageModel::col;i+=1)
        {
            ImageList<<qres3[i];
        }
         //如果没有就提示，并恢复原来页数
        if(ImageList.size()==0)
        {
           QMessageBox::warning(this, tr("提示！"),tr("已经是最后一页！"),QMessageBox::Yes);
           this->page--;
        }
        //否则加加载图片
        else
        {
            imagelist();
        }

}

void Widget::previous()
{
    if(this->page>1)
       {
           this->page--;
           imagelist();
       }
       //如果页数是第一页就提示
       else
       {
           QMessageBox::warning(this, tr("提示！"),tr("已经是第一页！"),QMessageBox::Yes);
       }

}


