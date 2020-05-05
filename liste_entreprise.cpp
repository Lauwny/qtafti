#include <iostream>
#include "liste_entreprise.h"
#include "ui_liste_entreprise.h"
#include "seance.h"
#include "societe.h"
#include "vector"

#include "QStringListModel"


liste_entreprise::liste_entreprise(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::liste_entreprise)
{
    ui->setupUi(this);

    //setup de la liste des éléments à afficher
    QStringListModel *model = new QStringListModel(this);
    QStringList List;


    List << "Clair de Lune" << "Reverie" << "Prelude";
    model->setStringList (List);
    //setup du tableau
    ui->lvEnteprise->setModel(model);

    //liste de seances
    vector<seance> liste_seance;

    //setup le nom du label au dessus du tableau
    ui->labelTitre->setText("liste des entreprises");





    for (int i = 1; i <= 10; i++) {
        seance *s = new seance("05/11/63", fRand(0.0, 2.0), fRand(0.0, 2.0), 0.0, 2.0, fRandInt(1,999),"euros");
        liste_seance.push_back(*s);
    }






//    societe *so = new societe("Facebook", "FBK45", 2.0, 0.0, 10, )
}

liste_entreprise::~liste_entreprise()
{
    delete ui;
}

