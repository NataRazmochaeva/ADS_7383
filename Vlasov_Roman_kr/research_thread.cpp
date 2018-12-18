#include "research_thread.h"
#include "huffmanstatic.h"
#include "huffmandynamic.h"
#include "shennonfano.h"
#include <QMainWindow>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>
QT_CHARTS_USE_NAMESPACE

research_thread::research_thread(QObject *parent) : QObject(parent)
{

}

void research_thread::run()
{
    //Depends on input size
    QSplineSeries *hs1 = new QSplineSeries();
    QSplineSeries *sf1 = new QSplineSeries();
    QSplineSeries *hd1 = new QSplineSeries();
    QSplineSeries *hsop = new QSplineSeries();
    QSplineSeries *sfop = new QSplineSeries();
    QSplineSeries *hdop = new QSplineSeries();
    QSplineSeries *theor1 = new QSplineSeries();


    hs1->setName("Huffman static");
    sf1->setName("Shennon-Fano");
    hd1->setName("Huffman dynamic");
    hsop->setName("Huffman static");
    sfop->setName("Shennon-Fano");
    hdop->setName("Huffman dynamic");
    theor1->setName("Theoretical (n log(n))");

    for (int i = 1000; i >= 1; i/=3)
    {
        std::stringstream ss;
        std::string ans;
        std::string str;
        for (int j = 0; j < (int)(pow(10, 6)/i); j++)
            str.push_back(1 + rand()%127);
        ss << str;
        HuffmanStatic<char>* hufs = new HuffmanStatic<char>(ss, false);
        ans = hufs->abc + hufs->encode(ss);
        hsop->append((int)(pow(10, 6)/i), hufs->getOp());
        hs1->append((int)(pow(10, 6)/i), ans.size());
        ss.clear();
        ans.clear();
        ss << str;
        ShennonFano<char>* shf = new ShennonFano<char>(ss, false);
        ans = shf->abc + shf->encode(ss);
        sf1->append((int)(pow(10, 6)/i), ans.size());
        sfop->append((int)(pow(10, 6)/i), shf->getOp());
        ss.clear();
        ans.clear();
        ss << str;
        HuffmanDynamic<char>* hufd = new HuffmanDynamic<char>();
        ans = hufd->encode(ss);
        hd1->append((int)(pow(10, 6)/i), ans.size());
        hdop->append((int)(pow(10, 6)/i), hufd->getOp());

        delete hufs;
        delete shf;
        delete hufd;
    }
    for (int i = 1; i <= 1000001; i+= 100000)
    {
        theor1->append(i, i*log(i)/log(2));
    }
    QChart *chart1 = new QChart();
    chart1->addSeries(hs1);
    chart1->addSeries(sf1);
    chart1->addSeries(hd1);
    chart1->addSeries(theor1);
    chart1->setTitle("Size of encoded text depending on input size");

    QChart *chartop = new QChart();
    chartop->addSeries(hsop);
    chartop->addSeries(sfop);
    chartop->addSeries(hdop);
    chartop->setTitle("Operations depending on input size");

    QValueAxis *axisX1 = new QValueAxis();
    axisX1->setTitleText("Input text size (characters)");
    axisX1->setLabelFormat("%d");
    chart1->addAxis(axisX1, Qt::AlignBottom);
    hs1->attachAxis(axisX1);
    sf1->attachAxis(axisX1);
    hd1->attachAxis(axisX1);
    QValueAxis *axisY1 = new QValueAxis();
    axisY1->setTitleText("Output text size (characters)");
    axisY1->setLabelFormat("%d");
    chart1->addAxis(axisY1, Qt::AlignLeft);
    hs1->attachAxis(axisY1);
    sf1->attachAxis(axisY1);
    hd1->attachAxis(axisY1);

    QValueAxis *axisXop = new QValueAxis();
    axisXop->setTitleText("Input text size (characters)");
    axisXop->setLabelFormat("%d");
    chartop->addAxis(axisXop, Qt::AlignBottom);
    hsop->attachAxis(axisXop);
    sfop->attachAxis(axisXop);
    hdop->attachAxis(axisXop);
    QValueAxis *axisYop = new QValueAxis();
    axisYop->setTitleText("Operations (times)");
    axisYop->setLabelFormat("%d");
    chartop->addAxis(axisYop, Qt::AlignLeft);
    hsop->attachAxis(axisYop);
    sfop->attachAxis(axisYop);
    hdop->attachAxis(axisYop);

    QChartView *chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);
    QMainWindow *gr1 = new QMainWindow();
    //gr1->resize(1500, 800);
    gr1->setFixedSize(1800, 1000);
    gr1->setWindowTitle("Different input sizes");
    gr1->setCentralWidget(chartView1);
    gr1->show();
    QChartView *chartViewop = new QChartView(chartop);
    chartViewop->setRenderHint(QPainter::Antialiasing);
    QMainWindow *grop = new QMainWindow();
    //gr1->resize(1500, 800);
    grop->setFixedSize(1800, 1000);
    grop->setWindowTitle("Amount of operations");
    grop->setCentralWidget(chartViewop);
    grop->show();

    //Depends on alphabet size (500 characters)
    QSplineSeries *hs2 = new QSplineSeries();
    QSplineSeries *sf2 = new QSplineSeries();
    QSplineSeries *hd2 = new QSplineSeries();

    hs2->setName("Huffman static");
    sf2->setName("Shennon-Fano");
    hd2->setName("Huffman dynamic");


    for (int i = 1; i < 8; i++)
    {
        std::stringstream ss;
        std::string ans;
        std::string str;
        for (int j = 0; j < 500; j++)
            str.push_back(1 + rand()%(int)pow(2, i));
        ss << str;
        HuffmanStatic<char>* hufs = new HuffmanStatic<char>(ss, false);
        ans = hufs->abc + hufs->encode(ss);
        hs2->append((int)pow(2, i), ans.size());
        ss.clear();
        ans.clear();
        ss << str;
        ShennonFano<char>* shf = new ShennonFano<char>(ss, false);
        ans = shf->abc + shf->encode(ss);
        sf2->append((int)pow(2, i), ans.size());
        ss.clear();
        ans.clear();
        ss << str;
        HuffmanDynamic<char>* hufd = new HuffmanDynamic<char>();
        ans = hufd->encode(ss);
        hd2->append((int)pow(2, i), ans.size());

        delete hufs;
        delete shf;
        delete hufd;
    }

    QChart *chart2 = new QChart();
    chart2->addSeries(hs2);
    chart2->addSeries(sf2);
    chart2->addSeries(hd2);
    chart2->setTitle("Size of encoded text depending on alphabet size (500 characters)");

    QValueAxis *axisX2 = new QValueAxis();
    axisX2->setTitleText("Input alphabet size (characters)");
    axisX2->setLabelFormat("%d");
    chart2->addAxis(axisX2, Qt::AlignBottom);
    hs2->attachAxis(axisX2);
    sf2->attachAxis(axisX2);
    hd2->attachAxis(axisX2);
    QValueAxis *axisY2 = new QValueAxis();
    axisY2->setTitleText("Output text size (characters)");
    axisY2->setLabelFormat("%d");
    chart2->addAxis(axisY2, Qt::AlignLeft);
    hs2->attachAxis(axisY2);
    sf2->attachAxis(axisY2);
    hd2->attachAxis(axisY2);

    QChartView *chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);
    QMainWindow *gr2 = new QMainWindow();
    //gr2->resize(1920, 1080);
    gr2->setFixedSize(1800, 1000);
    gr2->setWindowTitle("Different alphabet sizes");
    gr2->setCentralWidget(chartView2);
    gr2->show();

    //Depends on alphabet size (1500 characters)
    QSplineSeries *hs3 = new QSplineSeries();
    QSplineSeries *sf3 = new QSplineSeries();
    QSplineSeries *hd3 = new QSplineSeries();

    hs3->setName("Huffman static");
    sf3->setName("Shennon-Fano");
    hd3->setName("Huffman dynamic");


    for (int i = 1; i < 8; i++)
    {
        std::stringstream ss;
        std::string ans;
        std::string str;
        for (int j = 0; j < 1500; j++)
            str.push_back(1 + rand()%(int)pow(2, i));
        ss << str;
        HuffmanStatic<char>* hufs = new HuffmanStatic<char>(ss, false);
        ans = hufs->abc + hufs->encode(ss);
        hs3->append((int)pow(2, i), ans.size());
        ss.clear();
        ans.clear();
        ss << str;
        ShennonFano<char>* shf = new ShennonFano<char>(ss, false);
        ans = shf->abc + shf->encode(ss);
        sf3->append((int)pow(2, i), ans.size());
        ss.clear();
        ans.clear();
        ss << str;
        HuffmanDynamic<char>* hufd = new HuffmanDynamic<char>();
        ans = hufd->encode(ss);
        hd3->append((int)pow(2, i), ans.size());

        delete hufs;
        delete shf;
        delete hufd;
    }

    QChart *chart3 = new QChart();
    chart3->addSeries(hs3);
    chart3->addSeries(sf3);
    chart3->addSeries(hd3);
    chart3->setTitle("Size of encoded text depending on alphabet size (1500 characters)");

    QValueAxis *axisX3 = new QValueAxis();
    axisX3->setTitleText("Input alphabet size (characters)");
    axisX3->setLabelFormat("%d");
    chart3->addAxis(axisX3, Qt::AlignBottom);
    hs3->attachAxis(axisX3);
    sf3->attachAxis(axisX3);
    hd3->attachAxis(axisX3);
    QValueAxis *axisY3 = new QValueAxis();
    axisY3->setTitleText("Output text size (characters)");
    axisY3->setLabelFormat("%d");
    chart3->addAxis(axisY3, Qt::AlignLeft);
    hs3->attachAxis(axisY3);
    sf3->attachAxis(axisY3);
    hd3->attachAxis(axisY3);

    QChartView *chartView3 = new QChartView(chart3);
    chartView3->setRenderHint(QPainter::Antialiasing);
    QMainWindow *gr3 = new QMainWindow();
    //gr2->resize(1920, 1080);
    gr3->setFixedSize(1800, 1000);
    gr3->setWindowTitle("Different alphabet sizes");
    gr3->setCentralWidget(chartView3);
    gr3->show();

    while(gr1->isVisible() || gr2->isVisible() || gr3->isVisible() || grop->isVisible())
    {
        ;
    }
    emit finished();
}
