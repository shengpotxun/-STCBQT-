#ifndef WIDGET_H
#define WIDGET_H
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_openport_clicked();

    void on_closeport_clicked();

    void on_button0_clicked();

    void on_button1_clicked();

    void on_button2_clicked();

    void on_button3_clicked();

    void on_button4_clicked();

    void on_button5_clicked();

    void on_button6_clicked();

    void on_button7_clicked();

    void on_button8_clicked();

    void on_button9_clicked();

    void on_buttonreset_clicked();

    void on_buttonconfirm_clicked();

    void read_date();

    void on_newwords_clicked();

private:
    Ui::Widget *ui;
    QSerialPort *serialPort;//添加一个成员
    int chanceleft;
};
#endif // WIDGET_H
