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


liste_cours_entreprise::liste_cours_entreprise(societe s, QString fichier,  QWidget *parent) :
    QWidget(parent),
    ui(new Ui::liste_cours_entreprise)
{
    ui->setupUi(this);

    // std::cout<<"nom societe passé au cons = "<<s.getNom_societe ()<<std::endl;


    this->le_nom_entreprise = QString::fromStdString(s.getNom_societe());
    this->le_code_societe = QString::fromStdString(s.getCode_associe_societe ());
    this->le_nom_fichier = fichier;
    this->la_societe = s;
    // std::cout<<"nom societe une fois tranformé = "<<la_societe.getNom_societe ()<<std::endl;
    this->afficher_les_seances();
}

liste_cours_entreprise::~liste_cours_entreprise()
{
    delete ui;
}



//lister cours des entreprises
void liste_cours_entreprise::afficher_les_seances(){

    QString fileName = this->le_nom_fichier;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        std::cout<<false<<std::endl;
    }

    QTextStream in(&file);
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    //std::cout<<in.readAll().toStdString()<<std::endl;
    QGuiApplication::restoreOverrideCursor();

    QVector<seance> v_liste_seances;
    QVector<double> v_max_societe;
    QVector<double> v_min_societe;
    QVector<int> v_nb_seance_societe;

    QStringList splitD;
    QStringList liste_seances;

    ui->lvListeSeance->setColumnCount(6);
    ui->lvListeSeance->setSortingEnabled(false);

    QList<QString> liste_header;
    liste_header << "Date" << "Valeur ouverture" << "Valeur fermeture" << "Minimum" << "Maximum" << "Currency";

    while (!in.atEnd()) {

        QString text = in.readLine();
        if(text.contains(this->le_nom_entreprise)){
            splitD = text.split("\t");

            seance s(splitD.at(2).toStdString(), splitD.at(3).toDouble(), splitD.at(6).toDouble(), splitD.at(5).toDouble(), splitD.at(4).toDouble(), splitD.at(7).toInt(), splitD.at(8).toStdString ());

            v_max_societe.push_back(splitD.at(4).toDouble());
            v_min_societe.push_back(splitD.at(5).toDouble());
            v_nb_seance_societe.push_back(splitD.at(7).toInt());
            v_liste_seances.push_back(s);
        }

        for(seance s : v_liste_seances){

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

        double max_societe = getMaxSociete(v_max_societe);
        double min_societe = getMinSociete(v_min_societe);
        int nb_seance = getNbSeanceSociete (v_nb_seance_societe);

        this->la_societe.setVal_max_societe (max_societe);
        this->la_societe.setVal_min_societe (min_societe);
        this->la_societe.setNb_seances_societe (nb_seance);
        vector<seance> liste_seances_v = std::vector<seance>(v_liste_seances.begin (), v_liste_seances.end ());
        this->la_societe.setListe_seance (liste_seances_v);
        //this->le_nom_entreprise.toStdString (), this->le_code_societe.toStdString (), max_societe, min_societe, nb_seance, std::vector<seance>(v_liste_seances.begin (), v_liste_seances.end ())
    }

    ui->lvListeSeance->setSortingEnabled(true);
}

//click sur le bouton
void liste_cours_entreprise::on_btnShowSeance_clicked()
{
    // std::cout<<"v_seance.size() au clic = "<<this->la_societe.getListe_seance ().size ()<<std::endl;

    companychart *c = new companychart(this->la_societe);
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




