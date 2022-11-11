#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

static const QString pathDisk = "/home/bova/Documents/test/20221108";

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void imagelist();

    void get_alarm();


public slots:
    void toimage();
    void next();
    void previous();
    void click_image(QListWidgetItem *item);

private:
    Ui::Widget *ui;

    QListWidget *imgList;

    int page;

    QImage image_file;
};
#endif // WIDGET_H
