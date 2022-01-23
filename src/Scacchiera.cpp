//Riccardo Di Bella
#include "Scacchiera.h"

#include "Posizione.h"
#include "Pezzo.h"
#include "Scacchista.h"
#include "Pedone.h"

#include "Re.h"
#include "Pedone.h"
#include "Alfiere.h"
#include "Regina.h"
#include "Cavallo.h"
#include "Torre.h"


#include <string>
#include <vector>
#include <memory>
#include <typeinfo>		// https://en.cppreference.com/w/cpp/language/typeid
#include <ctime>		// https://www.cplusplus.com/reference/ctime/strftime/
#include <fstream>		// file di log

/* 
	Nota tecnica:
	
	Per identificare il tipo di ciascun pezzo in questo file non e' stato usato getTipoPezzo: per
	tale scopo sono stati usati typeid e dynamic_cast (in modo abbastanza indifferente in quanto da
	scelte progettuali non e' possibile che ci siano piu' livelli di ereditarieta' nei pezzi, che
	altererebbero il funzionamento di typeid). In altri file (prevalentemente di altri autori), invece,
	e' stato preferita la funzione getTipoPezzo di Pezzo; non ci e' noto alcun motivo rilevante per cui,
	per le modalità con cui queste funzioni vengono usate per la sola identificazione del tipo e per la
	dimensione del progetto, sia preferibile usare uno dei tre approcci rispetto agli altri due.
	Non riteniamo sussista, dunque, la necessità di uniformare l'approccio all'interno dei diversi file
	(o anche solo di questo file, in cui e' stato usato piu' di un approccio per risolvere lo stesso problema)
	ma, per gli scopi della comprensione del codice, i tre approcci sono da considerarsi equivalenti.
	
*/

bool Scacchiera::isPositionValid(const Posizione &p) const{
	return !(p.riga>8||p.riga<1||p.colonna>8||p.colonna<1);
}
// Ritorna UNA COPIA del pezzo tramite unique_ptr
std::unique_ptr<Pezzo> Scacchiera::get(Posizione &p) const{
	if(!isPositionValid(p)){
		throw InvalidPosition();
	}
	int rigaVera = p.riga-1;
	int colonnaVera = p.colonna-1;
	if(matrice[rigaVera][colonnaVera]==nullptr){
		std::unique_ptr<Pezzo> ptrVuoto(nullptr);
		return ptrVuoto;
	}
	Pezzo* ptrOriginale = matrice[rigaVera][colonnaVera];
	std::unique_ptr<Pezzo> ptrDaRitornare(ptrOriginale->clone());
	return ptrDaRitornare;
}

Scacchiera::~Scacchiera(){
	for(int i=0; i<pezziViviBianco.size(); i++){
		delete pezziViviBianco[i];
	}
	for(int i=0; i<pezziMortiBianco.size(); i++){
		delete pezziMortiBianco[i];
	}
	for(int i=0; i<pezziViviNero.size(); i++){
		delete pezziViviNero[i];
	}
	for(int i=0; i<pezziMortiNero.size(); i++){
		delete pezziMortiNero[i];
	}
}

bool Scacchiera::sottoScacco(bool colore) const{
	if(colore==COLORE_BIANCO){
		return biancoSottoScacco;
	}
	return neroSottoScacco;
}

