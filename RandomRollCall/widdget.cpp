#include "widdget.h"
#include "ui_widdget.h"
#include <QFileDialog>
#include <QTextStream>
#include <QTime>
#include <QMessageBox>
#include <QDebug>
#include <cstdlib>

widdget::widdget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::widdget)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("随机点名v0.1"));
    this->setFixedSize(600,300);
//    widdget::setFontName();
    QFont ft("楷书",24,40);//字体，字号，加粗规格(50%正常)
    QPalette flabelcolor;
//    ft.setPointSize(30);
    flabelcolor.setColor(QPalette::WindowText,Qt::red);
    ui->Firstlabel->setPalette(flabelcolor);
    ui->Firstlabel->setFont(ft);

//    QTime timenow = QTime::currentTime();
    srand((unsigned)time(NULL));
    switchTime = new QTimer();
//  读入文件
    fileimport();
//  连接各个槽
    this->connect(ui->switchpushbtn,SIGNAL(clicked(bool)),this,SLOT(switchpushbtn_clicked()));
    this->connect(switchTime,SIGNAL(timeout()),this,SLOT(switchTime_out()));

}

void widdget::setFontName()
{
    QFont ft("楷书",26,60);
    QPalette flabelcolor;
    ft.setPointSize(35);
    flabelcolor.setColor(QPalette::WindowText,Qt::red);
    ui->Firstlabel->setPalette(flabelcolor);
    ui->Firstlabel->setFont(ft);
}

void widdget::switchpushbtn_clicked()
{
    if(cnt == 0)QMessageBox::information(this,tr("打开name.txt文件夹失败或文件夹内无名字！"),tr("请检查！"));
    else
    {
        switchbtnFlag = !switchbtnFlag;
        if(switchbtnFlag)
        {
            ui->switchpushbtn->setText("停止");
            switchTime->start(60);
        }
        else
        {
            ui->switchpushbtn->setText("开始");
            switchTime->stop();
        }
    }
}


void widdget::switchTime_out()
{
    setFontName();
    int test = rand()%cnt;
    ui->Firstlabel->setText(strListImport.at(test));
    qDebug() << test << Qt::endl;
}

void widdget::fileimport() // 读入当前文件夹的名字文件
{
//    QString filename = "C:\\Users\\luo_huang\\Desktop\\project_1\\QT\\RandomRollCall_luohuang\\name.txt";
//    QString filename = QFileDialog::getOpenFileName(this);
    QString filename = "./name.txt";//或.\\name.txt
    if(filename.isEmpty())
    {
        QMessageBox::information(this,tr("提示："),tr("导入失败，请检查格式是否正确！"));
    }
    else
    {
        QFile tmpfile(filename);
        if(tmpfile.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QTextStream Textstream(&tmpfile);//这里是打开tmp文件才对
            while(!Textstream.atEnd())
            {
                QString linecontent = Textstream.readLine();
                if(!linecontent.isEmpty())
                {
                    strListImport.append(linecontent);
                    cnt++;
                }
            }
//            QMessageBox::information(this,tr("提示："),tr("您已成功导入%1个名字！").arg(cnt));OK
            QMessageBox::information(this,tr("提示："),tr("导入成功！！共%1个名字").arg(cnt));
//            QMessageBox::information(this,tr("提示："),tr("导入成功！！！"),tr("共%1个名字").arg(cnt)); 不行
        }
        else QMessageBox::information(this,tr("提示："),tr("该目录下不存在name.txt文件，请检查！！"));
    }
}
widdget::~widdget()
{
    delete ui;
}
