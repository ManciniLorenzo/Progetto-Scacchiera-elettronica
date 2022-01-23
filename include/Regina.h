//Lorenzo Mancini
#ifndef Regina_h
#define Regina_h
#include "ForwardDeclaration.h"
#include "Pezzo.h"

class Regina : public Pezzo{
    public:
        Regina(Posizione& pos, bool colore, Scacchiera& scacchiera); //costruttore
        //virtuali in Pezzo.h
        std::vector<Posizione> mosseAccessibili();
        std::vector<Posizione> mosseLegali();
        Pezzo* clone();
};

#endif