bool Scacchiera::move(Scacchista* player, Posizione &partenza, Posizione &arrivo){
	if(!isPositionValid(partenza)||!isPositionValid(arrivo)){
		throw InvalidPosition();
	}
	int rigaVeraPartenza = partenza.riga-1;
	int colonnaVeraPartenza = partenza.colonna-1;
	if(matrice[rigaVeraPartenza][colonnaVeraPartenza]==nullptr){
		// nessun pezzo da spostare: mossa non valida
		return false;
	}
	Pezzo* pezzoDaSpostare = matrice[rigaVeraPartenza][colonnaVeraPartenza];
	bool coloreScacchista = pezzoDaSpostare->getColore();
	if(coloreScacchista!=player->getColore()){
		// Lo scacchista vuole muovere una pedina non sua: mossa non valida
		return false;
	}
	std::vector<Posizione> mosseLegaliPezzoDaSpostare = pezzoDaSpostare->mosseLegali();
	for(auto i=mosseLegaliPezzoDaSpostare.begin(); i!=mosseLegaliPezzoDaSpostare.end(); i++){
	}
	int indicePosDestinazione = -1;
	for(int i=0; i<mosseLegaliPezzoDaSpostare.size(); i++){
		if(mosseLegaliPezzoDaSpostare[i]==arrivo){
			indicePosDestinazione=i;
			break;
		}
	}
	if(indicePosDestinazione<0){
		// mossa non presente tra le mosse legali del pezzo da spostare: mossa non valida
		return false;
	}

	//se si arriva a questo punto la mossa e' sicuramente valida
	std::ofstream fileLog(fileName, std::ofstream::app);
	fileLog<<partenza.getStringa()<<" "<<arrivo.getStringa()<<"\n";
	fileLog.close();
	matrice[rigaVeraPartenza][colonnaVeraPartenza]=nullptr;
	if(mosseLegaliPezzoDaSpostare[indicePosDestinazione].flag==POSIZIONE_FLAG_ARROCCO){
		int rigaVeraArrivo = arrivo.riga-1; //Deve essere rigaVeraPartenza == rigaVeraArrivo
		int colonnaVeraArrivo = arrivo.colonna-1;
		pezzoDaSpostare->setPosizione(arrivo);
		(dynamic_cast<Re*>(pezzoDaSpostare))->setPrimaMossa(0);
		if(partenza.colonna<arrivo.colonna){
			//spostamento verso destra
			Torre* torreDaSpostare = dynamic_cast<Torre*>(matrice[rigaVeraArrivo][7]);
			torreDaSpostare->setPosizione(Posizione(arrivo.riga, arrivo.colonna-1));
			torreDaSpostare->setPrimaMossa(0);
			matrice[rigaVeraArrivo][7]=nullptr;
			matrice[rigaVeraArrivo][colonnaVeraArrivo-1]=torreDaSpostare;
			matrice[rigaVeraArrivo][colonnaVeraArrivo]=pezzoDaSpostare;
			pezzoDaSpostare->setPosizione(arrivo);
		}else{
			//spostamento verso sinistra
			Torre* torreDaSpostare = dynamic_cast<Torre*>(matrice[rigaVeraArrivo][0]);
			torreDaSpostare->setPosizione(Posizione(arrivo.riga, arrivo.colonna+1));
			torreDaSpostare->setPrimaMossa(0);
			matrice[rigaVeraArrivo][0]=nullptr;
			matrice[rigaVeraArrivo][colonnaVeraArrivo+1]=torreDaSpostare;
			matrice[rigaVeraArrivo][colonnaVeraArrivo]=pezzoDaSpostare;
			pezzoDaSpostare->setPosizione(arrivo);
		}
		aggiornaScacco();
		azzeraPedoneFlag(coloreScacchista);

		listaScreen.push_back(stringaScacchiera());
		return true;
	}
	if(mosseLegaliPezzoDaSpostare[indicePosDestinazione].flag==POSIZIONE_FLAG_EN_PASSANT){
		// pedone da mangiare ha posizione (riga di partenza, colonna di arrivo)
		if(coloreScacchista==COLORE_BIANCO){
			pedoneAzzerareFlagDuePassiNero->setDuePassi(0);
			pedoneAzzerareFlagDuePassiNero=nullptr;
		}else{
			pedoneAzzerareFlagDuePassiBianco->setDuePassi(0);
			pedoneAzzerareFlagDuePassiBianco=nullptr;
		}
		int rigaVeraArrivo = arrivo.riga-1;
		int colonnaVeraArrivo = arrivo.colonna-1;
		Pezzo* pedoneDaMangiare = matrice[rigaVeraPartenza][colonnaVeraArrivo];
		matrice[rigaVeraPartenza][colonnaVeraArrivo]=nullptr;
		if(coloreScacchista==COLORE_BIANCO){
			for(auto i=pezziViviNero.begin();i!=pezziViviNero.end(); i++){
				if((*i)==pedoneDaMangiare){
					pezziViviNero.erase(i);
					break;
				}
			}
			pezziMortiNero.push_back(pedoneDaMangiare);
		}else{
			for(auto i=pezziViviBianco.begin();i!=pezziViviBianco.end(); i++){
				if((*i)==pedoneDaMangiare){
					pezziViviBianco.erase(i);
					break;
				}
			}
			pezziMortiBianco.push_back(pedoneDaMangiare);
		}

		pezzoDaSpostare->setPosizione(arrivo);
		matrice[rigaVeraArrivo][colonnaVeraArrivo]=pezzoDaSpostare;
		aggiornaScacco();
		azzeraPedoneFlag(coloreScacchista);

		listaScreen.clear();
		return true;
	}

	//sicuramente non interessa piu' avere info sul flag duePassi, serve solo per en passant
	azzeraPedoneFlag(coloreScacchista);

	//se il pezzo  da muovere e' una torre o un re azzero il flag primaMossa
	if(typeid(*pezzoDaSpostare)==typeid(Re)){
		dynamic_cast<Re*>(pezzoDaSpostare)->setPrimaMossa(0);
	}
	if(typeid(*pezzoDaSpostare)==typeid(Torre)){
		dynamic_cast<Torre*>(pezzoDaSpostare)->setPrimaMossa(0);
	}
	// mossa normale:
	//	-controllare se si deve mangiare
	//		-eventualmente rimuovere dalla lista dei vivi e inserire in quella dei morti
	//	-spostare il pezzo
	//		-se pedone, controllare per promozione, e controllare due passi
	//	-aggiornare situazione scacchi
	bool resetListaScreen=false;
	int rigaVeraArrivo = arrivo.riga-1;
	int colonnaVeraArrivo = arrivo.colonna-1;
	if(matrice[rigaVeraArrivo][colonnaVeraArrivo]!=nullptr){
		resetListaScreen=true;
		// tolgo la pedina dai vivi (verra' sovrascritta nella matrice) e la inserisco nei morti
		Pezzo* pezzoDaMangiare = matrice[rigaVeraArrivo][colonnaVeraArrivo];
		if(coloreScacchista==COLORE_BIANCO){
			for(auto i=pezziViviNero.begin(); i!=pezziViviNero.end(); i++){
				if((*i)==pezzoDaMangiare){
					pezziViviNero.erase(i);
					break;
				}
			}
			pezziMortiNero.push_back(pezzoDaMangiare);
		}else{
			for(auto i=pezziViviBianco.begin(); i!=pezziViviBianco.end(); i++){
				if((*i)==pezzoDaMangiare){
					pezziViviBianco.erase(i);
					break;
				}
			}
			pezziMortiBianco.push_back(pezzoDaMangiare);
		}
	}
	matrice[rigaVeraArrivo][colonnaVeraArrivo]=pezzoDaSpostare;
	pezzoDaSpostare->setPosizione(arrivo);
	
	if(typeid(*pezzoDaSpostare)==typeid(Pedone)){
		resetListaScreen=true;
		Pedone* puntatorePedoneSpostato =  dynamic_cast<Pedone*>(pezzoDaSpostare);
		if((puntatorePedoneSpostato->getDirezione()==DIREZIONE_GIU&&puntatorePedoneSpostato->getPosizione().riga==1)||
			(puntatorePedoneSpostato->getDirezione()==DIREZIONE_SU&&puntatorePedoneSpostato->getPosizione().riga==8)){
			// promozione
			//	-rimuovo il pezzo spostato dalla lista dei vivi
			//	-lo distruggo
			//	-creo la nuova pedina
			//		-se e' una torre metto primaMossa=0
			//	-la inserisco nei pezzi vivi e nella matrice al posto di quella vecchia
			if(coloreScacchista==COLORE_BIANCO){
				for(auto i=pezziViviBianco.begin(); i!=pezziViviBianco.end(); i++){
					if((*i)==pezzoDaSpostare){
						pezziViviBianco.erase(i);
						break;
					}
				}
			}else{
				for(auto i=pezziViviNero.begin(); i!=pezziViviNero.end(); i++){
					if((*i)==pezzoDaSpostare){
						pezziViviNero.erase(i);
						break;
					}
				}
			}

			delete pezzoDaSpostare;

			char caratterePromozione = '\0';
			while(caratterePromozione!='A'&&caratterePromozione!='C'&&caratterePromozione!='D'&&caratterePromozione!='T'){
				caratterePromozione = player->dimmiChiPromuovere();
			}
			std::ofstream fileLog(fileName, std::ofstream::app);
			fileLog<<caratterePromozione<<"\n";
			fileLog.close();
			Pezzo* nuovaPedina=nullptr;

			switch(caratterePromozione){
				case 'A':{
					Alfiere* temp = new Alfiere(arrivo, coloreScacchista, *this);
					nuovaPedina=temp;
					break;
				}
				case 'C':{
					Cavallo* temp = new Cavallo(arrivo, coloreScacchista, *this);
					nuovaPedina=temp;
					break;
				}
				case 'D':{
					Regina* temp = new Regina(arrivo, coloreScacchista, *this);
					nuovaPedina=temp;
					break;
				}
				case 'T':{
					Torre* temp = new Torre(arrivo, coloreScacchista, *this);
					temp->setPrimaMossa(0);
					nuovaPedina=temp;
					break;
				}
			}
			if(coloreScacchista==COLORE_BIANCO){
				pezziViviBianco.push_back(nuovaPedina);
			}else{
				pezziViviNero.push_back(nuovaPedina);
			}

			matrice[rigaVeraArrivo][colonnaVeraArrivo]=nuovaPedina;
			nuovaPedina->setPosizione(arrivo);
		}else{
			if((arrivo.riga-partenza.riga)==2||(arrivo.riga-partenza.riga)==-2){
				puntatorePedoneSpostato->setDuePassi(1);
				if(coloreScacchista==COLORE_BIANCO){
					pedoneAzzerareFlagDuePassiBianco=puntatorePedoneSpostato;
				}else{
					pedoneAzzerareFlagDuePassiNero=puntatorePedoneSpostato;
				}
			}
		}
	}
	aggiornaScacco();
	if(resetListaScreen){
		listaScreen.clear();
	}else{
		listaScreen.push_back(stringaScacchiera());
	}
	return true;


}

