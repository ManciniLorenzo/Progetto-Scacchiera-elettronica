//Lorenzo Mancini

#include "Regina.h"
#include "Scacchiera.h"

//costruttore
Regina::Regina(Posizione& newPos, bool newColore, Scacchiera& newScacchiera) : Pezzo(newPos, newColore, newScacchiera, 'd'){}

//funzioni virtuali
std::vector<Posizione> Regina::mosseAccessibili(){
    std::vector<Posizione> listaMosse;
    Posizione fakePos(pos.riga, pos.colonna);
    int x,y; //variabili che indicano la variazione dello spostamento
    x = y = 0; //utili per ritornare alla posizione effettiva del pezzo

    //-------------mossa torre: ascissa++
    while(true){
        x++;
        fakePos.colonna = fakePos.colonna+1; //aggiornamento a posizione successiva
        try{
            if(scacchiera.get(fakePos)){ //se regina trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se regina non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna-x;
    x = 0;

    //-------------mossa torre: ascissa--
    while(true){
        x++;
        fakePos.colonna = fakePos.colonna-1; //aggiornamento a posizione successiva
        try{
            if(scacchiera.get(fakePos)){ //se regina trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se regina non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna+x;
    x = 0;

    //-------------mossa torre: ordinata++
    while(true){
        y++;
        fakePos.riga = fakePos.riga+1; //aggiornamento a posizione successiva
        try{
            if(scacchiera.get(fakePos)){ //se regina trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se regina non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.riga = fakePos.riga-y;
    y = 0;
    
    //-------------mossa torre: ordinata--
    while(true){
        y++;
        fakePos.riga = fakePos.riga-1; //aggiornamento a posizione successiva
        try{
            if(scacchiera.get(fakePos)){ //se regina trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se regina non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.riga = fakePos.riga+y;
    y = 0;
    //fakePos e' uguale a this->pos

    //-------------mosse alfiere: diagonale in su a destra
    while(true){
        x++;
        y++;
        //aggiornamento a posizione successiva
        fakePos.colonna = fakePos.colonna+1; //aumento ascissa
        fakePos.riga = fakePos.riga+1; //aumento ordinata
        try{
            if(scacchiera.get(fakePos)){ //se regina trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se regina non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna-y;
    fakePos.riga = fakePos.riga-x;
    x = y = 0;

    //-------------mosse alfiere: diagonale in su a sinistra
    while(true){
        x++;
        y++;
        //aggiornamento a posizione successiva
        fakePos.colonna = fakePos.colonna-1; //diminuisco ascissa
        fakePos.riga = fakePos.riga+1; //aumento ordinata
        try{
            if(scacchiera.get(fakePos)){ //se regina trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se regina non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna+y;
    fakePos.riga = fakePos.riga-x;
    x = y = 0;

    //-------------mosse alfiere: diagonale in giu a destra
    while(true){
        x++;
        y++;
        //aggiornamento a posizione successiva
        fakePos.colonna = fakePos.colonna+1; //aumento ascissa
        fakePos.riga = fakePos.riga-1; //diminuisco ordinata
        try{
            if(scacchiera.get(fakePos)){ //se regina trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se regina non trova niente in quella posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){break;}
    }
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna-y;
    fakePos.riga = fakePos.riga+x;
    x = y = 0;

    //-------------mosse alfiere: diagonale in giu a sinistra
    while(true){
        x++;
        y++;
        //aggiornamento a posizione successiva
        fakePos.colonna = fakePos.colonna-1; //diminuisco ascissa
        fakePos.riga = fakePos.riga-1; //diminuisco ordinata
        try{
            if(scacchiera.get(fakePos)){ //se regina trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
                break;
            }else{
                //se regina non trova niente in quella posizione
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

std::vector<Posizione> Regina::mosseLegali(){
    std::vector<Posizione> listaMosse = mosseAccessibili(); //ora controllo che il re non vada in scacco facendo una di queste mosse

    //mosse accessibili che non fanno andare in scacco
    for(int i=0; i<listaMosse.size(); i++){
        if(!scacchiera.isLegal(this->pos, listaMosse[i])){
            listaMosse.erase(listaMosse.begin()+i--);
        }
    }
    
    return listaMosse;
}

Pezzo* Regina::clone(){
    Pezzo* clone = new Regina(pos, colore, scacchiera);
    return clone;
}