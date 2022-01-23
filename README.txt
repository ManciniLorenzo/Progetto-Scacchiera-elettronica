Corso di Laboratorio di Programmazione @ UNIPD
Progetto finale - Scacchiera elettronica

Autori:
Mancini Lorenzo
De Simoni Riccardo
Di Bella Riccardo


Questo progetto implementa una scacchiera elettronica mediante linguaggio C++.
Vengono messe a disposizione funzionalita' per giocare partite umano vs cpu, simulare
partite cpu vs cpu e visualizzare replay di partite precedenti.


Organizzazione generale del progetto:

Il progetto è gestito tramite due file main (descritti in seguito) che utilizzano un oggetto
di tipo Scacchiera per tenere traccia della partita in corso; ciascun file main gestirà inoltre
due oggetti di tipo Scacchista, che si occuperanno di gestire la scelta delle mosse da fare
a seconda del tipo di input desiderato (lettura da tastiera: Giocatore, mossa casuale: Computer,
lettura da file di log: Log) e di effettuarla tramite la Scacchiera.
Il comportamento di uno scacchista "Computer" (presente nelle partite umano vs cpu e cpu vs cpu),
che verrà descritto piu' precisamente in seguito, e' da considerarsi casuale e in nessun modo
intelligente, pur mantenento il rispetto delle mosse legali nel gioco degli scacchi.
La scacchiera tiene traccia delle pedine nelle diverse posizioni attraverso oggetti di tipo Pezzo,
che attraverso diverse sottoclassi (una per tipo di pedina) realizzano i diversi comportamenti di
ciascun tipo di pezzo.


Compilazione e file eseguibili:

La compilazione del progetto e' stata gestita tramite CMake. La procedura di compilazione e' quella
standard e puo' variare a seconda del sistema operativo, della versione di cmake utilizzata o di
altre esigenze. Il flag -O2 e' stato impostato, come richiesto dalla consegna, nel file CMakeLists.
Nel progetto sono stati usati spesso strumenti introdotti con C++11 o versioni successive: sebbene
non sia stato imposto un vincolo di versione tramite CMakeLists.txt si consiglia l'uso di versioni
di GCC sufficientemente recenti da supportare questi standard.
Per risolvere problemi legati ad inclusioni cicliche tra i file e' stato creato il file
ForwardDeclaration.h, contenente le dichiarazioni di tutte le classi coinvolte nel progetto; questo
file deve venire incluso come prima istruzione da qualsiasi altro file sorgente per evitare problemi
di compilazione correlati.
Come da consegna, durante la compilazione sono generati due eseguibili: scacchiera e replay.
Con l'eseguibile scacchiera e' possibile giocare una partita umano vs cpu o cpu vs cpu (inserendo
come parametro da riga di comando pc o cc rispettivamente). Tramite l'eseguibile replay si possono
visualizzare a video (parametro v) o scrivere su file (parametro f e parametro aggiuntivo per il
nome del file) tutti gli stati in cui viene a trovarsi la scacchiera durante lo svolgimento di una
partita il cui file di log viene fornito come parametro.
Durante ogni esecuzione verra' generato un file di log contenente tutte le mosse effettuate durante
la partita e le eventuali promozioni, il cui nome sara' un timestamp (vedi sezione "Scacchiera").


Scacchiera:

