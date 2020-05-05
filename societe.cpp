#include "societe.h"
#include "iostream"
#include "seance.h"
#include <string>
using namespace std;


string societe::getNom_societe() const
{
    return nom_societe;
}

void societe::setNom_societe(string value)
{
    nom_societe = value;
}

std::string societe::getCode_associe_societe() const
{
    return code_associe_societe;
}

void societe::setCode_associe_societe(std::string value)
{
    code_associe_societe = value;
}

double societe::getVal_max_societe() const
{
    return val_max_societe;
}

void societe::setVal_max_societe(double value)
{
    val_max_societe = value;
}

double societe::getVal_min_societe() const
{
    return val_min_societe;
}

void societe::setVal_min_societe(double value)
{
    val_min_societe = value;
}

int societe::getNb_seances_societe() const
{
    return nb_seances_societe;
}

void societe::setNb_seances_societe(int value)
{
    nb_seances_societe = value;
}

std::vector<seance> societe::getListe_seance() const
{
    return liste_seance;
}

void societe::setListe_seance(std::vector<seance> &value)
{
    liste_seance = value;
}

societe::societe()
{
    std::cout<<"Creation de la société"<<endl;
    this->nom_societe = '\0';
    this->code_associe_societe = '\0';
    this->val_max_societe = 0.0;
    this->val_min_societe = 0.0;
    this->nb_seances_societe = 0;
    this->liste_seance = std::vector<seance>();
}

societe::societe(std::string nom, std::string code, double val_max, double val_min, int nb_seances, std::vector<seance> list)
{
    std::cout<<"Creation de la société"<<endl;
    this->nom_societe = nom;
    this->code_associe_societe = code;
    this->val_max_societe = val_max;
    this->val_min_societe = val_min;
    this->nb_seances_societe = nb_seances;
    this->liste_seance = list;
}

societe::~societe()
{
    std::cout<<"destruction de la societe"<<endl;
}


