#include <iostream>
#include "companychart.h"
#include "ui_companychart.h"
#include <QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCore/QDateTime>
#include <QtCharts/QDateTimeAxis>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtCharts/QValueAxis>

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCore/QRandomGenerator>
#include <QtWidgets/QGridLayout>
#include <QtCore/QTimer>
#include <societe.h>

using namespace QtCharts;

companychart::companychart(societe s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::companychart)
{
    ui->setupUi(this);
    ui->gvChart->setVisible (false);
    this->creer_charte ();
    this->la_societe = s;
    //    std::cout<<"la societe = "<<this->la_societe ().getNom_societe ()<<std::endl;
}

companychart::~companychart()
{
    delete ui;
}

void companychart::creer_charte (){

    setMinimumSize(800, 600);
    QLineSeries *series = new QLineSeries();
    //    QString fileName = QFileDialog::getOpenFileName(this,
    //                                                    tr("Open Text file"), "", tr("Text Files (*.txt)"));
    QFile file("/Users/corentin/Documents/C++/QT/projetafti/RecentIndices.txt");
    // QFile sunSpots("/Users/corentin/Documents/C++/QT/projetafti/RecentIndices.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout<<"pas ouverte"<<std::endl;
    }

    QTextStream stream(&file);
    while (!stream.atEnd()) {

        QString line = stream.readLine();
        if (line.startsWith("#") || line.startsWith(":"))
            continue;
        QStringList values = line.split(" ", QString::SkipEmptyParts);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(values[0].toInt(), values[1].toInt() , 15));
        series->append(momentInTime.toMSecsSinceEpoch(), values[2].toDouble());
    }
    file.close();

    QChart *chart = new QChart();
    std::cout<<"10-bis"<<std::endl;
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Sunspots count (by Space Weather Prediction Center)");
    std::cout<<"11"<<std::endl;
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    std::cout<<"12"<<std::endl;
    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Sunspots count");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    std::cout<<"13"<<std::endl;

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    //    chart->setAnimationOptions(QChart::AllAnimations);


    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView, 1, 1);
    setLayout(mainLayout);
}

