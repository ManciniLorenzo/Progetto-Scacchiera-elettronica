//Lorenzo Mancini

#include "Alfiere.h"
#include "Scacchiera.h"

//costruttore
Alfiere::Alfiere(Posizione& newPos, bool newColore, Scacchiera& newScacchiera) : Pezzo(newPos, newColore, newScacchiera, 'a'){}

//funzioni virtuali:
std::vector<Posizione> Alfiere::mosseAccessibili(){
    std::vector<Posizione> listaMosse;
    Posizione fakePos(pos.riga, pos.colonna);
    int x,y; //variabili che indicano la variazione dello spostamento
    x = y = 0; //utili per ritornare alla posizione effettiva del pezzo
    
    //-------------diagonale in su a destra
    while(true){
        x++;
        y++;
        //aggiornamento a posizione successiva
        fakePos.colonna = fakePos.colonna+1; //aumento ascissa
        fakePos.riga = fakePos.riga+1; //aumento ordinata
        try{
            if(scacchiera.get(fakePos)){ //se alfiere trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se alfiere non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna-y;
    fakePos.riga = fakePos.riga-x;
    x = y = 0;

    //-------------diagonale in su a sinistra
    while(true){
        x++;
        y++;
        //aggiornamento a posizione successiva
        fakePos.colonna = fakePos.colonna-1; //diminuisco ascissa
        fakePos.riga = fakePos.riga+1; //aumento ordinata
        try{
            if(scacchiera.get(fakePos)){ //se alfiere trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se alfiere non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna+y;
    fakePos.riga = fakePos.riga-x;
    x = y = 0;

    //-------------diagonale in giu a destra
    while(true){
        x++;
        y++;
        //aggiornamento a posizione successiva
        fakePos.colonna = fakePos.colonna+1; //aumento ascissa
        fakePos.riga = fakePos.riga-1; //diminuisco ordinata
        try{
            if(scacchiera.get(fakePos)){ //se alfiere trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se alfiere non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna-y;
    fakePos.riga = fakePos.riga+x;
    x = y = 0;

    //-------------diagonale in giu a sinistra
    while(true){
        x++;
        y++;
        //aggiornamento a posizione successiva
        fakePos.colonna = fakePos.colonna-1; //diminuisco ascissa
        fakePos.riga = fakePos.riga-1; //diminuisco ordinata
        try{
            if(scacchiera.get(fakePos)){ //se alfiere trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se alfiere non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna+y;
    fakePos.riga = fakePos.riga+x;
    x = y = 0;

    return listaMosse;
}

std::vector<Posizione> Alfiere::mosseLegali(){
    std::vector<Posizione> listaMosse = mosseAccessibili(); //ora controllo che il re non vada in scacco facendo una di queste mosse

    //mosse accessibili che non fanno andare in scacco
    for(int i=0; i<listaMosse.size(); i++){
        if(!scacchiera.isLegal(this->pos, listaMosse[i])){
            listaMosse.erase(listaMosse.begin()+i--);
        }
    }
    
    return listaMosse;

}

Pezzo* Alfiere::clone(){
    Pezzo* clone = new Alfiere(pos, colore, scacchiera);
    return clone;
}