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
    this->ui->leFiltre->setVisible (false);
    this->ui->btnFilter->setVisible (false);
    this->ui->lvEntreprises->setVisible (false);
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
                                                    tr("Open Text file"), "", tr("Text Files (*.txt)"));
    ui->lblNomFichier->setText(fileName);

    this->nom_fichier = fileName;

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
    ui->leFiltre->setVisible (true);
    ui->btnFilter->setVisible (true);
    ui->lvEntreprises->setVisible (true);

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
