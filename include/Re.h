//Lorenzo Mancini
#ifndef Re_h
#define Re_h
#include "ForwardDeclaration.h"
#include "Pezzo.h"

class Re : public Pezzo{
    private:
        int primaMossa; //flag per ARROCCO: 1 se prima mossa, 0 altrimenti
    public:
        Re(Posizione& pos, bool colore, Scacchiera& scacchiera); //costruttore
        //virtuali in Pezzo.h
        std::vector<Posizione> mosseAccessibili();
        std::vector<Posizione> mosseLegali();
        Pezzo* clone();
        //primaMossa
        int getPrimaMossa(){return primaMossa;}
        void setPrimaMossa(int newPrimaMossa){primaMossa = newPrimaMossa;}
};

#endif