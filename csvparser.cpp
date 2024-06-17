#include<QString>
#include<QStringList>
#include<QTextStream>
#include<QFile>
#include<QDebug>
#include<QQueue>
#include <csvparser.h>

#define HOUR_IN_SECS 3600
#define MINT_IN_SECS 60

using namespace std;
Racerdata::Racerdata()
{

}

void Racerdata::extractDataFromCSV(QString filename)
{
    QFile csvfile(filename);
    if(csvfile.open(QFile::ReadOnly))
    {
        QTextStream s1(&csvfile);
        unsigned int count = 0;
        while (!s1.atEnd())
        {
            if (count == 0)
            {
                count++;
                s1.readLine();
            }
            else
            {
                QString s=s1.readLine();
                QStringList listofcols = s.split(",");
                QString* mystr = new QString(listofcols.at(1));
                unsigned int time_in_secs = converttime(mystr);
                m_racerdata[listofcols.at(0)].push_back((make_pair(listofcols.at(1),time_in_secs)));
            }
        }
    }
}

unsigned int Racerdata::converttime(QString* str)
{
    QTextStream row(str);
    QString line = row.readLine();
    QStringList mylist = line.split(":");
    unsigned int hr_in_sec = (mylist.at(0).toInt())*HOUR_IN_SECS;
    unsigned int mint_in_secs = (mylist.at(1).toInt())*MINT_IN_SECS;
    unsigned int secs = mylist.at(2).toInt();
    unsigned int total_time_in_sec = hr_in_sec + mint_in_secs + secs;
    return total_time_in_sec;
}

unsigned int Racerdata::processResult()
{
    for(auto it = m_racerdata.begin(); it !=m_racerdata.end(); it++)
    {
        qDebug()<<"Driver Name -> "<<it.key()<<" ";
        auto itl = it.value().begin();
        auto itr = it.value().begin();
        itr++;
        unsigned int totalTimeTakenByRacer = 0;
        while(itr != it.value().end())
        {
            unsigned int diff_time = itr->second - itl->second;
            m_racerResult[it.key()].push_back( diff_time);
            totalTimeTakenByRacer = totalTimeTakenByRacer + diff_time;
            itl++;
            itr++;
        }
        m_fastest.push(make_pair(it.key(), totalTimeTakenByRacer));
    }
    return 0;
}

unsigned int Racerdata::declareResult()
{
    auto it = m_fastest.top();
    unsigned int fastest_time = it.second;

    m_resultQ.enqueue(make_pair(it.first, it.second));
    m_fastest.pop();
    while(!m_fastest.empty())
    {
        auto it = m_fastest.top();
        m_resultQ.enqueue(make_pair(it.first, it.second - fastest_time));
        m_fastest.pop();

    }
    return 0;
}

QQueue<pair<QString, unsigned int>> Racerdata::getResultQ()
{
    return m_resultQ;
}

