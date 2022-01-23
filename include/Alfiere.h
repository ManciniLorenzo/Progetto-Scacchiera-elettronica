//Lorenzo Mancini
#ifndef Alfiere_h
#define Alfiere_h
#include "ForwardDeclaration.h"
#include "Pezzo.h"

class Alfiere : public Pezzo{
    public:
        Alfiere(Posizione& pos, bool colore, Scacchiera& scacchiera); //costruttore
        //virtuali in Pezzo.h
        std::vector<Posizione> mosseAccessibili();
        std::vector<Posizione> mosseLegali();
        Pezzo* clone();
};

#endif