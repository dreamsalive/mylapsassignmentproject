#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<csvparser.h>
#include<dialog.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    //void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
    unique_ptr<Racerdata> uPtr_racerData;
    Dialog* dilog;
};
#endif // MAINWINDOW_H
