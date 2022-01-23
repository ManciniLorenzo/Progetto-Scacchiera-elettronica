// Riccardo De Simoni

#include "ForwardDeclaration.h"
#include "Scacchiera.h"
#include "Scacchista.h"
#include "Pezzo.h"
#include "Giocatore.h"
#include "Computer.h"
#include "Alfiere.h"
#include "Log.h"
#include <time.h>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    if(argc<3){
        std::cout<<"L'eseguibile necessita di almeno 2 parametri, riprovare\n";
        return 0;
    }
    if (argv[1][0] != 'v'&&argv[1][0] != 'f'){
        std::cout<<"Parametro da riga di comando non valido, riprovare\n";
        return 0;
    }
    std::ifstream inputFile;
    try
    {

        inputFile = std::ifstream(argv[2]);
    }
    catch (...)
    {
        std::cout << "Errore apertura file di input"
                  << "\n";
        return 0;
    }
    if(!inputFile){
        // il file di input non esiste o non e' stato aperto correttamente
        std::cout << "Errore apertura file di input\n";
        return 0;
    }

    Scacchiera scacchieraInputFile;
    Log primoP(0, scacchieraInputFile, inputFile);
    Log secondoP(1, scacchieraInputFile, inputFile);

    if (argv[1][0] == 'v')
    {
        int vittoria = 0;
        try
        {
            while (true)
            {
                vittoria = primoP.faiMossa();
                std::cout << scacchieraInputFile.stringaScacchiera() << "\n";
                
                         

                if (vittoria == 1 || vittoria == 2)
                {
                    if(vittoria==1){
                        std::cout << "Partita terminata (patta)\n";
                    }else{
                        std::cout << "Partita terminata: vittoria del nero\n";
                    }
                    break;
                }
                vittoria = secondoP.faiMossa();
                std::cout << scacchieraInputFile.stringaScacchiera() << "\n";
                

                if (vittoria == 1 || vittoria == 2){
                    if(vittoria==1){
                        std::cout << "Partita terminata (patta)\n";
                    }else{
                        std::cout << "Partita terminata: vittoria del bianco\n";
                    }
                    break;
                }
            }
        }
        catch (Log::MoveNonEseguito)
        {
            std::cout << "Partita interrotta\n";
        }
    }
    else if (argv[1][0] == 'f')
    {
        int vittoria=0;
        if(argc==3){
            std::cout<<"Non e' stato specificato nessun file per l'output, riprovare\n";
        }
        std::ofstream filegrafico(argv[3]);
        try
        {
            while (true)
            {
                vittoria = primoP.faiMossa();
                filegrafico << scacchieraInputFile.stringaScacchiera() << "\n";

                if (vittoria == 1 || vittoria == 2)
                {
                    if(vittoria==1){
                        filegrafico << "Partita terminata (patta)\n";
                    }else{
                        filegrafico << "Partita terminata: vittoria del nero\n";
                    }
                    break;
                }
                vittoria = secondoP.faiMossa();
                filegrafico << scacchieraInputFile.stringaScacchiera() << "\n";

                if (vittoria == 1 || vittoria == 2)
                {
                    if(vittoria==1){
                        filegrafico << "Partita terminata (patta)\n";
                    }else{
                        filegrafico << "Partita terminata: vittoria del bianco\n";
                    }
                    break;
                }
            }
        }
        catch (Log::MoveNonEseguito)
        {
            filegrafico << "Partita interrotta\n";
        }

        filegrafico.close();
    }

    return 0;
}