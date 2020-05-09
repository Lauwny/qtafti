#ifndef LISTE_COURS_ENTREPRISE_H
#define LISTE_COURS_ENTREPRISE_H
#include <iostream>
#include <QWidget>
#include <QTextStream>
#include <QListWidgetItem>
#include <vector>
#include <societe.h>

namespace Ui {
class liste_cours_entreprise;
}

class liste_cours_entreprise : public QWidget
{
    Q_OBJECT

public:
    explicit liste_cours_entreprise(societe s,  QWidget *parent = nullptr);
    ~liste_cours_entreprise();

    QString le_nom_societe;
    QString le_code_societe;
    double le_min_societe;
    double le_max_societe;
    int le_nb_seance_societe;
    vector<seance> les_seance_societe;

    QString getLe_nom_fichier() const;
    void setLe_nom_fichier(const QString &value);

    QString getLe_nom_entreprise() const;
    void setLe_nom_entreprise(const QString &value);

    void afficher_la_seance();
    void afficher_les_seances();


private:
    Ui::liste_cours_entreprise *ui;

    societe la_societe;

    enum Colonnes
    {
        DATE,
        V_O,
        V_F,
        MIN,
        MAX,
        CURRENCY
    };

    double getMaxSociete(QVector<double> v_liste_max);
    double getMinSociete(QVector<double> v_liste_min);
    int getNbSeanceSociete(QVector<int> v_liste_seance);


private slots:
    void on_btnShowSeance_clicked();

};

#endif // LISTE_COURS_ENTREPRISE_H