void Scacchiera::aggiornaScacco(){
	biancoSottoScacco=false;
	neroSottoScacco=false;
	for(auto i=pezziViviBianco.begin(); !neroSottoScacco&&i!=pezziViviBianco.end(); i++){
		std::vector<Posizione> posAccessibili=(*i)->mosseAccessibili();
		for(auto pos=posAccessibili.begin(); pos!=posAccessibili.end(); pos++){
			int rigaVera = pos->riga-1;
			int colonnaVera = pos->colonna-1;
			if(matrice[rigaVera][colonnaVera]!=nullptr){
				if(typeid(*matrice[rigaVera][colonnaVera])==typeid(Re)){
					neroSottoScacco=true;
					break;
				}
			}
		}
	}
	for(auto i=pezziViviNero.begin(); !biancoSottoScacco&&i!=pezziViviNero.end(); i++){
		std::vector<Posizione> posAccessibili=(*i)->mosseAccessibili();
		for(auto pos=posAccessibili.begin(); pos!=posAccessibili.end(); pos++){
			int rigaVera = pos->riga-1;
			int colonnaVera = pos->colonna-1;
			if(matrice[rigaVera][colonnaVera]!=nullptr){
				if(typeid(*matrice[rigaVera][colonnaVera])==typeid(Re)){
					biancoSottoScacco=true;
					break;
				}
			}
		}
	}
}

