#include "Prova.h"
#include "Lists.h"

Prova::Prova(Modalidade* m, Data d, Hora i, char g)
{
	modalidade = m;
	data = d;
	inicio = i;
	fim = i + m->getDuracao();
	if (g == 'M')
		genero = true;
	else genero = false;
	realizada = false;
}

Hora Prova::getInicio() const
{
	return inicio;
}

Hora Prova::getFim() const
{
	return fim;
}

Data Prova::getData() const
{
	return data;
}

Modalidade* Prova::getModalidade() const{
	return modalidade;
}

vector<Atleta*> Prova::getAtletas() const{
	return atletas;
}

bool  Prova::getGenero() const{
	return genero;
}

bool Prova::getRealizada() const{
	return realizada;
}

bool Prova::Simultaneo(Prova p)
{
	if (p.getData() < data || data < p.getData())
		return false;
	else
	{
		if (p.getInicio() < inicio)
			if (p.getFim() < inicio)
				return false;
		if (fim < p.getFim())
			if (fim < p.getInicio())
				return false;

	}
	return true;

}

void Prova::adicionaAtleta(Atleta * a){
	int indice = -1;

	for (unsigned int i = 0; i < atletas.size(); i++)
		{
		if (a->getNome() == atletas[i]->getNome())
			indice = i;
		}

	if (indice == -1)
		atletas.push_back(a);
}


void Prova::apagaAtleta(string nome)
{
	for(unsigned int i = 0; i < atletas.size(); i++)
	{
		if (atletas[i]->getNome() == nome)
			atletas.erase(atletas.begin()+i);
	}
}

ostream & operator<<(ostream & o, const Prova & p){
	o << p.data << " " << p.inicio << "-" << p.fim << "  "<< p.modalidade->getNome();
	return o;
}


bool Prova::operator < (const Prova &p2) const{
	if (getData() < p2.getData())
		return true;
	else if (getData() == p2.getData()){
		if (getInicio() < p2.getInicio())
			return true;
		else if (getInicio() > p2.getInicio())
			return false;
		else {
			if (getModalidade()->getNome() < p2.getModalidade()->getNome())
				return true;
			else return false;
		}
	} else return false;
}

bool Prova::operator ==(const Prova &p2) const {

	if(realizada != p2.getRealizada())
		return false;
	if (genero != p2.getGenero())
		return false;
	else if (modalidade->getNome() != p2.getModalidade()->getNome())
		return false;
	else if (!(data == p2.getData()))
		return false;
	else if (inicio < p2.getInicio() || inicio > p2.getInicio())
		return false;
	else{
		return true;
	}
}

void Prova::adicionarAtleta(vector<Equipa*> TeamList){
	bool exit = false;
	while (!exit){
		system("cls");

		int ch = fazMenu("Selecionar Equipa:", TeamList);
		if (ch == -1)
			exit = true;
		else{
			if (search(TeamList[ch]->getDesportos(), *modalidade->getDesporto()) == -1){
					cout << "A equipa " << TeamList[ch]->getNome() << " nao esta inscrita no desporto " << modalidade->getDesporto()->getNome() << ".\n";
				_getch();
			}
			else{
				bool exit2 = false;
				while (!exit2){
					system("cls");
					int ch2 = fazMenu("Selecionar Atleta:", TeamList[ch]->getAtletas());
					if (ch2 == -1)
						{
						exit2 = true;
						}
					else{
						if (search(atletas, *TeamList[ch]->getAtletas()[ch2]) == -1){
							atletas.push_back(TeamList[ch]->getAtletas()[ch2]);
							TeamList[ch]->getAtletas()[ch2]->adicionaProva(this);
							return;
						}
						else{
							system("cls");
							cout << "O atleta " << TeamList[ch]->getAtletas()[ch2]->getNome() << " ja esta inscrito.\n";
							_getch();
							return;
						}
					}
				}
			}
		}
	}
}

void Prova::retirarAtleta(){
	system("cls");

	if (atletas.size() == 0){
		cout << "Nao existem atletas inscritos.";
		_getch();
		return;
	}
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Selecionar Atletas:", atletas);
		if (ch == -1)
			exit = true;
		else{
			for (int i = 0; i < atletas[ch]->getProvas().size();i++){
				if (atletas[ch]->getProvas()[i]==this){
					atletas[ch]->apagaProva(i);
					break;
				}
			}
//			int i = search(atletas[ch]->getProvas(), *this);
//			atletas[ch]->getProvas().erase(atletas[ch]->getProvas().begin() + i);
			atletas.erase(atletas.begin()+ch);
			exit = true;
		}
	}
}

void Prova::menu(vector<Equipa*> TeamList){
	bool exit = false;
	while (!exit){
		system("cls");
		vector<string> choices;
		choices.push_back("Adicionar Atletas");
		choices.push_back("Retirar Atletas");

		cout << *this;
		cout << endl;
		int ch = fazMenu("Opcoes", choices);
		if (ch == -1)
			exit = true;
		else if (ch == 0)
			adicionarAtleta(TeamList);
		else
			retirarAtleta();
	}
}

void Prova::setInicio(Data d, Hora i){
	data = d;
	inicio = i;
	fim = i + modalidade->getDuracao();
}

void Prova::setRealizada(bool r){
	realizada = true;
}


/*
------------------------------------------------------------------------------
						    Prova Terminada
------------------------------------------------------------------------------
 */

ProvaTerminada::ProvaTerminada(Modalidade* m, Data d, Hora i, char g) :Prova(m, d, i, g) {realizada = true;}


Atleta* ProvaTerminada::getPrimeiro() const{
	return atletas[0];
}

Atleta* ProvaTerminada::getSegundo() const{
	return atletas[1];
}

Atleta*ProvaTerminada:: getTerceiro() const{
	return atletas[2];
}

void ProvaTerminada::setAtletas (vector<Atleta*> a) {
	atletas = a;
}

void ProvaTerminada::setPontuacoes(vector<float> pont){
	pontuacoes = pont;
}

void ProvaTerminada::setPontuacoesAtletas(vector<pair <Atleta*, float> > atletasPontos){
	for(unsigned int i = 0; i < atletasPontos.size() && i < atletas.size(); i++){
		atletas[i] = atletasPontos[i].first;
	}

	if (getAtletas().size() <= 2) {
		atletas[0]->adicionaPontuacao(3);
	} else {
		atletas[0]->adicionaPontuacao(3);
		atletas[1]->adicionaPontuacao(2);
		atletas[2]->adicionaPontuacao(1);
	}
}

void ProvaTerminada::setPontuacoesAtletasRev(vector<pair <Atleta*, float> > atletasPontos){
	if (getAtletas().size() <= 2) {
		atletasPontos[getAtletas().size() - 1].first->adicionaPontuacao(3);
	} else {
		atletasPontos[getAtletas().size() - 1].first->adicionaPontuacao(3);
		atletasPontos[getAtletas().size() - 2].first->adicionaPontuacao(2);
		atletasPontos[getAtletas().size() - 3].first->adicionaPontuacao(1);
	}

	for(unsigned int i = 0; i < atletasPontos.size() && i < atletas.size(); i++){

	}

}

vector <float> ProvaTerminada::getPontuacoes() const{
	return pontuacoes;
}

bool ProvaTerminada:: operator < (const ProvaTerminada &p) const{
	if (getData()< p.getData())
		return true;
	return false;
}


