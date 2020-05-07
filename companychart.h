#ifndef COMPANYCHART_H
#define COMPANYCHART_H

#include <QWidget>
#include <QChartView>
#include <QChart>
#include <QGridLayout>
#include <QtWidgets/QWidget>
#include <QtCharts/QPieSeries>
#include <societe.h>

class Qtimer;

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class companychart;
}

class companychart : public QWidget
{
    Q_OBJECT

public:
    explicit companychart(societe s, QWidget *parent = 0);
    ~companychart();

    void explodeSlice(bool exploded);
    void updateRotation();

private:
    Ui::companychart *ui;
    societe la_societe;
    void creer_charte();


};

#endif // COMPANYCHART_H
