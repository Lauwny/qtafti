#ifndef LISTE_ENTREPRISE_H
#define LISTE_ENTREPRISE_H

#include <QWidget>
#include <QMenu>
#include <QListWidgetItem>
#include <QTextCursor>
#include "liste_cours_entreprise.h"


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


private slots:

    void on_btnSelect_clicked();

    void on_lvEntreprises_itemClicked(QListWidgetItem *item);


    void on_lvEntreprises_cellClicked(int row, int column);


    void onTextChanged();
    void onCursorPositionChanged();

private:

    Ui::liste_entreprise *ui;

    QString nom_fichier;
    QString nom_entreprise;
    QString code_societe;

    static int nb_ouverture;

    enum Colonnes {
        ENTREPRISE
    };

    liste_cours_entreprise *liste_cours;
    QTextCursor m_cursor;

};

#endif // LISTE_ENTREPRISE_H
