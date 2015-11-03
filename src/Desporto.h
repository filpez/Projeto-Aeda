/*
 * Desporto.h
 *
 *  Created on: 14/10/2015
 *      Author: Filipe
 */

#ifndef SRC_DESPORTO_H_
#define SRC_DESPORTO_H_

#include <string>
#include <vector>
#include "Modalidade.h"

using namespace std;

struct Pontuacao{
	string nome;
	bool crescente; // se a pontuacao e crescente ou nao
};

class Desporto{
	string nome;
	vector<Modalidade *> modalidades;
	Pontuacao pontuacao;
public:
	Desporto();
	Desporto(string n, string pont, bool cresc);
	string getNome() const;
	string getPontuacao() const;
	bool isCrescente() const;
	bool adicionaModalidade(Modalidade *m);
	bool operator== (const Desporto & c) const;
	friend ostream & operator<<(ostream & o, const Desporto & d);
};


//class Corrida{
//
//public:
//	Corrida(){};
//	Corrida(string n, string pont);
//};
//
//class Natacao{
//
//public:
//	Natacao(){};
//	Natacao(string n, string pont);
//};
//
//class Futebol{
//	int
//public:
//	Futebol(){};
//	Futebol(string n, string pont);
//};

class DesportoEquipa: public Desporto{
	int numeroAtletas;
public:
	DesportoEquipa(){};
	DesportoEquipa(string n, string pont, bool cresc, int num);
};

class DesportoSolo: public Desporto{
public:
	DesportoSolo(){};
	DesportoSolo(string n, string pont, bool cresc);
};


#endif /* SRC_DESPORTO_H_ */

///*
// * Desporto.h
// *
// *  Created on: 14/10/2015
// *      Author: Filipe
// */
//
//#ifndef SRC_DESPORTO_H_
//#define SRC_DESPORTO_H_
//
//#include <string>
//#include <vector>
//#include "Data.h"
//
//using namespace std;
//
//struct Pontuacao{
//	string nome;
//	bool crescente; // se a pontuacao e crescente ou nao
//};
//
//class Desporto{
//	string nome;
//	vector<Modalidade *> modalidades; // o stor tinha dito que era um conjunto de modalidades
//	Pontuacao pontuacao; //fiz uma struct, mas se for preciso ser classe depois mudasse
//public:
//	Desporto();
//	Desporto(string n, string pont, bool cresc);
//
//	string getNome() const;
//	string getPontuacao() const;
//	bool isCrescente() const;
//
//	bool operator== (const Desporto & c) const;
//	friend ostream & operator<<(ostream & o, const Desporto & d);
//
//	void adicionaModalidade();
//	void menuModalidades();
//
//
//};
//
//class ModalidadeExiste{
//	string nome;
//public:
//	ModalidadeExiste();
//	ModalidadeExiste(string n);
//	string getNome() const;
//};
//
//class Modalidade{
//	string nome;
//	Hora duracao;
//	Desporto* desporto;
//
//public:
//	Modalidade();
//	Modalidade(string n, int h, int m, Desporto *d);
//
//	string getNome() const;
//	Hora getDuracao() const;
//	Desporto* getDesporto() const;
//
//	bool operator== (const Modalidade & c) const;
//	friend ostream & operator<<(ostream & o, const Modalidade & d);
//
//	void menu();
//};
//
//
////class Desporto{
////	string nome;
////	vector<Equipas *> equipas;
////public:
////	string getNome() const;
////};
//
//
//
//#endif /* SRC_DESPORTO_H_ */