void Scacchiera::azzeraPedoneFlag(bool colore){
	if(colore==COLORE_BIANCO){
		if(pedoneAzzerareFlagDuePassiBianco!=nullptr){
			pedoneAzzerareFlagDuePassiBianco->setDuePassi(0);
			pedoneAzzerareFlagDuePassiBianco=nullptr;
		}
		return;
	}
	if(pedoneAzzerareFlagDuePassiNero!=nullptr){
		pedoneAzzerareFlagDuePassiNero->setDuePassi(0);
		pedoneAzzerareFlagDuePassiNero=nullptr;
	}
	return;
}

std::vector<std::unique_ptr<Pezzo>> Scacchiera::pezziVivi(bool colore) const{
	std::vector<std::unique_ptr<Pezzo>> toReturn;
	if(colore==COLORE_BIANCO){
		for(int i=0; i<pezziViviBianco.size(); i++){
			toReturn.push_back(std::unique_ptr<Pezzo>(pezziViviBianco[i]->clone()));
		}
	}else{
		for(int i=0; i<pezziViviNero.size(); i++){
			toReturn.push_back(std::unique_ptr<Pezzo>(pezziViviNero[i]->clone()));
		}
	}
	return toReturn;
}

std::vector<std::unique_ptr<Pezzo>> Scacchiera::pezziMorti(bool colore) const{
	std::vector<std::unique_ptr<Pezzo>> toReturn;
	if(colore==COLORE_BIANCO){
		for(int i=0; i<pezziMortiBianco.size(); i++){
			toReturn.push_back(std::unique_ptr<Pezzo>(pezziMortiBianco[i]->clone()));
		}
	}else{
		for(int i=0; i<pezziMortiNero.size(); i++){
			toReturn.push_back(std::unique_ptr<Pezzo>(pezziMortiNero[i]->clone()));
		}
	}
	return toReturn;
}


