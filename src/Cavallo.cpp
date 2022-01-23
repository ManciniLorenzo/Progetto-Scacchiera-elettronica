//Lorenzo Mancini

#include "Cavallo.h"
#include "Scacchiera.h"

//costruttore
Cavallo::Cavallo(Posizione& newPos, bool newColore, Scacchiera& newScacchiera) : Pezzo(newPos, newColore, newScacchiera, 'c'){}

//funzioni virtuali
std::vector<Posizione> Cavallo::mosseAccessibili(){
    std::vector<Posizione> listaMosse;
    Posizione fakePos(pos.riga, pos.colonna);
    
    //-------------su sinistra
    //aggiornamento a posizione successiva
    fakePos.colonna = fakePos.colonna-1; //diminuisco ascissa
    fakePos.riga = fakePos.riga+2; //aumento ordinata
    try{
        if(scacchiera.get(fakePos)){ //se cavallo trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se cavallo non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna+1;
    fakePos.riga = fakePos.riga-2;

    //-------------su destra
    //aggiornamento a posizione successiva
    fakePos.colonna = fakePos.colonna+1; //aumento ascissa
    fakePos.riga = fakePos.riga+2; //aumento ordinata
    try{
        if(scacchiera.get(fakePos)){ //se cavallo trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se cavallo non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna-1;
    fakePos.riga = fakePos.riga-2;

    //-------------giu sinistra
    //aggiornamento a posizione successiva
    fakePos.colonna = fakePos.colonna-1; //diminuisco ascissa
    fakePos.riga = fakePos.riga-2; //diminuisco ordinata
    try{
        if(scacchiera.get(fakePos)){ //se cavallo trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se cavallo non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna+1;
    fakePos.riga = fakePos.riga+2;

    //-------------giu destra
    //aggiornamento a posizione successiva
    fakePos.colonna = fakePos.colonna+1; //aumento ascissa
    fakePos.riga = fakePos.riga-2; //diminuisco ordinata
    try{
        if(scacchiera.get(fakePos)){ //se cavallo trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se cavallo non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna-1;
    fakePos.riga = fakePos.riga+2;

    //-------------sinistra su
    //aggiornamento a posizione successiva
    fakePos.colonna = fakePos.colonna-2; //diminuisco ascissa
    fakePos.riga = fakePos.riga+1; //aumento ordinata
    try{
        if(scacchiera.get(fakePos)){ //se cavallo trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se cavallo non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna+2;
    fakePos.riga = fakePos.riga-1;

    //-------------sinistra giu
    //aggiornamento a posizione successiva
    fakePos.colonna = fakePos.colonna-2; //diminuisco ascissa
    fakePos.riga = fakePos.riga-1; //diminuisco ordinata
    try{
        if(scacchiera.get(fakePos)){ //se cavallo trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se cavallo non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna+2;
    fakePos.riga = fakePos.riga+1;

    //-------------destra su
    //aggiornamento a posizione successiva
    fakePos.colonna = fakePos.colonna+2; //aumento ascissa
    fakePos.riga = fakePos.riga+1; //aumento ordinata
    try{
        if(scacchiera.get(fakePos)){ //se cavallo trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se cavallo non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna-2;
    fakePos.riga = fakePos.riga-1;

    //-------------destra giu
    //aggiornamento a posizione successiva
    fakePos.colonna = fakePos.colonna+2; //aumento ascissa
    fakePos.riga = fakePos.riga-1; //diminuisco ordinata
    try{
        if(scacchiera.get(fakePos)){ //se cavallo trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se cavallo non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna-2;
    fakePos.riga = fakePos.riga+1;

    return listaMosse;
}

std::vector<Posizione> Cavallo::mosseLegali(){
    std::vector<Posizione> listaMosse = mosseAccessibili(); //ora controllo che il re non vada in scacco facendo una di queste mosse

    //mosse accessibili che non fanno andare in scacco
    for(int i=0; i<listaMosse.size(); i++){
        if(!scacchiera.isLegal(this->pos, listaMosse[i])){
            listaMosse.erase(listaMosse.begin()+i--);
        }
    }
    
    return listaMosse;
}

Pezzo* Cavallo::clone(){
    Pezzo* clone = new Cavallo(pos, colore, scacchiera);
    return clone;
}