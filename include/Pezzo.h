//Lorenzo Mancini
#ifndef Pezzo_h
#define Pezzo_h
#include "ForwardDeclaration.h"
#include "Posizione.h"
#include <vector>

class Pezzo{
    protected:
        Posizione pos;
        bool colore; //0 bianco, 1 nero
        Scacchiera& scacchiera;
        char tipoPezzo;
        Pezzo(Posizione& newPos, bool newColore, Scacchiera& newScacchiera, char newTipoPezzo): pos {newPos}, colore {newColore}, scacchiera{newScacchiera}, tipoPezzo{newTipoPezzo}{}
    public:
        virtual std::vector<Posizione> mosseAccessibili() = 0; //tutte le mosse che un pezzo puo' effettivamente fare
        virtual std::vector<Posizione> mosseLegali() = 0; //tutte le mosse accessibili che non mettono il proprio re in scacco
        virtual Pezzo* clone() = 0; //metodo utilizzato per non permettere ad altre parti del programma di invalidare lo stato della scacchiera
        Posizione getPosizione(){return pos;}
        void setPosizione(Posizione newPos){pos=newPos;}
        bool getColore(){return colore;}
        void setColore(bool newColore){colore=newColore;}
        char getTipoPezzo(){return tipoPezzo;}
};

#endif