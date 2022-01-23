//Lorenzo Mancini

#include "Torre.h"
#include "Scacchiera.h"

//costruttore
Torre::Torre(Posizione& newPos, bool newColore, Scacchiera& newScacchiera) : Pezzo(newPos, newColore, newScacchiera, 't'){}

//funzioni virtuali
std::vector<Posizione> Torre::mosseAccessibili(){
    std::vector<Posizione> listaMosse;
    Posizione fakePos(pos.riga, pos.colonna);
    int i = 0; //variabile che indica la variazione dello spostamento
               //utile per ritornare alla posizione effettiva del pezzo

    //-------------ascissa++
    while(true){
        i++;
        fakePos.colonna = fakePos.colonna+1; //aggiornamento a posizione successiva
        try{
            if(scacchiera.get(fakePos)){ //se torre trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se torre non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna-i;
    i = 0;

    //-------------ascissa--
    while(true){
        i++;
        fakePos.colonna = fakePos.colonna-1; //aggiornamento a posizione successiva
        try{
            if(scacchiera.get(fakePos)){ //se torre trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se torre non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna+i;
    i = 0;

    //-------------ordinata++
    while(true){
        i++;
        fakePos.riga = fakePos.riga+1; //aggiornamento a posizione successiva
        try{
            if(scacchiera.get(fakePos)){ //se torre trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se torre non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.riga = fakePos.riga-i;
    i = 0;
    
    //-------------ordinata--
    while(true){
        i++;
        fakePos.riga = fakePos.riga-1; //aggiornamento a posizione successiva
        try{
            if(scacchiera.get(fakePos)){ //se torre trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se torre non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.riga = fakePos.riga+i;
    i = 0;
    //fakePos e' uguale a this->pos

    return listaMosse;

}

std::vector<Posizione> Torre::mosseLegali(){
    std::vector<Posizione> listaMosse = mosseAccessibili(); //ora controllo che il re non vada in scacco facendo una di queste mosse

    //mosse accessibili che non fanno andare in scacco
    for(int i=0; i<listaMosse.size(); i++){
        if(!scacchiera.isLegal(this->pos, listaMosse[i])){
            listaMosse.erase(listaMosse.begin()+i--);
        }
    }
    
    return listaMosse;
}

Pezzo* Torre::clone(){
    Pezzo* clone = new Torre(pos, colore, scacchiera);
    dynamic_cast<Torre*>(clone)->setPrimaMossa(primaMossa);
    return clone;
}