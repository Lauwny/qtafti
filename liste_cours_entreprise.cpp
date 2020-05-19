#include "liste_cours_entreprise.h"
#include "ui_liste_cours_entreprise.h"
#include "seance.h"
#include "societe.h"
#include "companychart.h"
#include "vector"
#include<iostream>
#include<QListWidgetItem>
#include <QFile>
#include <QMessageBox>
#include <numeric>
#include <QList>
#include <QDebug>
#include <regex>


liste_cours_entreprise::liste_cours_entreprise(societe s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::liste_cours_entreprise)
{
    ui->setupUi(this);
    //std::cout<<"nom societe passé au cons = "<<s.getNom_societe ()<<std::endl;


    this->le_nom_societe = QString::fromStdString(s.getNom_societe());
    this->le_code_societe = QString::fromStdString(s.getCode_associe_societe ());
    this->le_max_societe = s.getVal_max_societe ();
    this->le_min_societe = s.getVal_min_societe ();
    this->le_nb_seance_societe = s.getNb_seances_societe ();
    this->les_seance_societe =  s.getListe_seance ();
    this->afficher_les_seances();
}

liste_cours_entreprise::~liste_cours_entreprise()
{
    delete ui;
}



//lister cours des entreprises
void liste_cours_entreprise::afficher_les_seances(){



    QStringList splitD;
    QStringList liste_seances;

    ui->lvListeSeance->setColumnCount(6);
    ui->lvListeSeance->setSortingEnabled(false);

    QList<QString> liste_header;
    liste_header << "Date" << "Valeur ouverture" << "Valeur fermeture" << "Minimum" << "Maximum" << "Currency";


    for(seance s : this->les_seance_societe){

        ui->lvListeSeance->setHorizontalHeaderLabels(liste_header);
        ui->lvListeSeance->insertRow(ui->lvListeSeance->rowCount());
        int fila = ui->lvListeSeance->rowCount () - 1;

        QTableWidgetItem *date  = new QTableWidgetItem(QString::fromStdString(s.getDate_seance ()));
        date->setFlags(date->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *v_o  = new QTableWidgetItem(QString::number(s.getValeur_ouverture_seance()));
        v_o->setFlags(v_o->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *v_f = new QTableWidgetItem(QString::number(s.getValeur_fermeture_seance ()));
        v_f->setFlags(v_f->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *min  = new QTableWidgetItem(QString::number(s.getValeur_minimal_seance ()));
        min->setFlags(min->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *max  = new QTableWidgetItem(QString::number(s.getValeur_maximal_seance ()));
        max->setFlags(max->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *currency  = new QTableWidgetItem(QString::fromStdString(s.getMonnaie_seance ()));
        currency->setFlags(currency->flags() ^ Qt::ItemIsEditable);

        ui->lvListeSeance->setItem(fila, DATE, date);
        ui->lvListeSeance->setItem(fila, V_O, v_o);
        ui->lvListeSeance->setItem(fila, V_F,v_f);
        ui->lvListeSeance->setItem(fila, MIN, min);
        ui->lvListeSeance->setItem(fila, MAX, max);
        ui->lvListeSeance->setItem(fila, CURRENCY, currency);

    }

    this->la_societe.setNom_societe(this->le_nom_societe.toStdString ());
    this->la_societe.setCode_associe_societe(this->le_code_societe.toStdString ());
    this->la_societe.setVal_max_societe (this->le_max_societe);
    this->la_societe.setVal_min_societe (this->le_min_societe);
    this->la_societe.setNb_seances_societe (this->le_nb_seance_societe);
    this->la_societe.setListe_seance (this->les_seance_societe);
    //this->le_nom_entreprise.toStdString (), this->le_code_societe.toStdString (), max_societe, min_societe, nb_seance, std::vector<seance>(v_liste_seances.begin (), v_liste_seances.end ())


    ui->lvListeSeance->setSortingEnabled(true);
}

//click sur le bouton
void liste_cours_entreprise::on_btnShowSeance_clicked()
{

    companychart *c = new companychart(this->la_societe);
    //std::cout<<"nom societe = "<<this->la_societe.getNom_societe ()<<std::endl;
    c->show ();
}


////return max de la valeur de la société
double liste_cours_entreprise::getMaxSociete(QVector<double> v_liste_max)
{
    return *max_element(v_liste_max.begin(), v_liste_max.end());
}

////return min de la valeur de la société
double liste_cours_entreprise::getMinSociete(QVector<double> v_liste_min)
{
    return *min_element(v_liste_min.begin(), v_liste_min.end());
}

////return l'addition du nombre de séances
int liste_cours_entreprise::getNbSeanceSociete(QVector<int> v_liste_seance)
{
    int sum_of_elems;

    sum_of_elems = std::accumulate(v_liste_seance.begin(), v_liste_seance.end(), 0);

    return sum_of_elems;
}