Lo scopo di un oggetto di tipo scacchiera e' quello di tenere traccia dello stato della partita
durante tutta la sua durata, fornire agli scacchisti e ai pezzi le informazioni necessarie al suo
corretto svolgimento e gestire il file di log di output. La scacchiera e' l'unico oggetto che
"conosce" le mosse fatte da ciascuno scacchista e che ha accesso "in scrittura" alle pedine di
ciascun colore. 
Il costruttore di Scacchiera accetta due parametri opzionali: un nome per il file di log (se non
viene specificato il nome di default e' un timestamp formato da Log + 4 cifre per l'anno, 2 per
il mese, 2 per il giorno, 2 per l'ora, 2 per i minuti, 2 per i secondi). Si puo' quindi ragionevolmente
supporre che il nome di default del file sia univoco per ogni esecuzione, e non si rischia quindi
di sovrascrivere un file di una partita precedente per errore. Il secondo parametro del costruttore
e' una stringa che codifica la situazione iniziale (con caratteri con lo stesso formato di quelli della
stampa, spazio dove non siano previste pedine) da cui deve iniziare la partita; questo parametro e' utile
solamente come strumento di debug e non garantisce l'inizio corretto di una partita in una situazione
diversa da quella iniziale "standard".
Come membro pubblico di Scacchiera e' presente la classe InvalidPosition, una cui istanza verra' lanciata 
in caso in qualche funzione venga passata come parametro una posizione (tipo Position, una classe che mette
a disposizione funzioni utili per gestire una posizione di tipo riga-colonna sulla scacchiera) non valida.
Scacchiera mette a disposizione le funzioni isLegal (ritorna true se la mossa non espone il proprio Re a
uno scacco da parte dell'avversario), sottoScacco (ritorna true se il giocatore del colore passato come
argomento e' sotto scacco) e patta (ritorna true se il giocatore deve dichiarare la partita terminata con
una patta, per maggiori informazioni o chiarimenti sulle situazioni di patta considerate si vedano i
commenti all'interno della funzione).
La funzione get restituisce una copia della eventuale pedina che si trova alla posizione specificata. Piu'
precisamente, viene ritornato uno smart pointer contenente l'indirizzo di una copia di quella pedina
(ottenuta con la funzione clone di pezzo). Questo meccanismo e' necessario perche', essendo i pezzi 
memorizzati sempre tramite puntatori (per evitare problemi di slicing), fornendo ad altre parti del
programma esterne a Scacchiera un puntatore al pezzo "originale" si potrebbe invocare su di esso una
funzione come setColore o setPosizione, rischiando di invalidare lo stato della partita e causare
risultati incoerenti. La memoria di tutti i pezzi e' allocata nel free store per evitare problemi di
"uscita dallo scope" ed, essendo il numero massimo di pezzi limitato, non e' stato ritenuto necessario
trovare una soluzione diversa eventualmente piu' conveniente in termini di prestazioni (analogamente, 
anche la memoria per gli scacchisti nei main e' stata allocata nel free store per lo stesso motivo). Anche 
i cloni ritornati con get e altre funzioni si trovano nel free store e vengono gestiti tramite unique_ptr
per garantire che la loro memoria venga deallocata appena non sono piu' necessari, evitando cosi' di
appesantire l'uso delle funzioni di Scacchiera che usano questo meccanismo. Altre due funzioni che
utilizzano questo sistema di gestione dei cloni sono pezziVivi/pezziMorti, che ritornano i pezzi sulla
scacchiera o mangiati per il giocatore specificato.
La funzione move di Scacchiera e' quella che bisogna invocare quando uno Scacchista vuole effettuare
una mossa: necessita come parametri di un puntatore a uno scacchista (per avere informazioni sul suo
colore e avere qualcosa a cui chiedere informazioni riguardo ad una eventuale promozione di un pedone)
e due posizioni per partenza e arrivo.
Costruttore e assegnamento di copia sono state disabilitate (e di conseguenza anche quelle di spostamento)
per evitare problemi conseguenti alla duplicazione di tutte le pedine e dello stato della partita, in quanto
per gli scopi del progetto queste funzioni non sono in nessun modo necessarie.
Con il distruttore di Scacchiera si dealloca la memoria di tutte le pedine.
Il file di log gestito da Scacchiera viene aperto prima di ogni lettura da effettuare e chiuso subito
dopo per evitare che, in caso di interruzione prematura della partita, il file rimanga vuoto, incompleto
o danneggiato.


Pezzo e sottoclassi:

Un oggetto di classe Pezzo identifica una singola pedina all'interno di una partita. Pezzo e' una classe
virtuale (il suo costruttore non e' pubblico): non puo' esistere una pedina semplicemente di tipo pezzo,
devono tutte essere di una sua classe derivata (Alfiere Cavallo Pedone Re Regina o Torre) che ne definisca
i comportamenti concreti delle funzioni, che in pezzo sono virtuali e non implementate. La classe Pezzo fornisce 
anche l'implementazione di semplici funzioni comuni a tutte le pedine (getter e setter). Per quanto riguarda
l'utilizzo (o mancato utilizzo) di getTipoPezzo si possono trovare informazioni aggiuntive in un commento
all'inizio del file Scacchiera.cpp . Dove necessario, per alcune sotto classi sono stati aggiunti funzioni
per la modifica di flag relativi allo stato della pedina (esempio: torre e re non ancora mossi, pedone mosso
nel turno precedente).
Ciascuna sottoclasse di Pezzo deve fornire un'implementazione delle funzioni mosseAccessibili e mosseLegali:
mosseAccessibili deve ritornare tutte le posizioni in cui una pedina si puo' spostare secondo i movimenti
previsti per il suo tipo dal regolamento senza considerare eventuali scacchi al proprio Re, mentre mosseLegali
fornisce un sottoinsieme delle mosseAccessibili della pedina, eliminando le mosse che espongono il proprio Re
a scacco (in realta' mosseLegali non e' esattamente un sottoinsieme di mosseAccessibili poiche' mosse come 
l'arrocco e la cattura en-passant non possono catturare il Re avversario, e non risultano utili quindi per le 
situazioni in cui viene usata mosseAccessibili invece di mosseLegali).


Scacchista e sottoclassi:

La classe Scacchista e' quella che descrive in modo generale i comportamenti che devono essere realizzati 
concretamente dalle tre sottoclassi che rappresentano i tre tipi di "giocatore" previsti, in particolare le 
funzioni faiMossa e dimmiChiPromuovere: la prima viene invocata dai main e si deve concludere dopo che viene
effettuata una mossa oppure viene segnalata una condizione di scaccomatto o patta, la seconda viene invocata
da Scacchiera quando durante move un pedone arriva "alla fine" della scacchiera e deve essere scelta la pedina
in cui promuoverlo.
Giocatore e' la sottoclasse che realizza l'interazione con l'utente umano: entrambe le funzioni chiedono all'utente
di inserire dei dati corretti fino a quando questi non vengono forniti.
Log e' la sottoclasse dedicata alla lettura delle mosse dal file di log fornito come parametro al costruttore:
legge una riga alla volta le posizioni di partenza ed arrivo analogamente a come vengono scritte da scacchiera
(in modo che due Log possano leggere, uno alla volta, dallo stesso file) e le esegue con move, segnalando con il
lancio di un'eccezione al main che la mossa non e' stata eseguita (questo errore non e' in nessun modo risolvibile
all'interno della classe Log, che ha come unica informazione il file da cui leggere). Analogamente, per la promozione
viene letto dal file un carattere che viene "inoltrato" alla scacchiera.
Computer e' la sottoclasse che sceglie in modo casuale (qui di seguito definito) le mosse e le pedine da promuovere.
La funzione faiMossa e' implementata in modo che, se non si e' in condizione di scacco o patta, partendo dalla lista
dei propri pezzi vivi se ne sceglie uno in modo casuale: se non ha nessuna mossa legale disponibile lo rimuove dalla
lista e ripete la scelta casuale, altrimenti sceglie a caso una delle sue mosse legali. In generale questa modalita'
non sceglie a caso una mossa con probabilita' uniforme all'interno dell'insieme delle mosse legali dello scacchista,
ma assegnera' una probabilita' piu' alta (per singola mossa) alle mosse delle pedine con meno elementi in mosseLegali.
La scelta della pedina in dimmiChiPromuovere e' fatta in modo casuale tra le quattro opzioni possibili. Computer ha
anche un'altra funzione, lastMove, necessaria per poter, dal main, stampare la mossa effettuata dal computer quando
necessario.