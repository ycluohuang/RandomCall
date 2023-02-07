#ifndef WIDDGET_H
#define WIDDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class widdget; }
QT_END_NAMESPACE

class widdget : public QMainWindow
{
    Q_OBJECT

public:
    widdget(QWidget *parent = nullptr);
    ~widdget();
    void setFontName();
    void fileimport();

private slots:
    void switchpushbtn_clicked();
    void switchTime_out();

private:
    Ui::widdget *ui;
    QTimer *switchTime;
    int cnt = 0;
    QStringList strListImport;
    bool switchbtnFlag = false;
};
#endif // WIDDGET_H
