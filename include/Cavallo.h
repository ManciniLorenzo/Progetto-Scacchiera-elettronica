//Lorenzo Mancini
#ifndef Cavallo_h
#define Cavallo_h
#include "ForwardDeclaration.h"
#include "Pezzo.h"

class Cavallo : public Pezzo{
    public:
        Cavallo(Posizione& pos, bool colore, Scacchiera& scacchiera); //costruttore
        //virtuali in Pezzo.h
        std::vector<Posizione> mosseAccessibili();
        std::vector<Posizione> mosseLegali();
        Pezzo* clone();
};

#endif