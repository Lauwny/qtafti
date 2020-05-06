#ifndef LISTE_COURS_ENTREPRISE_H
#define LISTE_COURS_ENTREPRISE_H

#include <QWidget>

namespace Ui {
class liste_cours_entreprise;
}

class liste_cours_entreprise : public QWidget
{
    Q_OBJECT

public:
    explicit liste_cours_entreprise(QWidget *parent = nullptr);
    ~liste_cours_entreprise();

private:
    Ui::liste_cours_entreprise *ui;
};

#endif // LISTE_COURS_ENTREPRISE_H
