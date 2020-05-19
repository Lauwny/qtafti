#include <iostream>
#include "companychart.h"
#include "ui_companychart.h"
#include <societe.h>
#include <seance.h>
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

    std::cout<<"la societe name = "<<this->la_societe.getNom_societe ()<<std::endl;
    this->creer_charte ();

}

companychart::~companychart()
{
    delete ui;
}

void companychart::creer_charte (){

    setMinimumSize(800, 600);
    QLineSeries *series = new QLineSeries();

    QDateTime momentInTime;
    QDate qd_date;
    std::cout<<"taille du vecteur = "<<this->la_societe.getListe_seance().size()<<std::endl;
    //QVector<seance> v_seance  = QVector<seance>(this->la_societe.getListe_seance().begin(), this->la_societe.getListe_seance().end());

    //ça bug ici
    QVector<seance> v_seance  = QVector<seance>::fromStdVector (this->la_societe.getListe_seance());
    for(seance seance : v_seance){
        std::cout<<"eance.getDate_seance () = "<<seance.getDate_seance ()<<std::endl;
        QString qs_date_string = QString::fromStdString (seance.getDate_seance ());
        std::cout<<"qs_date_string = "<<qs_date_string.toStdString ()<<std::endl;
        qd_date = QDate::fromString(qs_date_string,"dd/MM/yyyy");
        std::cout<<"qd_date= "<<qd_date.toString ().toStdString ()<<std::endl;
        momentInTime.setDate(qd_date);
        series->append(momentInTime.toMSecsSinceEpoch(), seance.getValeur_maximal_seance());
    }

    QFile sunSpots("/Users/corentin/Downloads/RecentIndices.txt");
    if (!sunSpots.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout<<"immeuble en verre"<<std::endl;
    }



    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle(QString::fromStdString(this->la_societe.getNom_societe()));

    //----axe du bas----//
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(25);
    axisX->setFormat("dd/MM/yy"); //07/08/20
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    //----axe qui monte----//
    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Valeur maximum atteinte");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    series->show ();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);


    //    chart->setAnimationOptions(QChart::AllAnimations);


    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView, 1, 1);
    setLayout(mainLayout);

    QMessageBox msgBox;
    msgBox.setText("Tips : ");
    msgBox.setInformativeText("Pour zoomer : clique gauche et laisser glisser sur le groupe de date voulue. \n Pour dezoomer, clique droit.");
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
}

