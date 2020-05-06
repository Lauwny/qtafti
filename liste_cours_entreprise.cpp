#include "liste_cours_entreprise.h"
#include "ui_liste_cours_entreprise.h"

liste_cours_entreprise::liste_cours_entreprise(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::liste_cours_entreprise)
{
    ui->setupUi(this);
}

liste_cours_entreprise::~liste_cours_entreprise()
{
    delete ui;
}
