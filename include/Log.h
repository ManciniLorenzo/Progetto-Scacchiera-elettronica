//Riccardo De Simoni
#ifndef Log_h
#define Log_h
#include "ForwardDeclaration.h"

#include "Scacchista.h"
#include <iostream>

class Log: public Scacchista{
    private:
        std::istream& inputFile;//XX XX X

    public:
        //costruttore
        Log(bool colore, Scacchiera& scacchiera, std::istream& inputFile);

        class MoveNonEseguito{};
        
        //metodi per leggere da file la listaMosse
        //virtual da Scacchista
        char dimmiChiPromuovere();

        int faiMossa();/*controlla se puo' fare mosse
                        legge posizione di partenza da file --> partenza
                        legge posizione di arrivo da file --> arrivo
                        scacchiera.move(partenza, arrivo)*/
};

#endif