// Riccardo De Simoni
#ifndef SCACCHISTA_H
#define SCACCHISTA_H
#include "ForwardDeclaration.h"
#include "Scacchiera.h"

class Scacchista
{
protected:
    bool colore;            // 0 se bianco, 1 se nero
    Scacchiera &scacchiera; // scacchista deve giocare su una scacchiera
    // costruttore
    Scacchista(bool new_colore, Scacchiera &new_scacchiera) : colore{new_colore}, scacchiera{new_scacchiera} {}

public:
    virtual char dimmiChiPromuovere() = 0;

    virtual int faiMossa() = 0; // 0 se la partita non è finita,
                                // 1 se è patta
                                // 2 se è persa

    bool getColore() { return colore; }
};

#endif