Scacchiera::Scacchiera(const std::string &nomeFileLog, const std::string &situazioneIniziale){
	fileName=nomeFileLog;
	if(fileName==""){	// se non viene specificato niente viene usato come nome un timestamp
					// 4 cifre per l'anno, 2 per il mese, 2 per il giorno, 2 per l'ora, 2 per i minuti, 2 per i secondi
		char buff[20];
		time_t rawtime;
		struct tm * timeinfo;	
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		strftime (buff,20,"%Y%m%d%H%M%S",timeinfo);
		for(int i=0; buff[i]!='\0'; i++){
			fileName.push_back(buff[i]);
		}
		fileName="Log"+fileName+".txt";
	}
	for(int i=0; i<NUMERO_RIGHE_SCACCHIERA*NUMERO_COLONNE_SCACCHIERA; i++){
		Pezzo* pezzoDaAggiungere=nullptr;
		int rigaVeraPos=i/8;
		int colonnaVeraPos=i%8;
		Posizione pos(rigaVeraPos+1,colonnaVeraPos+1);
		switch(situazioneIniziale[i]){
			case 'A':{
				pezzoDaAggiungere=new Alfiere(pos, COLORE_NERO, *this);
				break;
			}
			case 'a':{
				pezzoDaAggiungere=new Alfiere(pos, COLORE_BIANCO, *this);
				break;
			}
			case 'C':{
				pezzoDaAggiungere=new Cavallo(pos, COLORE_NERO, *this);
				break;
			}
			case 'c':{
				pezzoDaAggiungere=new Cavallo(pos, COLORE_BIANCO, *this);
				break;
			}
			case 'D':{
				pezzoDaAggiungere=new Regina(pos, COLORE_NERO, *this);
				break;
			}
			case 'd':{
				pezzoDaAggiungere=new Regina(pos, COLORE_BIANCO, *this);
				break;
			}
			case 'T':{
				pezzoDaAggiungere=new Torre(pos, COLORE_NERO, *this);
				(dynamic_cast<Torre*>(pezzoDaAggiungere))->setPrimaMossa(1);
				break;
			}
			case 't':{
				pezzoDaAggiungere=new Torre(pos, COLORE_BIANCO, *this);
				(dynamic_cast<Torre*>(pezzoDaAggiungere))->setPrimaMossa(1);
				break;
			}
			case 'R':{
				Re* nuovoRe = new Re(pos, COLORE_NERO, *this);
				nuovoRe->setPrimaMossa(1);
				pezzoDaAggiungere=nuovoRe;
				break;
			}
			case 'r':{
				Re* nuovoRe = new Re(pos, COLORE_BIANCO, *this);
				nuovoRe->setPrimaMossa(1);
				pezzoDaAggiungere=nuovoRe;
				break;
			}
			case 'P':{
				pezzoDaAggiungere=new Pedone(pos, COLORE_NERO, *this, DIREZIONE_GIU);
				(dynamic_cast<Pedone*>(pezzoDaAggiungere))->setDuePassi(0);
				break;
			}
			case 'p':{
				pezzoDaAggiungere=new Pedone(pos, COLORE_BIANCO, *this, DIREZIONE_SU);
				(dynamic_cast<Pedone*>(pezzoDaAggiungere))->setDuePassi(0);
				break;
			}
		}
		matrice[rigaVeraPos][colonnaVeraPos]=pezzoDaAggiungere;
		if(pezzoDaAggiungere!=nullptr){
			if(pezzoDaAggiungere->getColore()==COLORE_BIANCO){
				pezziViviBianco.push_back(pezzoDaAggiungere);
			}else{
				pezziViviNero.push_back(pezzoDaAggiungere);
			}
		}
	}
	aggiornaScacco();
	pedoneAzzerareFlagDuePassiBianco=nullptr;
	pedoneAzzerareFlagDuePassiNero=nullptr;
}

