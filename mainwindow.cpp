#include<QFileDialog>
#include<QMessageBox>
#include<QTableWidget>
#include<QDebug>
#include<QInputDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvparser.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), uPtr_racerData(new Racerdata)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open CSV File", ".//");

    //Process input file
    uPtr_racerData->extractDataFromCSV(filename);

    uPtr_racerData->processResult();

    uPtr_racerData->declareResult();
#if 0
    QQueue<pair<QString, unsigned int>> displayRESULT = uPtr_racerData->getResultQ()    ;
    QString str = "";
    while(!displayRESULT.isEmpty())
    {
        auto it = displayRESULT.dequeue();

        qDebug()<<"Wineer is "<<it.first<<" "<<it.second<<" ";
        str = str + it.first + " " + QString::number(it.second) + "\n";
    }
    QMessageBox::information(this,"...", str);
#endif
    dilog = new Dialog();
    QQueue<pair<QString, unsigned int>> displayRESULT2 = uPtr_racerData->getResultQ();
    QTableWidget* table = new QTableWidget(dilog);
    table->setRowCount(displayRESULT2.size());
    qDebug()<<" "<<displayRESULT2.size()<<" ";
    table->setColumnCount(2);
    unsigned int qs = displayRESULT2.size();
        for(unsigned int i = 0; i<qs; i++)
        {
            auto it = displayRESULT2.dequeue();
            QTableWidgetItem* item;
            for(unsigned int j = 0; j<3; j++)
            {
                item = new QTableWidgetItem;
                if (j == 0)
                    item->setText(it.first);
                if (j == 1)
                    item->setText(QString::number(it.second));
                table->setItem(i,j,item);
            }
        }
        dilog->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    QString input_text = QInputDialog::getText(this, "asdf","asdfa" );
    auto it = uPtr_racerData->m_racerResult[input_text].begin();
    unsigned int tot_time = 0;

    while(it != uPtr_racerData->m_racerResult[input_text].end())
    {
        tot_time = tot_time + *it;
        it++;
    }

    unsigned int avg_lap_time = tot_time/uPtr_racerData->m_racerResult[input_text].size();
    qDebug()<<avg_lap_time<<" ";

    QMessageBox::information(this,"Total time taken avg.", QString::number(avg_lap_time));
//QMessageBox::information(this,"...", str);

}


