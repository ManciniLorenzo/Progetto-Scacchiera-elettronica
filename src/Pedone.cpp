//Lorenzo Mancini

#include "Pedone.h"
#include "Scacchiera.h"

//costruttore
Pedone::Pedone(Posizione& newPos, bool newColore, Scacchiera& newScacchiera, int newDir) : Pezzo(newPos, newColore, newScacchiera, 'p'), direzione{newDir}{}

//funzioni virtuali
std::vector<Posizione> Pedone::mosseAccessibili(){
    std::vector<Posizione> listaMosse;
    Posizione fakePos(pos.riga, pos.colonna);
    Posizione fakePos2(pos.riga, pos.colonna);

    //direzione verso il basso
    if(direzione==0){

        //-------------se prima mossa aggiungo anche duePassi a listaMosse
        if(fakePos.riga == 7){
            fakePos.riga = fakePos.riga-2; //aggiornamento a posizione successiva
            fakePos2.riga = fakePos2.riga-1; //per fare due passi non deve esserci niente in mezzo
            try{
                if(!scacchiera.get(fakePos) && !scacchiera.get(fakePos2)){ //se pedone non trova un pezzo in una determinata posizione
                    listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
                    
                }
            }catch(Scacchiera::InvalidPosition){}
                //else --> se pedone trova pezzo non puo' fare niente
                // non aggiungo la posizione a listaMosse
            //ritorno in posizione originale
            fakePos.riga = fakePos.riga+2;
            fakePos2.riga = fakePos2.riga+1;
            //fakePos e' uguale a this->pos
            //fakePos2 e' uguale a this->pos

            //scacchiera aggiorna il flag duePassi
        }

        //-------------mossa torre: ordinata--
        fakePos.riga = fakePos.riga-1; //aggiornamento a posizione successiva
        try{
            if(!scacchiera.get(fakePos)){ //se pedone non trova un pezzo in una determinata posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){}
            //else --> se pedone trova pezzo non puo' fare niente
            // non aggiungo la posizione a listaMosse
        //ritorno in posizione originale
        fakePos.riga = fakePos.riga+1;
        //fakePos e' uguale a this->pos

        //aggiungo a lista mosse anche se un pedone puo' mangiare:
        //-------------mangia a destra
        fakePos.riga = fakePos.riga-1; //aggiornamento a posizione successiva
        fakePos.colonna = fakePos.colonna-1;
        try{
            if(scacchiera.get(fakePos)){ //se pedone trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
            }
        }catch(Scacchiera::InvalidPosition){}
            //else --> se pedone non trova pezzo in diagonale non puo' fare niente
            // non aggiungo la posizione a listaMosse
        //ritorno in posizione originale
        fakePos.riga = fakePos.riga+1;
        fakePos.colonna = fakePos.colonna+1;
        //fakePos e' uguale a this->pos

        //-------------mangia a sinistra
        fakePos.riga = fakePos.riga-1; //aggiornamento a posizione successiva
        fakePos.colonna = fakePos.colonna+1;
        try{
            if(scacchiera.get(fakePos)){ //se pedone trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
            }
        }catch(Scacchiera::InvalidPosition){}
            //else --> se pedone non trova pezzo in diagonale non puo' fare niente
            // non aggiungo la posizione a listaMosse
        //ritorno in posizione originale
        fakePos.riga = fakePos.riga+1;
        fakePos.colonna = fakePos.colonna-1;
        //fakePos e' uguale a this->pos
    }
    //direzione verso l'alto (direzione==1)
    else{

        //-------------se prima mossa aggiungo anche duePassi a listaMosse
        if(fakePos.riga == 2){
            fakePos.riga = fakePos.riga+2; //aggiornamento a posizione successiva
            fakePos2.riga = fakePos2.riga+1; //per fare due passi non deve esserci niente in mezzo
            try{
                if(!scacchiera.get(fakePos) && !scacchiera.get(fakePos2)){ //se pedone non trova un pezzo in una determinata posizione
                    listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
                }
            }catch(Scacchiera::InvalidPosition){}
                //else --> se pedone trova pezzo non puo' fare niente
                // non aggiungo la posizione a listaMosse
            //ritorno in posizione originale
            fakePos.riga = fakePos.riga-2;
            fakePos2.riga = fakePos2.riga-1;
            //fakePos e' uguale a this->pos
            //fakePos2 e' uguale a this->pos

            //scacchiera aggiorna il flag duePassi
        }

        //-------------mossa torre: ordinata++
        fakePos.riga = fakePos.riga+1; //aggiornamento a posizione successiva
        try{
            if(!scacchiera.get(fakePos)){ //se pedone non trova un pezzo in una determinata posizione
                listaMosse.push_back(fakePos); //la inserisce nella lista e controlla in una casa successiva
            }
        }catch(Scacchiera::InvalidPosition){}
            //else --> se pedone trova pezzo non puo' fare niente
            // non aggiungo la posizione a listaMosse
        //ritorno in posizione originale
        fakePos.riga = fakePos.riga-1;
        //fakePos e' uguale a this->pos
        
        //aggiungo a lista mosse anche se un pedone puo' mangiare:
        //-------------mangia a destra
        fakePos.riga = fakePos.riga+1; //aggiornamento a posizione successiva
        fakePos.colonna = fakePos.colonna+1;
        try{
            if(scacchiera.get(fakePos)){ //se pedone trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
            }
        }catch(Scacchiera::InvalidPosition){}
            //else --> se pedone non trova pezzo in diagonale non puo' fare niente
            // non aggiungo la posizione a listaMosse
        //ritorno in posizione originale
        fakePos.riga = fakePos.riga-1;
        fakePos.colonna = fakePos.colonna-1;
        //fakePos e' uguale a this->pos

        //-------------mangia a sinistra
        fakePos.riga = fakePos.riga+1; //aggiornamento a posizione successiva
        fakePos.colonna = fakePos.colonna-1;
        try{
            if(scacchiera.get(fakePos)){ //se pedone trova un pezzo in una determinata posizione
                if(scacchiera.get(fakePos)->getColore()!=this->colore){ //e se quel pezzo e' della squadra avversaria
                    listaMosse.push_back(fakePos); //inserisco quella posizione nella lista delle posizioni accessibili
                }
            }
        }catch(Scacchiera::InvalidPosition){}
            //else --> se pedone non trova pezzo in diagonale non puo' fare niente
            // non aggiungo la posizione a listaMosse
        //ritorno in posizione originale
        fakePos.riga = fakePos.riga-1;
        fakePos.colonna = fakePos.colonna+1;
        //fakePos e' uguale a this->pos
    }
    return listaMosse;

}

std::vector<Posizione> Pedone::mosseLegali(){
    std::vector<Posizione> listaMosse = mosseAccessibili(); //ora controllo che il re non vada in scacco se faccio una di queste mosse

    //mosse accessibili che non fanno andare in scacco
    for(int i=0; i<listaMosse.size(); i++){
        if(!scacchiera.isLegal(this->pos, listaMosse[i])){
            listaMosse.erase(listaMosse.begin()+i--);
        }
    }

    //-------------EN-PASSANT-------------
    //EN-PASSANT a destra
    Posizione fakePosDx(0, 0);
    if(this->direzione == 1){ // se direzione pedone = 1 (va in su)
         fakePosDx = Posizione (this->pos.riga, this->pos.colonna+1); //prendo il pedone alla mia destra
    } else { // se direzione pedone = 0 (va in giu)
        fakePosDx = Posizione (this->pos.riga, this->pos.colonna-1); //prendo il pedone alla mia destra 
    }
    try{
        if(scacchiera.get(fakePosDx)){
            if(scacchiera.get(fakePosDx)->getTipoPezzo() == 'p' && scacchiera.get(fakePosDx)->getColore()!=colore){ //se a destra ho un pedone avversario
                Pezzo* pedoneDaMangiare = scacchiera.get(fakePosDx).release(); // recupero la posizione di quel pedone (fakePosDx)
                if(dynamic_cast<Pedone*>(pedoneDaMangiare)->getDuePassi() == 1){ //faccio dynamic cast a pedone, controllo se prima mossa di quel pedone
                    Posizione posArrivo(0, 0);
                    if(this->direzione == 1){ // se direzione pedone = 1 (va in su)
                        posArrivo = Posizione (this->pos.riga+1, this->pos.colonna+1); // aumento ascissa e ordinata
                    } else { // se direzione pedone = 0 (va in giu)
                        posArrivo = Posizione (this->pos.riga-1, this->pos.colonna-1); //diminuisco ascissa e diminuisco ordinata
                    }
                    if(scacchiera.isLegal(this->pos, posArrivo)){ //controllo che fare en-passant non dia uno scacco al mio re
                            listaMosse.push_back(Posizione(posArrivo.riga, posArrivo.colonna, 2)); //inserisco la posizione di arrivo del pedone dopo en-passant nella lista di mosse legali
                                                                                                      // segnalo che quella posizione e' un en-passant
                    }
                }
                delete pedoneDaMangiare; //dopo cast da unique_ptr a raw_ptr elimino il puntatore
            }
        }
    }catch(Scacchiera::InvalidPosition){}

    //EN-PASSANT a sinistra
    Posizione fakePosSx(0, 0);
    if(this->direzione == 1){ // se direzione pedone = 1 (va in su)
        fakePosSx = Posizione (this->pos.riga, this->pos.colonna-1); // prendo il pedone alla mia sinistra
    } else { // se direzione pedone = 0 (va in giu)
        fakePosSx = Posizione (this->pos.riga, this->pos.colonna+1); //prendo il pedone alla mia sinistra
    }
    try{
        if(scacchiera.get(fakePosSx)){
            if(scacchiera.get(fakePosSx)->getTipoPezzo() == 'p' && scacchiera.get(fakePosSx)->getColore()!=colore){ //se a sinistra ho un pedone avversario
                Pezzo* pedoneDaMangiare = scacchiera.get(fakePosSx).release(); // recupero la posizione di quel pedone (fakePosSx)
                if(dynamic_cast<Pedone*>(pedoneDaMangiare)->getDuePassi() == 1){ //faccio dynamic cast a pedone, controllo se prima mossa di quel pedone
                    Posizione posArrivo(0, 0);
                    if(this->direzione == 1){ // se direzione pedone = 1 (va in su)
                        posArrivo = Posizione (this->pos.riga+1, this->pos.colonna-1); //diminuisco ascissa e aumento ordinata
                    } else { // se direzione pedone = 0 (va in giu)
                        posArrivo = Posizione (this->pos.riga-1, this->pos.colonna+1); //aumento ordinata e diminuisco ascissa
                    }
                    if(scacchiera.isLegal(this->pos, posArrivo)){ //controllo che fare en-passant non dia uno scacco al mio re
                            listaMosse.push_back(Posizione(posArrivo.riga, posArrivo.colonna, 2)); //inserisco la posizione di arrivo del pedone dopo en-passant nella lista di mosse legali
                                                                                                      // segnalo che quella posizione e' un en-passant
                    }
                }
                delete pedoneDaMangiare; //dopo cast da unique_ptr a raw_ptr elimino il puntatore
            }
        }
    }catch(Scacchiera::InvalidPosition){}

    return listaMosse;
}

Pezzo* Pedone::clone(){
    Pezzo* clone = new Pedone(pos, colore, scacchiera, direzione);
    dynamic_cast<Pedone*>(clone)->setDuePassi(duePassi);
    return clone;
}