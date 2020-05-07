#include <iostream>
#include "liste_entreprise.h"
#include "ui_liste_entreprise.h"
#include "seance.h"
#include "societe.h"
#include "vector"


#include "QStringListModel"
#include "QListWidget"
#include "QToolBar"
#include "QFileDialog"
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <fstream>
#include <QMessageBox>
#include <QList>
#include <QListWidget>
#include <QTableWidgetItem>

liste_entreprise::liste_entreprise(QWidget *parent) : QWidget(parent), ui(new Ui::liste_entreprise)
{
    ui->setupUi(this);
    connect(ui->teFiltre, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    connect(ui->teFiltre, SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChanged()));
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
    //std::cout<<in.readAll().toStdString()<<std::endl;
    QGuiApplication::restoreOverrideCursor();

    QVector<QString> v_liste_entreprise;
    QStringList splitD;

    QString text;

    while (!in.atEnd()) {

        text = in.readLine();
        splitD = text.split("\t");

        v_liste_entreprise.push_back(splitD.at(1));

    }

    this->code_societe =  text.split('\t').at(0);

    QList<QString> liste_header;
    liste_header << "Nom de l'entreprise";

    v_liste_entreprise.erase( std::unique(v_liste_entreprise.begin(), v_liste_entreprise.end() ), v_liste_entreprise.end() );

    for(QString societe : v_liste_entreprise){

        //std::cout<<"vecteur "<<societe.toStdString ()<<std::endl;
        if(societe == "label"){
            continue;
        }else{
            ui->lvEntreprises->setHorizontalHeaderLabels(liste_header);
            ui->lvEntreprises->insertRow(ui->lvEntreprises->rowCount());
            int fila = ui->lvEntreprises->rowCount () - 1;
            std::cout<<"ui->lvEntreprises->rowCount() =  "<<ui->lvEntreprises->rowCount()<<std::endl;
            ui->lvEntreprises->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


            QTableWidgetItem *entreprise  = new QTableWidgetItem(societe);
            entreprise->setFlags(entreprise->flags() ^ Qt::ItemIsEditable);
            ui->lvEntreprises->setItem(fila, ENTREPRISE, entreprise);
        }
    }


        ui->lvEntreprises->setSortingEnabled(true);

}

void liste_entreprise::on_btnSelect_clicked()
{

    this->importer_fichier();
}




void liste_entreprise::on_lvEntreprises_itemClicked(QListWidgetItem *item)
{



}

void liste_entreprise::on_lvEntreprises_cellClicked(int row, int column)
{

    QTableWidgetItem *item = new QTableWidgetItem;
    item = ui->lvEntreprises->item(row,column);
    this->nom_entreprise = item->text();
    std::cout<<"nom entreprise : "<<this->nom_entreprise.toStdString ()<<std::endl;

    societe s(nom_entreprise.toStdString (), code_societe.toStdString());

    liste_cours = new liste_cours_entreprise(s, nom_fichier);
    liste_cours->show();
}

void liste_entreprise::onTextChanged()
{
        for( int i = 0; i < ui->lvEntreprises->rowCount(); ++i )
        {
            bool match = false;
            for( int j = 0; j < ui->lvEntreprises->columnCount(); ++j )
            {
                QTableWidgetItem *item = ui->lvEntreprises->item( i, j );
                if( item->text().contains('AC') )
                {
                    match = true;
                    break;
                }
            }
            ui->lvEntreprises->setRowHidden( i, !match );
        }

}

void liste_entreprise::onCursorPositionChanged()
{
    // Code that executes on cursor change here
    m_cursor = ui->teFiltre->textCursor();
}




