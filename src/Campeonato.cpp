#include "Campeonato.h"
#include <iostream>
#include "Lists.h"

using namespace std;

bool ficheiroExiste(const string &ficheiro)
{
	bool existe = false;
	ifstream ficheiro_tab;
	ficheiro_tab.open(ficheiro.c_str());		// abre o ficheiro...
	if (ficheiro_tab.is_open())			// ... e verifica se a abertura do ficheiro foi bem-sucedida
	{
		existe = true;
		ficheiro_tab.close();			// volta a fechar o ficheiro
	}
	return existe;
}

vector<Desporto *> Campeonato::getDesportos() const
{
	return desportos;
}

vector<Prova> Campeonato::getProvas() const
{
	return provas;
}

Campeonato::Campeonato(string n, Data i, Data f)
{
	nome = n;
	inicio = i;
	fim = f;
}

bool Campeonato::adicionaProva(Prova p)
{

	if (p.getData() < inicio || fim < p.getData())
		return false;
	else
	{
		Hora abertura(8,0);
		Hora fecho(20,0);
		Hora fimProva = p.getInicio() + p.getModalidade().getDuracao();

		if (p.getInicio() < abertura || fecho < fimProva)
			return false;
		else
		{
			if (provas.size() == 0)
			{
				provas.push_back(p);
				return true;
			}
			else
			{
				for (unsigned int i = 0; i < provas.size(); i++)
				{
					bool simultaneo = provas[i].Simultaneo(p);

					if (simultaneo)
						return false;
				}
			}
		}
	}

	provas.push_back(p);
	return true;
}

bool Campeonato::criaDesportosCampeonato(string nome_ficheiro)
{
	int elementos_equipa;
	char barra;
	char crescente;
	bool c;
	ifstream in;

	if (!ficheiroExiste(nome_ficheiro))
		return false;

	in.open(nome_ficheiro.c_str());

	while (!in.eof())
	{
		string desporto = "";
		string tipo_de_pontuacao = "";

		in >> elementos_equipa;
		in >> barra;

		string extraido = "";

		if (!in.eof())
			do
			{
				in >> extraido;
				if (extraido != "/")
					desporto = desporto + extraido;
			} while (extraido != "/");

		extraido = "";

		in >> tipo_de_pontuacao;
		in >> barra;
		in >> crescente;


		if (crescente == 'C')
			c = true;
		else if (crescente == 'D')
			c = false;
		else return false;

		if (elementos_equipa == 0)
			return false;
		else {
			Desporto ds (desporto, tipo_de_pontuacao, c, elementos_equipa);
			desportos.push_back(&ds);
		}
	}

	in.close();

	return true;
}

void Campeonato::menuCriacao(){
	bool exit = false;
	while (!exit){
		system("cls");
		vector<string> choices;
		choices.push_back("Modalidades");
		if(desportos.size() > 0){
			choices.push_back("Equipas");
			choices.push_back("Provas");
		}
		int ch = fazMenu("Campeonato Polidesportivo", choices);
		if (ch == -1)
			exit = true;
//		else if (ch == 0)
//			menuModalidades();
		else if (ch == 1)
			menuEquipas();
//		else
//			menuProvas();
	}
}

void Campeonato::menuEquipas(){
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Equipas:", equipas, "Nova Equipa");
		if (ch == -1)
			exit = true;
		else if (ch < equipas.size())
			//equipas[ch]->menu();
			equipas[ch]->getNome();
		else{
			try{
				adicionaEquipa();
			}
			catch (EquipaExiste eq){
				cout << "Equipa \"" << eq.getNome() << "\" ja existe.";
				_getch();
			}

		}

	}
}

void Campeonato::adicionaEquipa(){
	string n;

	system("cls");

	cout << "Nome: ";
	getline(cin, n);
	cin.ignore(10000,'\n');

	Equipa *eq = new Equipa(n);
	if (search(equipas , *eq) != -1)
		throw EquipaExiste(n);
	equipas.push_back(eq);
}

