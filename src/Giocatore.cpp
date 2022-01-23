// Riccardo De Simoni

#include "Giocatore.h"
#include "Scacchiera.h"
#include <iostream>

// metodi virtual
char Giocatore::dimmiChiPromuovere()
{
    while (true)
    {
        std::cout << "Pedina da promuovere: (D A C T): ";
        char promotion;
        std::cin >> promotion;
        if(promotion>='a'&&promotion<='z'){
            promotion-=32;
        }
        if (promotion == 'D' || promotion == 'A' || promotion == 'C' || promotion == 'T')
            return promotion;
        else
        { // carattere di promozione non valido
            std::cout << "Pedina non valida, riprova...\n";
        }
    }
}

int Giocatore::faiMossa()
{ // ritorna 0 se partita in corso, 1 se patta, 2 se persa
    if(scacchiera.patta(colore)){
        return 1;
    }
    // controllo se pezziVivi possono fare almeno una mossa legale, cioe' che non espone a scacco matto
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

    while (true)
    {
        std::string partenza;
        std::string arrivo;
        std::cout << "GIOCATORE: inserisci coordinate partenza e arrivo: ";
        
        std::cin >> partenza;
        std::cin >> arrivo;
        for(int i = 0; i < partenza.length() ; i++) {
            if(partenza[i] >= 'A' && partenza[i] <= 'Z' ){
                partenza[i] += 32 ;
            }

        }

        for(int i = 0; i < arrivo.length() ; i++) {
            if(arrivo[i] >= 'A' && arrivo[i] <= 'Z' ){
                arrivo[i] += 32 ;
            }

        }
        

        if( arrivo == "xx" && partenza == "xx" ){
            std::cout << scacchiera.stringaScacchiera();
            continue;
        }
        Posizione partenza1 = Posizione(partenza); // costruttore Posizione(std::string)
        Posizione arrivo1 = Posizione(arrivo);     // costruttore Posizione(std::string)

        try
        {
            if (scacchiera.move(this, partenza1, arrivo1))
            {
                break; // mossa valida
            }
            else // mossa non valida
            {
                std::cout << "Mossa non valida, inserire un'altra mossa\n";
            }
        }
        catch (Scacchiera::InvalidPosition)
        {
            std::cout << "Posizione non consentita, inserire un'altra mossa\n";
        }
    }
    return 0; // partita in corso
}