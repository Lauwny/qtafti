#ifndef SEANCE_H
#define SEANCE_H

#include <string>
using namespace std;

class seance
{
private:
    string date_seance;
    double valeur_ouverture_seance;
    double valeur_fermeture_seance;
    double valeur_minimal_seance;
    double valeur_maximal_seance;
    int nb_action_echange_seance;
    string monnaie_seance;

public:
    seance();
    seance(string date, double valeur_ouverture, double valeur_fermeture, double valeur_minimal, double valeur_maximal, int nb_action, string monnaie);
    ~seance();
    string getDate_seance();
    void setDate_seance(string value);
    double getValeur_ouverture_seance() const;
    void setValeur_ouverture_seance(double value);
    double getValeur_fermeture_seance() const;
    void setValeur_fermeture_seance(double value);
    double getValeur_minimal_seance() const;
    void setValeur_minimal_seance(double value);
    double getValeur_maximal_seance() const;
    void setValeur_maximal_seance(double value);
    int getNb_action_echange_seance() const;
    void setNb_action_echange_seance(int value);
    string getMonnaie_seance() const;
    void setMonnaie_seance(string value);
};

#endif // SEANCE_H
