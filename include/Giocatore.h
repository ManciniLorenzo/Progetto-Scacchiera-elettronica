//Riccardo De Simoni
#ifndef GIOCATORE_H
#define GIOCATORE_H
#include "ForwardDeclaration.h"
#include "Scacchista.h"

class Giocatore : public Scacchista
{
public:
    //costruttore
    Giocatore(bool colore, Scacchiera &scacchiera) : Scacchista(colore, scacchiera) {}
    //metodi per leggere da input
    //virtual da Scacchista
    char dimmiChiPromuovere();
    int faiMossa();
};

#endif
