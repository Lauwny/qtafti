#ifndef LISTE_ENTREPRISE_H
#define LISTE_ENTREPRISE_H

#include <QWidget>

namespace Ui {
class liste_entreprise;
}

class liste_entreprise : public QWidget
{
    Q_OBJECT

public:
    explicit liste_entreprise(QWidget *parent = nullptr);
    ~liste_entreprise();

    double fRand(double fMin, double fMax)
    {
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    int fRandInt(int fMin, int fMax)
    {
        int f = (int)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

private:
    Ui::liste_entreprise *ui;
};

#endif // LISTE_ENTREPRISE_H
