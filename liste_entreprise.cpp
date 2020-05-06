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

liste_entreprise::liste_entreprise(QWidget *parent) : QWidget(parent), ui(new Ui::liste_entreprise)
{
    ui->setupUi(this);

}

liste_entreprise::~liste_entreprise()
{
    delete ui;
}


void liste_entreprise::importer_fichier(){
    std::cout<<"clic !!!"<<std::endl;

    QStringList stringList;
    QFile textFile;

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Text file"), "", tr("Text Files (*.txt)"));
    ui->lblNomFichier->setText(fileName);

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

    while (!in.atEnd()) {

        QString text = in.readLine();
        splitD = text.split("\t");

        v_liste_entreprise.push_back(splitD.at(1));
        //std::cout<< "taille du vecteur avant réduction = " << vector.size ()<<std::endl;
    }


    std::sort( v_liste_entreprise.begin(), v_liste_entreprise.end() );

    v_liste_entreprise.erase( std::unique(v_liste_entreprise.begin(), v_liste_entreprise.end() ), v_liste_entreprise.end() );

    QStringList test = v_liste_entreprise.toList();



    for (QString lol : v_liste_entreprise) {
      std::cout<<lol.toStdString ()<<std::endl;

    }
     ui->lvEntreprises->addItems(test);

}

void liste_entreprise::on_btnSelect_clicked()
{
    this->importer_fichier();
}




void liste_entreprise::on_lvEntreprises_itemClicked(QListWidgetItem *item)
{
     std::cout<<item->text().toStdString ()<<std::endl;
}
