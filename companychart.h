#ifndef COMPANYCHART_H
#define COMPANYCHART_H

#include <QWidget>


namespace Ui {
class companychart;
}

class companychart : public QWidget
{
    Q_OBJECT

public:
    explicit companychart(QWidget *parent = nullptr);
    ~companychart();

private:
    Ui::companychart *ui;
    void creer_charte();
};

#endif // COMPANYCHART_H
