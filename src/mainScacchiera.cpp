// Riccardo De Simoni
#include "ForwardDeclaration.h"
#include "Scacchiera.h"
#include "Scacchista.h"
#include "Pezzo.h"
#include "Giocatore.h"
#include "Computer.h"
#include "Alfiere.h"
#include <time.h>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "L'eseguibile necessita di almeno un parametro, riprovare\n";
        return 0;
    }
    if (!((argv[1][0] != '\0' && argv[1][0] == 'p' && argv[1][1] != '\0' && argv[1][1] == 'c')) &&
        !((argv[1][0] != '\0' && argv[1][0] == 'c' && argv[1][1] != '\0' && argv[1][1] == 'c')))
    {
        std::cout << "Parametro da riga di comando non valido, riprovare\n";
        return 0;
    }
    srand(time(NULL));

    bool coloreRandom = rand() % 2;

    Scacchiera scacchieraEasyInput;
    Scacchista *giocatoreUno;
    Scacchista *giocatoreDue;
    int counterScambi = -1;
    bool stampaComputer = false;

    if (argv[1][0] != '\0' && argv[1][0] == 'p' && argv[1][1] != '\0' && argv[1][1] == 'c')
    {
        stampaComputer = true;
        std::cout << "giocatore vs computer\n";
        giocatoreUno = new Giocatore(coloreRandom, scacchieraEasyInput);
        giocatoreDue = new Computer(!coloreRandom, scacchieraEasyInput);
        if (giocatoreUno->getColore() == false)
        {
            std::cout << "Sei il giocatore bianco, muovi i pezzi minuscoli!\n";
        }
        else
        {
            std::cout << "Sei il giocatore nero, muovi i pezzi maiuscoli!\n";
        }
    }
    else if (argv[1][0] != '\0' && argv[1][0] == 'c' && argv[1][1] != '\0' && argv[1][1] == 'c')
    {
        counterScambi = 40;
        giocatoreUno = new Computer(coloreRandom, scacchieraEasyInput);
        giocatoreDue = new Computer(!coloreRandom, scacchieraEasyInput);
    }
    else
    {

        std::cout << "Parametro da riga di comando non valido, riprovare\n";
        return 0;
    }

    int vittoria = 0;

    while (true)
    {
        if (giocatoreUno->getColore() == false)
        {
            vittoria = giocatoreUno->faiMossa();

            if (vittoria == 1)
            { // patta
                std::cout << "Partita terminata (patta)\n";
                break;
            }
            else if (vittoria == 2)
            { // scaccomatto
                if (giocatoreUno->getColore())
                {
                    std::cout << "Partita terminata: vittoria del bianco\n";
                }
                else
                {
                    std::cout << "Partita terminata: vittoria del nero\n";
                }
                break;
            }
            vittoria = giocatoreDue->faiMossa();
            if (!vittoria && stampaComputer)
                std::cout << "\nMossa Computer: " << dynamic_cast<Computer *>(giocatoreDue)->lastMove() << "\n";
            if (vittoria == 1)
            { // patta
                std::cout << "Partita terminata (patta)\n";
                break;
            }
            else if (vittoria == 2)
            { // scaccomatto
                if (giocatoreDue->getColore())
                {
                    std::cout << "Partita terminata: vittoria del bianco\n";
                }
                else
                {
                    std::cout << "Partita terminata: vittoria del nero\n";
                }
                break;
            }
        }
        else if (giocatoreUno->getColore() == true)
        {
            vittoria = giocatoreDue->faiMossa();
            if (!vittoria && stampaComputer)
                std::cout << "\nMossa Computer: " << dynamic_cast<Computer *>(giocatoreDue)->lastMove() << "\n";

            if (vittoria == 1)
            { // patta
                std::cout << "Partita terminata (patta)\n";
                break;
            }
            else if (vittoria == 2)
            { // scaccomatto
                if (giocatoreDue->getColore())
                {
                    std::cout << "Partita terminata: vittoria del bianco\n";
                }
                else
                {
                    std::cout << "Partita terminata: vittoria del nero\n";
                }
                break;
            }
            vittoria = giocatoreUno->faiMossa();

            if (vittoria == 1)
            { // patta
                std::cout << "Partita terminata (patta)\n";
                break;
            }
            else if (vittoria == 2)
            { // scaccomatto
                if (giocatoreUno->getColore())
                {
                    std::cout << "Partita terminata: vittoria del bianco\n";
                }
                else
                {
                    std::cout << "Partita terminata: vittoria del nero\n";
                }
                break;
            }
        }
        if (counterScambi > 0)
        {
            counterScambi--;
        }
        if (counterScambi == 0)
        {
            std::cout << "Partita interrotta: limite mosse raggiunto\n";
            break;
        }
    }
    delete giocatoreUno;
    delete giocatoreDue;

    return 0;
}