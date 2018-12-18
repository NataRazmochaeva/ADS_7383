#ifndef RESEARCH_THREAD_H
#define RESEARCH_THREAD_H

#include <QObject>
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>
class research_thread : public QObject
{
    Q_OBJECT

    public:
        explicit research_thread(QObject *parent = nullptr);

    signals:
        void finished();

    public slots:
        void run();
};

#endif // RESEARCH_THREAD_H
