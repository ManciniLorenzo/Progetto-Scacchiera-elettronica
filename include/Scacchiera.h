//Riccardo Di Bella
#ifndef SCACCHIERA_H
#define SCACCHIERA_H
#include "ForwardDeclaration.h"
#include "Pezzo.h"
#include "Pedone.h"
#include "Posizione.h"


#include <string>
#include <vector>
#include <fstream>
#include <memory>

constexpr int NUMERO_RIGHE_SCACCHIERA = 8;
constexpr int NUMERO_COLONNE_SCACCHIERA = 8;

constexpr bool COLORE_BIANCO = 0;
constexpr bool COLORE_NERO = 1;

constexpr int DIREZIONE_GIU = 0;
constexpr int DIREZIONE_SU = 1;

class Scacchiera{
	public:
		class InvalidPosition{};
		// ritorna una copia in modo che gli scacchisti o gli altri pezzi non possano modificare i pezzi originali
		// lo unique_ptr dealloca il clone quando esce dallo scope "l'ultima volta"
		std::unique_ptr<Pezzo> get(Posizione &p) const;
		
		// player deve essere un puntatore allo scacchista che fa la mossa
		// serve per sapere a chi chiedere in caso di promozione
		// bisogna aggiornare le situazioni di scacco dopo la mossa
		// bisogna gestire il movimento della torre per l'arrocco
		// e mangiare il pedone nella cattura en passant
		// bisogna aggiornare il flag due_passi del pedone
		// il turno dopo che ha fatto la prima mossa
		bool move(Scacchista* player, Posizione &partenza, Posizione &arrivo);


		// bisogna gestire correttamente la cattura en-passant
		// non puo' essere const perche' anche se tra inizio e fine la situazione non cambia al suo interno modifica alcune variabili 
		bool isLegal(const Posizione &partenza, const Posizione &arrivo);
		
		std::string stringaScacchiera(bool coloreSotto = COLORE_BIANCO) const;
		
		// Se non si vuole che il file di log abbia un timestamp come nome (si veda .cpp per il formato) si puo' specificare nel parametro nomeFileLog 
		// il nome del file da creare/sovrascrivere (completo di estensione)

		// situazioneIniziale utile per debug, in generale non fa riprendere correttamente la partita da una situazione intermedia
		// (eventuali flag delle pedine hanno i valori di default anche se non si trovano nella posizione iniziale "standard")
		Scacchiera(const std::string &nomeFileLog="", const std::string &situazioneIniziale="tcadractpppppppp                                PPPPPPPPTCADRACT");

		// fa la delete dei pezzi nelle 4 liste, chiude lo stream di output
		~Scacchiera();

		bool sottoScacco(bool colore) const;

		// controlla se una posizione e' valida, chiamato in varie funzioni di scacchiera
		bool isPositionValid(const Posizione &p) const;
		
		

		std::vector<std::unique_ptr<Pezzo>> pezziVivi(bool colore) const;
		std::vector<std::unique_ptr<Pezzo>> pezziMorti(bool colore) const;

		bool patta(bool colore) const;

		// Costruttore e assegnamento di copia e di spostamento disabilitati
		// (Spostamento disabilitato di default con la disabilita della copia)
		// https://stackoverflow.com/questions/48864976/most-concise-way-to-disable-copy-and-move-semantics
		// https://stackoverflow.com/questions/37092864/should-i-delete-the-move-constructor-and-the-move-assignment-of-a-smart-pointer/38820178#38820178
		Scacchiera(const Scacchiera&) = delete;
		Scacchiera& operator=(const Scacchiera&) = delete;
		
	private:

		// Funzioni private: sono ausiliare, non devono essere chiamate dall'esterno

		// azzera il flag due_passi del pedone del colore specificato
		void azzeraPedoneFlag(bool colore);

		// aggiorna le variabili biancoSottoScacco e neroSottoScacco
		// (parametro per scegliere solo quale aggiornare? se ne aggiorna sicuramente solo una alla volta)
		void aggiornaScacco();

		// Dati privati

		// matrice di pezzi
		Pezzo* matrice[NUMERO_RIGHE_SCACCHIERA][NUMERO_COLONNE_SCACCHIERA];

		// lista di pezzi (vivi e morti) per ogni giocatore
		// devono essere sempre riempite completamente
		std::vector<Pezzo*> pezziViviBianco, pezziMortiBianco, pezziViviNero, pezziMortiNero;
		
		std::string fileName;

		bool biancoSottoScacco, neroSottoScacco;

		// in certi punti dell'esecuzione potrebbero essercene uno bianco e uno nero
		// in questo modo prima di fare la mossa successiva si può azzerare il flag al pedone della mossa precedente
		Pedone* pedoneAzzerareFlagDuePassiBianco;
		Pedone* pedoneAzzerareFlagDuePassiNero;

		// contiene una lista delle situazioni in cui si e' trovata la scacchiera dall'ultimo movimento di pedone o pedina mangiata
		// utile per il controllo delle situazioni di patta
		// per identificare una situazione viene utilizzata la stringa ottenuta con stringaScacchiera
		std::vector<std::string> listaScreen;
};
#endif