//Riccardo De Simoni
#ifndef COMPUTER_H
#define COMPUTER_H
#include "ForwardDeclaration.h"
#include "Scacchista.h"

class Computer : public Scacchista
{
public:
    //costruttore
    Computer(bool colore, Scacchiera &scacchiera) : Scacchista(colore, scacchiera) {}
    //metodi per scegliere in modo random le mosse da listaMosse
    //virtual da Scacchista
    char dimmiChiPromuovere();

    std::string lastMove();

    int faiMossa(); /*controlla se puo' fare mosse 
                        sceglie la posizione di un pezzo da muovere a caso --> partenza
                        sceglie dove mettere il pezzo--> arrivo
                        scacchiera.move(partenza, arrivo)*/
private:
    std::string ultimaMossa;
};

#endif