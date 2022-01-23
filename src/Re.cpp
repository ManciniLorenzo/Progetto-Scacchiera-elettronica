//Lorenzo Mancini

#include "Re.h"
#include "Torre.h"
#include "Scacchiera.h"

//costruttore
Re::Re(Posizione& newPos, bool newColore, Scacchiera& newScacchiera) : Pezzo(newPos, newColore, newScacchiera, 'r'){}

//funzioni virtuali
std::vector<Posizione> Re::mosseAccessibili(){
    std::vector<Posizione> listaMosse;
    Posizione fakePos(pos.riga, pos.colonna);
    
    //-------------mossa torre: ordinata--
    fakePos.riga = fakePos.riga-1; //aggiornamento a posizione successiva
    try{
        if(scacchiera.get(fakePos)){ //se re trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se re non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.riga = fakePos.riga+1;
    //fakePos e' uguale a this->pos

    //-------------mossa torre: ordinata++
    fakePos.riga = fakePos.riga+1; //aggiornamento a posizione successiva
    try{
        if(scacchiera.get(fakePos)){ //se re trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se re non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.riga = fakePos.riga-1;
    //fakePos e' uguale a this->pos

    //-------------mossa torre: ascissa++
    fakePos.colonna = fakePos.colonna+1; //aggiornamento a posizione successiva
    try{
        if(scacchiera.get(fakePos)){ //se re trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se re non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna-1;
    //fakePos e' uguale a this->pos

    //-------------mossa torre: ascissa--
    fakePos.colonna = fakePos.colonna-1; //aggiornamento a posizione successiva
    try{
        if(scacchiera.get(fakePos)){ //se re trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se re non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna+1;
    //fakePos e' uguale a this->pos

    //-------------mossa alfiere: diagonale in su a destra
    //aggiornamento a posizione successiva
    fakePos.colonna = fakePos.colonna+1;
    fakePos.riga = fakePos.riga+1;

    try{
        if(scacchiera.get(fakePos)){ //se re trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se re non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna-1;
    fakePos.riga = fakePos.riga-1;
    //fakePos e' uguale a this->pos

    //-------------mossa alfiere: diagonale in su a sinistra
    //aggiornamento a posizione successiva
    fakePos.colonna = fakePos.colonna-1;
    fakePos.riga = fakePos.riga+1;

    try{
        if(scacchiera.get(fakePos)){ //se re trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se re non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna+1;
    fakePos.riga = fakePos.riga-1;
    //fakePos e' uguale a this->pos
    
    //-------------mossa alfiere: diagonale in giu a destra
    //aggiornamento a posizione successiva
    fakePos.colonna = fakePos.colonna+1;
    fakePos.riga = fakePos.riga-1;

    try{
        if(scacchiera.get(fakePos)){ //se re trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se re non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna-1;
    fakePos.riga = fakePos.riga+1;
    //fakePos e' uguale a this->pos

    //-------------mossa alfiere: diagonale in giu a sinistra
    //aggiornamento a posizione successiva
    fakePos.colonna = fakePos.colonna-1;
    fakePos.riga = fakePos.riga-1;

    try{
        if(scacchiera.get(fakePos)){ //se re trova un pezzo in una determinata posizione
            if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
            }
        }else{
            //se re non trova niente in quella posizione
            listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
        }
    }catch(Scacchiera::InvalidPosition){}
    //ritorno in posizione originale
    fakePos.colonna = fakePos.colonna+1;
    fakePos.riga = fakePos.riga+1;
    //fakePos e' uguale a this->pos

    return listaMosse;
}

std::vector<Posizione> Re::mosseLegali(){
    std::vector<Posizione> listaMosse = mosseAccessibili(); //ora controllo che il re non vada in scacco se faccio una di queste mosse
    
    //mosse accessibili che non fanno andare in scacco
    for(int i=0; i<listaMosse.size(); i++){
        if(!scacchiera.isLegal(this->pos, listaMosse[i])){
            listaMosse.erase(listaMosse.begin()+i--);
        }
    }

    //-------------ARROCCO-------------
    if(primaMossa && !scacchiera.sottoScacco(this->colore)){ //se prima mossa del re e se non e' sotto scacco

        //controllo torre dx se in basso, sx se in alto (ARROCCO CORTO)
        Posizione fakePos2(pos.riga, 8);
        if(scacchiera.get(fakePos2)){
            if(scacchiera.get(fakePos2)->getTipoPezzo() == 't'){ //controllo se nell'angolo destro (sopra o sotto) c'e' una torre
                Pezzo* torre = scacchiera.get(fakePos2).release(); //prendo il Pezzo che si trova in fakePos2
                if(dynamic_cast<Torre*>(torre)->getPrimaMossa() == 1){ //faccio dynamic cast a torre, controllo se prima mossa della torre
                    Posizione pos_arrivo1(this->pos.riga, this->pos.colonna+1);
                    Posizione pos_arrivo2(this->pos.riga, this->pos.colonna+2);
                    if(!scacchiera.get(pos_arrivo1) && !scacchiera.get(pos_arrivo2)) { // controllo che le posizioni intermedie a re e torre siano vuote
                        if(scacchiera.isLegal(this->pos, pos_arrivo1) && scacchiera.isLegal(this->pos, pos_arrivo2)){ //controllo che le pos intermedie non diano uno scacco al re
                            listaMosse.push_back(Posizione(this->pos.riga, this->pos.colonna+2, 1)); //inserisco la posizione di arrivo del re dopo arrocco
                        }
                    }
                }
                delete torre; //dopo cast da unique_ptr a raw_ptr elimino il puntatore
            }
        }
        
        //controllo torre sx se in basso, dx se in alto (ARROCCO LUNGO)
        Posizione fakePos3(pos.riga, 1);
        if(scacchiera.get(fakePos3)){
            if(scacchiera.get(fakePos3)->getTipoPezzo() == 't'){ //controllo se nell'angolo sinistro (sopra o sotto) c'e' una torre
                Pezzo* torre = scacchiera.get(fakePos3).release(); //prendo il Pezzo che si trova in fakePos3
                if(dynamic_cast<Torre*>(torre)->getPrimaMossa() == 1){ //faccio dynamic cast a torre, controllo se prima mossa della torre
                    Posizione pos_arrivo1(this->pos.riga, this->pos.colonna-1);
                    Posizione pos_arrivo2(this->pos.riga, this->pos.colonna-2);
                    if(!scacchiera.get(pos_arrivo1) && !scacchiera.get(pos_arrivo2)) {
                        if(scacchiera.isLegal(this->pos, pos_arrivo1) && scacchiera.isLegal(this->pos, pos_arrivo2)){ //controllo che le pos intermedie non diano uno scacco al re
                            listaMosse.push_back(Posizione(this->pos.riga, this->pos.colonna-2, 1)); //inserisco la posizione di arrivo del re dopo arrocco
                        }
                    }
                }
                delete torre; //dopo cast da unique_ptr a raw_ptr elimino il puntatore
            }
        }
    }

    return listaMosse;
}

Pezzo* Re::clone(){
    Pezzo* clone = new Re(pos, colore, scacchiera);
    dynamic_cast<Re*>(clone)->setPrimaMossa(primaMossa);
    return clone;
}