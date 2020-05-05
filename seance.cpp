#include "seance.h"

#include "iostream"

#include <string>
using namespace std;

string seance::getDate_seance()
{
    return date_seance;
}

void seance::setDate_seance(string value)
{
    date_seance = value;
}

double seance::getValeur_ouverture_seance() const
{
    return valeur_ouverture_seance;
}

void seance::setValeur_ouverture_seance(double value)
{
    valeur_ouverture_seance = value;
}

double seance::getValeur_fermeture_seance() const
{
    return valeur_fermeture_seance;
}

void seance::setValeur_fermeture_seance(double value)
{
    valeur_fermeture_seance = value;
}

double seance::getValeur_minimal_seance() const
{
    return valeur_minimal_seance;
}

void seance::setValeur_minimal_seance(double value)
{
    valeur_minimal_seance = value;
}

double seance::getValeur_maximal_seance() const
{
    return valeur_maximal_seance;
}

void seance::setValeur_maximal_seance(double value)
{
    valeur_maximal_seance = value;
}

int seance::getNb_action_echange_seance() const
{
    return nb_action_echange_seance;
}

void seance::setNb_action_echange_seance(int value)
{
    nb_action_echange_seance = value;
}

std::string seance::getMonnaie_seance() const
{
    return monnaie_seance;
}

void seance::setMonnaie_seance(std::string value)
{
    monnaie_seance = value;
}

seance::seance()
{
    std::cout<<"Creation de la séance"<<endl;
    this->date_seance = '\0';
    this->valeur_ouverture_seance = 0.0;
    this->valeur_fermeture_seance = 0.0;
    this->valeur_minimal_seance = 0.0;
    this->valeur_maximal_seance = 0.0;
    this->nb_action_echange_seance = 0;
    this->monnaie_seance = '\0';
}

seance::seance(string date, double valeur_ouverture, double valeur_fermeture, double valeur_minimal, double valeur_maximal, int nb_action, string monnaie)
{
    std::cout<<"Creation de la séance"<<endl;
    this->date_seance = date;
    this->valeur_ouverture_seance = valeur_ouverture;
    this->valeur_fermeture_seance = valeur_fermeture;
    this->valeur_minimal_seance = valeur_minimal;
    this->valeur_maximal_seance = valeur_maximal;
    this->nb_action_echange_seance = nb_action;
    this->monnaie_seance = monnaie;
}

seance::~seance()
{
    std::cout<<"destruction de la seance"<<endl;
}