bool Scacchiera::isLegal(const Posizione &partenza, const Posizione &arrivo){
	if(!isPositionValid(partenza)||!isPositionValid(arrivo)){
		return false;
	}
	bool toReturn=true;
	int rigaVeraPartenza = partenza.riga-1;
	int colonnaVeraPartenza = partenza.colonna-1;
	int rigaVeraArrivo = arrivo.riga-1;
	int colonnaVeraArrivo = arrivo.colonna-1;
	Pezzo* pezzoDaSpostare=matrice[rigaVeraPartenza][colonnaVeraPartenza];
	Pezzo* pezzoDaMangiare=matrice[rigaVeraArrivo][colonnaVeraArrivo];
	if(arrivo.flag==POSIZIONE_FLAG_EN_PASSANT){
		pezzoDaMangiare=matrice[rigaVeraPartenza][colonnaVeraArrivo];
		matrice[rigaVeraPartenza][colonnaVeraArrivo]=nullptr;
	}
	matrice[rigaVeraPartenza][colonnaVeraPartenza]=nullptr;
	if(pezzoDaMangiare!=nullptr){
		if(pezzoDaSpostare->getColore()==COLORE_BIANCO){
			for(auto i=pezziViviNero.begin(); i!=pezziViviNero.end(); i++){
				if((*i)==pezzoDaMangiare){
					pezziViviNero.erase(i);
					break;
				}
			}
		}else{
			for(auto i=pezziViviBianco.begin(); i!=pezziViviBianco.end(); i++){
				if((*i)==pezzoDaMangiare){
					pezziViviBianco.erase(i);
					break;
				}
			}
		}
	}
	matrice[rigaVeraPartenza][colonnaVeraPartenza]=nullptr;
	matrice[rigaVeraArrivo][colonnaVeraArrivo]=pezzoDaSpostare;

	if(pezzoDaSpostare->getColore()==COLORE_BIANCO){
		for(auto i=pezziViviNero.begin(); i!=pezziViviNero.end(); i++){
			std::vector<Posizione> posAccessibili=(*i)->mosseAccessibili();
			for(int j=0; j<posAccessibili.size(); j++){
				Posizione posConsiderata = posAccessibili[j];
				int rigaVeraPosConsiderata = posConsiderata.riga-1;
				int colonnaVeraPosConsiderata = posConsiderata.colonna-1;
				if(matrice[rigaVeraPosConsiderata][colonnaVeraPosConsiderata]!=nullptr&&typeid(*matrice[rigaVeraPosConsiderata][colonnaVeraPosConsiderata])==typeid(Re)){
					toReturn=false;
				}
			}
		}
	}else{
		for(auto i=pezziViviBianco.begin(); i!=pezziViviBianco.end(); i++){
			std::vector<Posizione> posAccessibili=(*i)->mosseAccessibili();
			for(int j=0; j<posAccessibili.size(); j++){
				Posizione posConsiderata = posAccessibili[j];
				int rigaVeraPosConsiderata = posConsiderata.riga-1;
				int colonnaVeraPosConsiderata = posConsiderata.colonna-1;
				if(matrice[rigaVeraPosConsiderata][colonnaVeraPosConsiderata]!=nullptr&&typeid(*matrice[rigaVeraPosConsiderata][colonnaVeraPosConsiderata])==typeid(Re)){
					toReturn=false;
				}
			}
		}
	}

	matrice[rigaVeraPartenza][colonnaVeraPartenza]=pezzoDaSpostare;
	matrice[rigaVeraArrivo][colonnaVeraArrivo]=nullptr;
	if(pezzoDaMangiare!=nullptr){
		int rigaVeraPezzoMangiato = pezzoDaMangiare->getPosizione().riga-1;
		int colonnaVeraPezzoMangiato = pezzoDaMangiare->getPosizione().colonna-1;
		matrice[rigaVeraPezzoMangiato][colonnaVeraPezzoMangiato]=pezzoDaMangiare;
		if(pezzoDaSpostare->getColore()==COLORE_BIANCO){
			pezziViviNero.push_back(pezzoDaMangiare);
		}else{
			pezziViviBianco.push_back(pezzoDaMangiare);
		}
	}
	return toReturn;
}

