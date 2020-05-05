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

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Text file"), "", tr("Text Files (*.txt)"));
    ui->lblNomFichier->setText(fileName);
    QFile file(fileName);

    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){


        QTextStream in(&file);
          while (!in.atEnd())
          {
              line = in.readLine();
              //std::cout<<line.toStdString()<<std::endl;
              if (line.contains("ticker") ||
                      line.contains("label") ||
                      line.contains("date") ||
                      line.contains("open") ||
                      line.contains("high") ||
                      line.contains("low") ||
                      line.contains("close") ||
                      line.contains("volume") ||
                      line.contains("currency")){

                  std::cout<<line.toStdString()<<std::endl;

                }else{
                  break;
              }
          file.close();

        }
    file.close();
    }
}

void liste_entreprise::on_btnSelect_clicked()
{
    this->importer_fichier();
}


