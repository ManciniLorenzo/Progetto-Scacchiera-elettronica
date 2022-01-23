//Riccardo Di Bella
#ifndef POSIZIONE_H
#define POSIZIONE_H

#include <string>

constexpr int POSIZIONE_NO_FLAG = 0;
constexpr int POSIZIONE_FLAG_ARROCCO = 1;
constexpr int POSIZIONE_FLAG_EN_PASSANT = 2;
class Posizione{
	// contiene Riga e colonna da 1 a 8
	// costruita direttamente o con stringa posizione
	public:
		int riga;
		int colonna;
		int flag;
		Posizione(int r, int c, int f=POSIZIONE_NO_FLAG): riga {r}, colonna {c}, flag{f} {}
		//stringa posizione:
		//	primo carattere: Colonna (maiuscolo o minuscolo)
		//	carattere: riga (numerico)
		Posizione(std::string s, int f=POSIZIONE_NO_FLAG){
			if(s[0]<='Z'&&s[0]>='A'){
				colonna=s[0]-'A'+1;
			}else{
				colonna=s[0]-'a'+1;
			}
			riga=s[1]-'0';
			flag=f;
		}
		//operator== e operator!= confrontano solo riga e colonna, non flag
		bool operator==(Posizione &p){
			return riga==p.riga&&colonna==p.colonna;
		}
		bool operator!=(Posizione &p){
			return !((*this)==p);
		}
		std::string getStringa() const{
			std::string str="";
			str+=static_cast<char>('A'-1+colonna);
			str+=('0'+riga);
			return str;
		}
};
#endif