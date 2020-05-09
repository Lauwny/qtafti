#ifndef SOCIETE_H
#define SOCIETE_H

#include "vector"

#include "seance.h"

#include <string>
using namespace std;

class societe
{
private:

    string nom_societe;
    string code_associe_societe;
    double val_max_societe;
    double val_min_societe;
    int nb_seances_societe;
    vector<seance> liste_seance;

public:
    societe();

    societe(std::string nom, std::string code);

    societe(std::string nom, std::string code, double val_max, double val_min, int nb_seances, vector<seance> list);

    ~societe();

    string getNom_societe() const;
    void setNom_societe(string value);
    std::string getCode_associe_societe() const;
    void setCode_associe_societe(string value);
    double getVal_max_societe() const;
    void setVal_max_societe(double value);
    double getVal_min_societe() const;
    void setVal_min_societe(double value);
    int getNb_seances_societe() const;
    void setNb_seances_societe(int value);
    vector<seance> getListe_seance() const;
    void setListe_seance(vector<seance> &value);

    string toString();
};

#endif // SOCIETE_H
