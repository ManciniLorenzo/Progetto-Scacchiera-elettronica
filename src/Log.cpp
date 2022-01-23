//Lorenzo Mancini

#include "Log.h"

//costruttore
Log::Log(bool colore, Scacchiera& scacchiera, std::istream& newInputFile) : Scacchista(colore, scacchiera), inputFile{newInputFile} {}

//metodi virtual
char Log::dimmiChiPromuovere(){
    std::string str;
    inputFile>>str;
    char nuovoPezzo = str[0];
	return nuovoPezzo;
}

int Log::faiMossa(){
    if(scacchiera.patta(colore)){
        return 1;
    }
    //controllo se pezziVivi possono fare almeno una mossa legale, cioe' che non espone a scacco
    std::vector<std::unique_ptr<Pezzo>> pezzi=scacchiera.pezziVivi(colore);
    bool trovato = false;
    for(int i=0; i<pezzi.size(); i++){
        if(pezzi[i]->mosseLegali().size()>0){
            trovato = true;
            break;
        }
    }

    if(!trovato){
        if(scacchiera.sottoScacco(colore)){return 2;}
        else{return 1;}
    }

    std::string partenza, arrivo;
    inputFile>>partenza;
    inputFile>>arrivo;
    Posizione inizio = Posizione(partenza);
    Posizione fine = Posizione(arrivo);
    
    try{
        if(!scacchiera.move(this, inizio, fine)){
            throw MoveNonEseguito();
        }
    }catch(Scacchiera::InvalidPosition){throw MoveNonEseguito();};
    
    return 0;
}