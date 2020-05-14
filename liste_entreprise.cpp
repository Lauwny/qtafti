#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "liste_entreprise.h"
#include "ui_liste_entreprise.h"
#include "seance.h"
#include "societe.h"
#include "vector"



liste_entreprise::liste_entreprise(QWidget *parent) : QWidget(parent), ui(new Ui::liste_entreprise)
{
    ui->setupUi(this);
    ui->leFiltre->setReadOnly (true);
    ui->btnFilter->setEnabled (false);

}

liste_entreprise::~liste_entreprise()
{
    delete ui;
}

void liste_entreprise::importer_fichier(){


    ui->lvEntreprises->setColumnCount(1);
    ui->lvEntreprises->setSortingEnabled(false);

    QStringList stringList;
    QFile textFile;

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Selectionnez un fichier à ouvrir"), "", tr("Text Files (*.txt)"));
    ui->lblNomFichier->setText(fileName);

    this->nom_fichier = fileName;

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Impossible d'ouvrir le fichier %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        std::cout<<false<<std::endl;
    }

    QTextStream in(&file);
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QGuiApplication::restoreOverrideCursor();
    QVector<QString> v_liste_entreprise;
    QStringList splitD;

    QString text;

    while (!in.atEnd()) {
        text = in.readLine();
        splitD = text.split("\t");

        v_liste_entreprise.push_back(splitD.at(1));
    }

    v_liste_entreprise.erase( std::unique(v_liste_entreprise.begin(), v_liste_entreprise.end() ), v_liste_entreprise.end() );

    this->code_societe =  text.split('\t').at(0);
    QList<QString> liste_header;
    liste_header << "Nom de l'entreprise";


    for(QString societe : v_liste_entreprise){
        if(societe == "label"){
            continue;
        }else{
            ui->lvEntreprises->setHorizontalHeaderLabels(liste_header);
            ui->lvEntreprises->insertRow(ui->lvEntreprises->rowCount());
            int fila = ui->lvEntreprises->rowCount () - 1;
            ui->lvEntreprises->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


            QTableWidgetItem *entreprise  = new QTableWidgetItem(societe);
            entreprise->setFlags(entreprise->flags() ^ Qt::ItemIsEditable);
            ui->lvEntreprises->setItem(fila, ENTREPRISE, entreprise);
        }
    }


    ui->lvEntreprises->setSortingEnabled(true);
    ui->leFiltre->setReadOnly(false);
    ui->btnFilter->setEnabled (true);
}

void liste_entreprise::on_btnSelect_clicked()
{
    this->importer_fichier();
}


void liste_entreprise::on_btnFilter_clicked()
{
    QString filter = ui->leFiltre->text();
    for( int i = 0; i < ui->lvEntreprises->rowCount(); ++i )
    {
        bool match = false;
        for( int j = 0; j < ui->lvEntreprises->columnCount(); ++j )
        {
            QTableWidgetItem *item = ui->lvEntreprises->item( i, j );
            if( item->text().contains(filter) || item->text().contains(filter.toUpper ()) || item->text().contains(filter.toLower ())  )
            {
                match = true;
                break;
            }
        }
        ui->lvEntreprises->setRowHidden( i, !match );
    }
}

void liste_entreprise::on_lvEntreprises_cellClicked(int row, int column)
{

    this->nom_entreprise = ui->lvEntreprises->item(row,column)->text ();
    QVector<seance> v_liste_seances;
    QVector<double> v_max_societe;
    QVector<double> v_min_societe;
    QVector<int> v_nb_seance_societe;
    QString fileName = this->nom_fichier;
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
    QGuiApplication::restoreOverrideCursor();
    QVector<QString> v_liste_entreprise;
    QStringList splitD;


    while (!in.atEnd()) {
        QString text = in.readLine();
        if(text.contains(this->nom_entreprise)){

            splitD = text.split("\t");

            seance s(splitD.at(2).toStdString(), splitD.at(3).toDouble(), splitD.at(6).toDouble(), splitD.at(5).toDouble(), splitD.at(4).toDouble(), splitD.at(7).toInt(), splitD.at(8).toStdString ());
            v_max_societe.push_back(splitD.at(4).toDouble());
            v_min_societe.push_back(splitD.at(5).toDouble());
            v_nb_seance_societe.push_back(splitD.at(7).toInt());
            v_liste_seances.push_back(s);
        }else{
//            QMessageBox::warning(this, tr("MDI"),
//                                 tr("Aucune entreprise ne correspond à votre recherche"));
//            ui->lvEntreprises->setRowHidden(NULL, NULL);
        }
    }

    double max_societe = getMaxSociete(v_max_societe);
    double min_societe = getMinSociete(v_min_societe);
    int nb_seance = getNbSeanceSociete (v_nb_seance_societe);


    vector<seance> liste_seances_v = std::vector<seance>(v_liste_seances.begin (), v_liste_seances.end ());



    societe *s = new societe(this->nom_entreprise.toStdString (), this->code_societe.toStdString (), max_societe, min_societe, nb_seance, liste_seances_v);

    //    companychart *c = new companychart(this->la_societe);

    liste_cours_entreprise *lse = new liste_cours_entreprise(*s);
    lse->show();
}

////return max de la valeur de la société
double liste_entreprise::getMaxSociete(QVector<double> v_liste_max)
{
    return *max_element(v_liste_max.begin(), v_liste_max.end());
}

////return min de la valeur de la société
double liste_entreprise::getMinSociete(QVector<double> v_liste_min)
{
    return *min_element(v_liste_min.begin(), v_liste_min.end());
}

////return l'addition du nombre de séances
int liste_entreprise::getNbSeanceSociete(QVector<int> v_liste_seance)
{
    int sum_of_elems;

    sum_of_elems = std::accumulate(v_liste_seance.begin(), v_liste_seance.end(), 0);

    return sum_of_elems;
}
