//Lorenzo Mancini
#ifndef Pedone_h
#define Pedone_h
#include "ForwardDeclaration.h"
#include "Pezzo.h"

class Pedone : public Pezzo{
    private:
        int direzione; //pedoni hanno direzioni diverse in base alla squadra
                       //0 va giu', 1 va su
        int duePassi; //flag per EN-PASSANT: il pedone parte con flag=0
                       //se fa i due passi il flag=1 quindi puo' essere mangiato
                       //se non viene mangiato il flag=0
    public:
        Pedone(Posizione& pos, bool colore, Scacchiera& scacchiera, int direzione); //costruttore
        //virtuali in Pezzo.h
        std::vector<Posizione> mosseAccessibili();
        std::vector<Posizione> mosseLegali();
        Pezzo* clone();
        //direzione
        int getDirezione(){return direzione;}
        void setDirezione(int newDirezione){direzione = newDirezione;}
        //DuePassi
        int getDuePassi(){return duePassi;}
        void setDuePassi(int newDuePassi){duePassi = newDuePassi;}
};

#endif