std::string Scacchiera::stringaScacchiera(bool coloreSotto) const{
	std::string toReturn="";
	if(coloreSotto==COLORE_BIANCO){
		for(int riga=7; riga>=0; riga--){
			toReturn+=('1'+riga);
			toReturn+=' ';
			for(int colonna=0; colonna<8; colonna++){
				if(matrice[riga][colonna]==nullptr){
					toReturn+=' ';
				}else{
					char carattereDaAggiungere;
					if(typeid(*matrice[riga][colonna])==typeid(Re)){
						carattereDaAggiungere='R';
					}else if(typeid(*matrice[riga][colonna])==typeid(Regina)){
						carattereDaAggiungere='D';
					}else if(typeid(*matrice[riga][colonna])==typeid(Torre)){
						carattereDaAggiungere='T';
					}else if(typeid(*matrice[riga][colonna])==typeid(Alfiere)){
						carattereDaAggiungere='A';
					}else if(typeid(*matrice[riga][colonna])==typeid(Cavallo)){
						carattereDaAggiungere='C';
					}else if(typeid(*matrice[riga][colonna])==typeid(Pedone)){
						carattereDaAggiungere='P';
					}
					if(matrice[riga][colonna]->getColore()==COLORE_BIANCO&&(carattereDaAggiungere<='Z'&&carattereDaAggiungere>='A')){
						carattereDaAggiungere+=32;
					}
					toReturn+=carattereDaAggiungere;
				}
			}
			toReturn+='\n';
		}
		toReturn+="\n  ABCDEFGH\n";
	}else{
		for(int riga=0; riga<8; riga++){
			toReturn+=('1'+riga);
			toReturn+=' ';
			for(int colonna=7; colonna>=0; colonna--){
				if(matrice[riga][colonna]==nullptr){
					toReturn+=' ';
				}else{
					char carattereDaAggiungere;
					if(typeid(*matrice[riga][colonna])==typeid(Re)){
						carattereDaAggiungere='R';
					}else if(typeid(*matrice[riga][colonna])==typeid(Regina)){
						carattereDaAggiungere='D';
					}else if(typeid(*matrice[riga][colonna])==typeid(Torre)){
						carattereDaAggiungere='T';
					}else if(typeid(*matrice[riga][colonna])==typeid(Alfiere)){
						carattereDaAggiungere='A';
					}else if(typeid(*matrice[riga][colonna])==typeid(Cavallo)){
						carattereDaAggiungere='C';
					}else if(typeid(*matrice[riga][colonna])==typeid(Pedone)){
						carattereDaAggiungere='P';
					}
					if(matrice[riga][colonna]->getColore()==COLORE_BIANCO&&(carattereDaAggiungere<='Z'&&carattereDaAggiungere>='A')){
						carattereDaAggiungere+=32;
					}
					toReturn+=carattereDaAggiungere;
				}
			}
			toReturn+='\n';
		}
		toReturn+="\n  HGFEDCBA\n";
	}
	return toReturn;
}

