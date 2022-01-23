// Riccardo De Simoni
#include <iostream>
#include "Computer.h"

// metodi virtual
char Computer::dimmiChiPromuovere()
{
    int promotion = rand() % 4 + 1;
    if (promotion == 1)
        return 'D';
    else if (promotion == 2)
        return 'A';
    else if (promotion == 3)
        return 'C';
    return 'T';
}

int Computer::faiMossa()
{ // ritorna 0 se partita in corso, 1 se patta, 2 se persa
    if(scacchiera.patta(colore)){
        return 1;
    }
    // controllo se i pezzi vivi del mio colore possono fare almeno una mossa legale, cioe' che non espone a scacco
    std::vector<std::unique_ptr<Pezzo>> pezzi = scacchiera.pezziVivi(colore);

    bool trovato = false;
    for (int i = 0; i < pezzi.size(); i++)
    {
        if (pezzi[i]->mosseLegali().size() > 0) // se la lista di mosse legali di ogni pezzo e' piu' grande di zero
        {
            trovato = true; // c'e' almeno un pezzo che puo' fare almeno una mossa legale
            break;
        }
    }

    if (!trovato)
    { // se non si possono fare mosse legali
        if (scacchiera.sottoScacco(colore))
        { // scacco matto
            return 2;
        } // partita persa
        else
        {
            return 1;
        } // partita patta
    }

    std::vector<std::unique_ptr<Pezzo>> listaPezzi = scacchiera.pezziVivi(colore); // lista di pezzi vivi della mia squadra
    Posizione partenza(0, 0);
    Posizione arrivo(0, 0);
    while (true)
    {
        int i = rand() % listaPezzi.size();
        // listaPezzi[i] è un pezzo random vivo della mia squadra
        partenza = listaPezzi[i]->getPosizione(); // recupero posizione di partenza del pezzo random

        std::vector<Posizione> listaMosse = (listaPezzi[i])->mosseLegali(); // lista di mosseLegali del pezzo random
        if (listaMosse.size() > 0)
        {                                       // se il pezzo puo' fare mosse legali
            int j = rand() % listaMosse.size(); // scelgo mossa legale a caso
            arrivo = listaMosse[j];             // recupero posizione di arrivo del pezzo random
            break;
        }
        else
        {                                             // se il pezzo non puo' fare mosse
            listaPezzi.erase(listaPezzi.begin() + i); // tolgo il pezzo dalla listaPezzi
        }
    }
    scacchiera.move(this, partenza, arrivo); // eseguo la mossa
    ultimaMossa = partenza.getStringa() + " " + arrivo.getStringa();

    return 0; // partita in corso
}

std::string Computer::lastMove()
{
    return ultimaMossa;
}