void atribuiPontuacao(Prova pro, vector< float> pontos){
	int primeiro = -1;
	int segundo = -1;

	if (pontos.size() < 3) {
		cout <<"-2";
		if (pro.getModalidade().getDesporto()->isCrescente())
			if (pontos[0] > pontos[1])
				primeiro = 0;
			else
				primeiro = 1;

		else {
			if (pontos[0] > pontos[1])
				primeiro = 1;
			else
				primeiro = 0;
		}

		// nao e preciso devolver nada
		//	vector<Atleta> rankingProva;
		//
		//	rankingProva.push_back(pro.getAtletas()[primeiro]);
		//	rankingProva.push_back(pro.getAtletas()[segundo]);
		//	rankingProva.push_back(pro.getAtletas()[terceiro]);

	pro.getAtletas()[primeiro]->adicionaPontuacao(3);
}
	else {
		cout << "+2";
		int terceiro = -1;

			int menor = pontos[0];
			int segundoMenor = pontos[1];
			int terceiroMenor = pontos[2];

			int maior = pontos[0];
			int segundoMaior = pontos[1];
			int terceiroMaior = pontos[2];

			if (pro.getModalidade().getDesporto()->isCrescente()) {
				for (unsigned int i = 0; i < pontos.size(); i++)
					if (pontos[i] > maior) {
						terceiroMaior = segundoMaior;
						segundoMaior = maior;
						maior = pontos[i];
						terceiro = segundo;
						segundo = primeiro;
						primeiro = i;
					} else if (pontos[i] > segundoMaior) {
						terceiroMaior = segundoMaior;
						segundoMaior = pontos[i];
						terceiro = segundo;
						segundo = i;
					}
			} else
				for (unsigned int i = 0; i < pontos.size(); i++)
					if (pontos[i] < menor) {
						terceiroMenor = segundoMenor;
						segundoMenor = menor;
						menor = pontos[i];
						terceiro = segundo;
						segundo = primeiro;
						primeiro = i;
					} else if (pontos[i] < segundoMenor) {
						terceiroMenor = segundoMenor;
						segundoMenor = pontos[i];
						terceiro = segundo;
						segundo = i;
					}

		// nao e preciso devolver nada
		//	vector<Atleta> rankingProva;
		//
		//	rankingProva.push_back(pro.getAtletas()[primeiro]);
		//	rankingProva.push_back(pro.getAtletas()[segundo]);
		//	rankingProva.push_back(pro.getAtletas()[terceiro]);

			pro.getAtletas()[primeiro]->adicionaPontuacao(3);
			pro.getAtletas()[segundo]->adicionaPontuacao(2);
			pro.getAtletas()[terceiro]->adicionaPontuacao(1);

	}
}

bool Campeonato::criaEquipasCampeonato(string nome_ficheiro)
{
	char barra;
	char genero;
	ifstream in;

	if (!ficheiroExiste(nome_ficheiro))
	{
		cerr << "O ficheiro Equipas.txt nao existe!";
		return false;
	}

	in.open(nome_ficheiro.c_str());

	while (!in.eof())
	{
		string equipa = "";
		string atleta = "";

		string extraido = "";

		if (!in.eof())
			do
			{
				in >> extraido;
				if (extraido != "/")
					equipa = equipa + extraido;
			} while (extraido != "/");

		extraido = "";

		if (!in.eof())
			do
			{
				in >> extraido;
				if (extraido != "/")
					atleta = atleta + extraido;
			} while (extraido != "/");

		in >> genero;

		Equipa * eq = new Equipa(equipa);
		Atleta * at = new Atleta(atleta, eq);
		int indiceEquipa = -1;

		for (unsigned int i = 0; i < equipas.size(); i++)
		{
			if (equipa == equipas[i]->getNome())
				indiceEquipa = i;

		}

		if (indiceEquipa == -1)
		{
			equipas.push_back(eq);
			eq->adicionaAtleta(at);
		}
		else
		{
			equipas[indiceEquipa]->adicionaAtleta(at);
		}

	}

		in.close();

		return true;
}