bool Scacchiera::patta(bool colore) const{
	/*
		Da https://www.scuolascacchipordenone.eu/scacco-scaccomatto-patta-.html

		Ci sono poi occasioni in cui una partita di scacchi non si conclude con un vincitore, ma con una patta. Sono 5 i casi per cui una partita di scacchi può finire in parità:
		1. La partita si conclude con uno stallo, quando il giocatore a cui tocca muovere non può eseguire alcuna mossa legale ed il suo re NON si trova sotto scacco
		2. I giocatori possono semplicemente accordarsi per la patta e smettere di giocare.
		3. Non ci sono abbastanza pezzi sulla scacchiera per poter forzare lo scacco matto (per esempio: un Re ed un Alfiere contro un Re)
		4. Un giocatore può dichiarare la patta nel momento in cui la medesima posizione si ripresenta per la terza volta nel corso della partita (non necessariamente per tre volte consecutive)
		5. Sono state giocate 50 mosse consecutive senza che uno dei due giocatori abbia spostato un pedone o catturato un pezzo.
		
		In caso l'utente voglia applicare la condizione 2 si usi la combinazione da tastiera CTRL+C o si chiuda il prompt in cui e' eseguito il programma
	*/
	// Per la condizione 1 riciclo il codice degli scacchisti
	std::vector<std::unique_ptr<Pezzo>> pezzi = pezziVivi(colore);
	bool trovato = false;
	for (auto i = 0; i < pezzi.size(); i++){
		if (pezzi[i]->mosseLegali().size() > 0){
			trovato = true;
			break;
		}
	}
	if (!trovato&&!sottoScacco(colore)){
		// Condizione 1: stallo
		return true;
	}

	// Riferimento alla lista https://www.scacchi64.com/teoria_finali_teoricamente_patti.html
	// Controllo tutti i casi a mano

	// RE vs RE
	if(pezziViviBianco.size()==1&&pezziViviNero.size()==1){
		//Se rimane un pezzo a testa e' sicuramente un re
		return true;
	}
	// RE + CAVALLO vs RE
	// RE + ALFIERE vs RE
	if(pezziViviBianco.size()==2&&pezziViviNero.size()==1){
		// Nero ha solo re
		// bianco ha cavallo o alfiere?
		Pezzo* nonRe=pezziViviBianco[0];
		if(typeid(*nonRe)==typeid(Re)){
			nonRe=pezziViviBianco[1];
		}
		if(typeid(*nonRe)==typeid(Cavallo)||typeid(*nonRe)==typeid(Alfiere)){
			return true;
		}
	}
	if(pezziViviBianco.size()==1&&pezziViviNero.size()==2){
		// Bianco ha solo re
		// nero ha cavallo o alfiere?
		Pezzo* nonRe=pezziViviNero[0];
		if(typeid(*nonRe)==typeid(Re)){
			nonRe=pezziViviNero[1];
		}
		if(typeid(*nonRe)==typeid(Cavallo)||typeid(*nonRe)==typeid(Alfiere)){
			return true;
		}
	}
	//RE + ALFIERE vs RE + ALFIERE stesso colore
	if(pezziViviBianco.size()==2&&pezziViviNero.size()==2){
		Pezzo* nonReBianco=pezziViviBianco[0];
		if(typeid(*nonReBianco)==typeid(Re)){
			nonReBianco=pezziViviBianco[1];
		}
		Pezzo* nonReNero=pezziViviNero[0];
		if(typeid(*nonReNero)==typeid(Re)){
			nonReNero=pezziViviNero[1];
		}
		if(typeid(*nonReNero)==typeid(Alfiere)&&typeid(*nonReBianco)==typeid(Alfiere)){
			if(((nonReBianco->getPosizione().riga+nonReBianco->getPosizione().colonna)%2)==((nonReNero->getPosizione().riga+nonReNero->getPosizione().colonna)%2)){
				return true;
			}
		}
	}
	// Condizioni 4 e 5: Su wikipedia https://it.wikipedia.org/wiki/Patta_(scacchi) si distinguono i numeri di mosse e di ripetizioni di posizione
	// per una patta opzionale e per una obbligatoria (50/75 mosse, 3/5 ripetizioni).
	// Sul regolamento FIDE http://www.arbitriscacchi.com/up_file/439-Laws_of_Chess_Italiano.pdf pero' non si fa riferimento a questa distinzione,
	// quindi consideriamo 3 e 50 come numero di ripetizioni e mosse rispettivamente.

	// Per la gestione 4 e 5 tengo traccia degli screenshot della situazione della scacchiera
	//	si puo' usare stringaScacchiera, potrebbe essere piu' efficiente con un array di char senza caratteri aggiuntivi
	//	uso un vector, forse potrebbe essere piu' efficiente con una mappa

	if(listaScreen.size()>=50){
		// Condizione 4: (almeno) 50 mosse senza mangiare o muovere pedone
		return true;
	}
	// Per la condizione 5 controllo solo l'ultimo "screen" inserito: se c'e' una patta non se ne potranno inserire altri
	if(listaScreen.size()>0){
		std::string ultimoScreen = listaScreen[listaScreen.size()-1];
		int contatore=0;
		for(auto i=listaScreen.begin(); i!=listaScreen.end(); i++){
			if((*i)==ultimoScreen){
				contatore++;
			}
		}
		if(contatore>=3){
			// Condizione 5: stessa situazione si verifica 3 volte, anche non consecutive
			return true;
		}
	}
	return false;
}