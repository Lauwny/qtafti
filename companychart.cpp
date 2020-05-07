#include <iostream>
#include "companychart.h"
#include "ui_companychart.h"
#include <societe.h>
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
#include <QVector>


using namespace QtCharts;

companychart::companychart(societe s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::companychart)
{
    ui->setupUi(this);
    ui->gvChart->setVisible (false);
    this->la_societe = s;
    this->creer_charte ();
    //    std::cout<<"la societe = "<<this->la_societe ().getNom_societe ()<<std::endl;
}

companychart::~companychart()
{
    delete ui;
}

void companychart::creer_charte (){


    setMinimumSize(800, 600);
    QLineSeries *series = new QLineSeries();

    QDateTime momentInTime;


    QVector<seance> v_seance  = QVector<seance>::fromStdVector (this->la_societe.getListe_seance());
    for(seance seance : v_seance){
        //std::cout<<"v_seance = "<<seance.getDate_seance ()<<std::endl;
        QString qs_date_string = QString::fromStdString (seance.getDate_seance ());
        std::cout<<"qs_date = "<<qs_date_string.toStdString ()<<std::endl;
        QDate qd_date = QDate::fromString(qs_date_string,"dd/MM/yyyy");
        momentInTime.setDate(qd_date);
        series->append(momentInTime.toMSecsSinceEpoch(), seance.getValeur_maximal_seance());


    }




    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle(QString::fromStdString(this->la_societe.getNom_societe()));
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy ");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Prix du cours");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    //    chart->setAnimationOptions(QChart::AllAnimations);


    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView, 1, 1);
    setLayout(mainLayout);
}

