#include "widget.h"
#include "ui_widget.h"
#include "QMessageBox"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    QStringList serialNamePort;//用来存放所有的串口的名称

    ui->setupUi(this);

    this->setWindowTitle("密码锁");//用来指定标题的内容

    /* 创建一个串口对象 */
    serialPort = new QSerialPort(this);

    /* 搜索所有可用串口 */
    foreach (const QSerialPortInfo &inf0, QSerialPortInfo::availablePorts()) {
       serialNamePort<<inf0.portName();
    }
    ui->serialBox->addItems(serialNamePort);

    this->chanceleft=5;
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_openport_clicked()
{
    /* 串口设置 */
       serialPort->setPortName(ui->serialBox->currentText());//名称
       serialPort->setBaudRate(ui->baudrateBox->currentText().toInt());//波特率
       serialPort->setDataBits(QSerialPort::Data8);//8个数据
       serialPort->setStopBits(QSerialPort::OneStop);//一个停止位
       serialPort->setParity(QSerialPort::NoParity);//没有校验位

       /* 打开串口提示框 */
       if (true == serialPort->open(QIODevice::ReadWrite))
       {
           QMessageBox::information(this, "提示", "串口打开成功");
       }
       else
       {
           QMessageBox::critical(this, "提示", "串口打开失败");
       }
       connect(serialPort,&QSerialPort::readyRead,this,&Widget::read_date);
}



void Widget::on_closeport_clicked()
{
    serialPort->close();
    QMessageBox::information(this,"提示","串口关闭");
}



void Widget::on_button0_clicked()
{
    ui->textsend->insertPlainText("0");
}

void Widget::on_button1_clicked()
{
    ui->textsend->insertPlainText("1");
}

void Widget::on_button2_clicked()
{
    ui->textsend->insertPlainText("2");
}

void Widget::on_button3_clicked()
{
    ui->textsend->insertPlainText("3");
}

void Widget::on_button4_clicked()
{
    ui->textsend->insertPlainText("4");
}

void Widget::on_button5_clicked()
{
    ui->textsend->insertPlainText("5");
}

void Widget::on_button6_clicked()
{
    ui->textsend->insertPlainText("6");
}

void Widget::on_button7_clicked()
{
    ui->textsend->insertPlainText("7");
}

void Widget::on_button8_clicked()
{
    ui->textsend->insertPlainText("8");
}

void Widget::on_button9_clicked()
{
    ui->textsend->insertPlainText("9");
}

void Widget::on_buttonreset_clicked()
{
    ui->textsend->clear();
}

void Widget::on_buttonconfirm_clicked()
{
    QString temp = ui->textsend->toPlainText();
    QByteArray Data_1;
    if(temp.length()!=8){QMessageBox::information(this,"错误","请输入八个数字");ui->textsend->clear();return ;}
    Data_1 = QByteArray::fromHex(temp.toLatin1().data());
    serialPort->write(Data_1);
    ui->textsend->clear();
}

void Widget::read_date(){
    QByteArray buf;
    buf=this->serialPort->readAll();
    QString a;
    a=buf.toHex(' ').trimmed().toUpper();

    if (a=="01"){
        this->chanceleft=5;
        ui->textget->setPlainText("welcome home!");
    }

    else if(a=="02"){
        this->chanceleft=5;
        ui->textget->setPlainText("请输入新密码");

    }
    else if(a=="00"){
        this->chanceleft-=1;
        if(this->chanceleft==4)ui->textget->setPlainText("wrong,you have four chances left to try");
        if(this->chanceleft==3)ui->textget->setPlainText("wrong,you have three chances left to try");
        if(this->chanceleft==2)ui->textget->setPlainText("wrong,you have two chances left to try");
        if(this->chanceleft==1)ui->textget->setPlainText("wrong,you have only one chance left to try");
        if(this->chanceleft==0){
            QString temp="2C2C2C2C";
            QByteArray Data_1;
            Data_1 = QByteArray::fromHex(temp.toLatin1().data());
            serialPort->write(Data_1);
            ui->textsend->clear();
        }
    }
    else if(a=="03")this->close();

}

void Widget::on_newwords_clicked()
{
    QString temp="2B2B2B2B";
    QByteArray Data_1;
    Data_1 = QByteArray::fromHex(temp.toLatin1().data());
    serialPort->write(Data_1);
    ui->textsend->clear();
    ui->textget->setPlainText("请输入旧密码");

}
