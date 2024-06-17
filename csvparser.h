#ifndef CSVPARSER_H
#define CSVPARSER_H
#include<iostream>
#include<string>
#include<sstream>
#include<map>
#include<vector>
#include<queue>
#include<utility>
#include<QString>
#include<QQueue>

using namespace std;
class Racerdata
{
public:

    QString m_filename;
    QMap<QString, QVector<QPair<QString, unsigned int>>> m_racerdata;
    QMap<QString, QVector<unsigned int>> m_racerResult;
    QQueue<pair<QString, unsigned int>> m_resultQ;
    explicit Racerdata();
    void extractDataFromCSV(QString filename);
    unsigned int converttime( QString* str);
    unsigned int processResult();
    unsigned int declareResult();
    QQueue<pair<QString, unsigned int>> getResultQ();
    map<QString, vector<unsigned int>>  m_fastestlapwinner_mp;
    map<QString, vector<unsigned int>> m_race;
    struct mycomparator
    {
        bool operator()(pair<QString,unsigned int>& a, pair<QString, unsigned int>& b)
        {
            return a.second > b.second;
        }
    };
    priority_queue<pair<QString, unsigned int>, vector<pair<QString,unsigned int>>, mycomparator> m_fastest;

    queue<pair<QString, unsigned int>> m_laggers;

};
#endif // CSVPARSER_H
