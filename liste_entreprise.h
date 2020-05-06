#ifndef LISTE_ENTREPRISE_H
#define LISTE_ENTREPRISE_H

#include <QWidget>
#include <QMenu>

namespace Ui {
class liste_entreprise;
}

class liste_entreprise : public QWidget
{
    Q_OBJECT

public:
    liste_entreprise(QWidget *parent = nullptr);
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

    void importer_fichier();

    void traiter_ligne(QString texte);


private slots:

    void on_btnSelect_clicked();

private:

    Ui::liste_entreprise *ui;

};

#endif // LISTE_ENTREPRISE_H
