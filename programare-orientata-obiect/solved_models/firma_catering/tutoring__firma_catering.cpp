#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

class Comanda {
	//am nevoie de 4 atribute
	//unul sa fie const sau static
	//de un atribut alocat dinamic(un pointer)
	const int idComanda;
	string numeClient;
	int ziComanda;
	int nrProduse;
	float* preturiProduse;
public:
	Comanda():idComanda(0) {
		this->numeClient = "X";
		this->ziComanda = 1;
		this->nrProduse = 0;
		this->preturiProduse = NULL;
	}

	int getZiComanda() {
		return this->ziComanda;
	}

	void setZiComanda(int ziComanda) {
		if (ziComanda >= 1 && ziComanda <= 31) {
			this->ziComanda = ziComanda;
		}
	}

	Comanda(const int idComanda, string numeClient, int ziComanda, int nrProduse, float* preturiProduse) :idComanda(idComanda) {
		//validarile in constructori se fac pe PARAMETRII!!
		//la validarile in constructori va rog sa va puneti si ramura de else

		//validarea pentru string se face in functie de numarul de caractere
		if (numeClient.size() >= 3) {
			this->numeClient = numeClient;
		}
		else {
			this->numeClient = "Necunoscut";
		}

		if (ziComanda >= 1 && ziComanda <= 31) {
			this->ziComanda = ziComanda;
		}
		else {
			this->ziComanda = 1;
		}
		if (nrProduse > 0 && preturiProduse != NULL) {
			this->nrProduse = nrProduse;
			this->preturiProduse = new float[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++) {
				this->preturiProduse[i] = preturiProduse[i];
			}
		}
		else {
			this->nrProduse = 0;
			this->preturiProduse = NULL;
		}
		
	}

	Comanda(const Comanda& c) :idComanda(c.idComanda) {
		if (c.numeClient.size() >= 3) {
			this->numeClient = c.numeClient;
		}
		else {
			this->numeClient = "Necunoscut";
		}

		if (c.ziComanda >= 1 && c.ziComanda <= 31) {
			this->ziComanda = c.ziComanda;
		}
		else {
			this->ziComanda = 1;
		}
		if (c.nrProduse > 0 && c.preturiProduse != NULL) {
			this->nrProduse = c.nrProduse;
			this->preturiProduse = new float[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++) {
				this->preturiProduse[i] = c.preturiProduse[i];
			}
		}
		else {
			this->nrProduse = 0;
			this->preturiProduse = NULL;
		}
	}

	//in destructor dezalocam ce este alocat dinamic
	~Comanda() {
		if (this->preturiProduse != NULL) {
			delete[]this->preturiProduse;
		}
		//this->preturiProduse = NULL;
		//cout << "S-a apelat destructorul!" << endl;
	}
	
	Comanda& operator=(const Comanda& c) {
		if (this != &c) {
			if (this->preturiProduse != NULL) {
				delete[]this->preturiProduse;
			}
			if (c.numeClient.size() >= 3) {
				this->numeClient = c.numeClient;
			}
			else {
				this->numeClient = "Necunoscut";
			}

			if (c.ziComanda >= 1 && c.ziComanda <= 31) {
				this->ziComanda = c.ziComanda;
			}
			else {
				this->ziComanda = 1;
			}
			if (c.nrProduse > 0 && c.preturiProduse != NULL) {
				this->nrProduse = c.nrProduse;
				this->preturiProduse = new float[this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++) {
					this->preturiProduse[i] = c.preturiProduse[i];
				}
			}
			else {
				this->nrProduse = 0;
				this->preturiProduse = NULL;
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Comanda& c) {
		out << c.idComanda << endl;
		out << c.numeClient << endl;
		out << c.ziComanda << endl;
		out << c.nrProduse << endl;
		for (int i = 0; i < c.nrProduse; i++) {
			out << c.preturiProduse[i] << endl;
		}
		return out;
		
	}
	//ofstream si ifstream sunt ostream si istream fara atribute statice/constante si fara comentarii 
	//aditionale!!!!
	friend ofstream& operator<<(ofstream& out, const Comanda& c) {
		out << c.numeClient << endl;
		out << c.ziComanda << endl;
		out << c.nrProduse << endl;
		for (int i = 0; i < c.nrProduse; i++) {
			out << c.preturiProduse[i] << endl;
		}
		return out;

	}
	/*friend istream& operator>>(istream& in, Comanda& c) {

	}*/
	friend ifstream& operator>>(ifstream& in, Comanda& c) {
		delete[]c.preturiProduse;
		getline(in, c.numeClient);
		in >> c.ziComanda;
		in >> c.nrProduse;
		c.preturiProduse = new float[c.nrProduse];
		for (int i = 0; i < c.nrProduse; i++) {
			in >> c.preturiProduse[i];
		}
		return in;
	}

	 static void aplicaFiltruFisierText(int nrComenzi, Comanda* comenzi, int nrZiComanda) {
		ofstream f("exportFisFiltre.txt", ios::out);
		for (int i = 0; i < nrComenzi; i++) {
			if (comenzi[i].getZiComanda() <= nrZiComanda) {
				f << comenzi[i] << endl;
			}
		}
		f.close();
	}

	 void aplicaFiltruFisierText(int nrZiComanda) {
		 if (this->ziComanda <= nrZiComanda) {
		 ofstream f("exportFisFiltreSingle.txt", ::out);
			f <<*this << endl;
			 f.close();	
		 }
	 }
	

	//operator[] -- operatorul de indexare/index

	float& operator[](int poz) {
		if (poz >= 0 && poz < this->nrProduse) {
			return this->preturiProduse[poz];
		}
		else {
			float eroare = -1;
			return eroare;
		}
	}

	//post incrementare

	Comanda operator++(int) {
		Comanda copie = *this;//constructorul de copiere 
		for (int i = 0; i < this->nrProduse; i++) {
			this->preturiProduse[i]++;
		}
		return copie;
	}

	//pre incrementare

	Comanda& operator++() {
		for (int i = 0; i < this->nrProduse; i++) {
			++this->preturiProduse[i];
		}
		return *this;
	}
};

void schimbaValori(int a, int b) {
	int aux = a;
	a = b;
	b = aux;
}

int main() {
	Comanda c;
	cout << c.getZiComanda() << endl << endl;
	c.setZiComanda(14);
	c.setZiComanda(55);
	c.setZiComanda(-5);
	cout << c.getZiComanda() << endl << endl;

	float preturi[] = { 19.5,111.3,54.1,65.1,66.4,77.4,98.11 };
	Comanda c1(15, "Ionel", 17, 7, preturi);
	cout << c1.getZiComanda() << endl << endl;

	Comanda c2 = c;
	cout << c2.getZiComanda() << endl << endl;

	c2 = c1;
	cout << c2.getZiComanda() << endl << endl;

	cout << c2 << endl;

	cout << c2[3] << endl;
	cout << c2[16] << endl;
	cout << c2[-1] << endl << endl;

	c2[3] = 11.11;

	cout << c2 << endl;

	//post-incrementare
	Comanda c3 = c2++;
	cout << c3 << endl;
	cout << c2 << endl;
	cout << endl << endl;

	//pre-incrementare
	Comanda c4 = ++c2;
	cout << c4 << endl;
	cout << c2 << endl;
	cout << endl << endl;

	ofstream f("exempluFis.txt", ios::out);
	f << c2;
	f.close();

	Comanda cText;
	cout << cText << endl << endl;
	ifstream g("exempluFis.txt", ios::in);
	if (g.is_open()) {
		g >> cText;
		g.close();
		cout << cText << endl;
	}
	else {
		cout << "Nu s-a gasit fisierul cautat!" << endl;
	}

	cout << endl << endl << endl;
	cout << "=========================== STL===========================" << endl << endl;
	//stl --> standard template library
	vector<Comanda> vectComenzi;

	///inserare 
	vectComenzi.push_back(c);
	vectComenzi.push_back(c1);
	vectComenzi.push_back(c2);
	vectComenzi.push_back(c2);
	vectComenzi.push_back(c2);
	vectComenzi.push_back(c2);
	vectComenzi.push_back(c2);
	vectComenzi.push_back(c2);
	vectComenzi.push_back(c3);
	vectComenzi.push_back(c4);
	vectComenzi.push_back(c);
	vectComenzi.push_back(c);
	vectComenzi.push_back(c);

	for (int i = 0; i < vectComenzi.size(); i++) {
		cout << vectComenzi[i] << endl;
	}

	cout << endl << endl << endl;

	//stergem cu pop_back();
	vectComenzi.pop_back();
	vectComenzi.pop_back();
	vectComenzi.pop_back();

	for (int i = 0; i < vectComenzi.size(); i++) {
		cout << vectComenzi[i] << endl;
	}

	cout << endl << endl << endl;

	//comanda erase de stergere
	vectComenzi.erase(vectComenzi.begin());
	vectComenzi.erase(vectComenzi.end() - 1);
	for (int i = 0; i < vectComenzi.size(); i++) {
		cout << vectComenzi[i] << endl;
	}

	cout << endl << endl << endl;

	vectComenzi.erase(vectComenzi.begin() + 1, vectComenzi.end() - 2);//[,)

	for (int i = 0; i < vectComenzi.size(); i++) {
		cout << vectComenzi[i] << endl;
	}

	cout << endl << endl << endl;
	Comanda com(8, "Dorel", 26, 3, preturi);
	Comanda com1(43, "Ioana", 13, 2, preturi);
	Comanda com2(11, "Maria", 12, 6, preturi);
	Comanda com3(76, "Jimmy", 30, 4, preturi);
	Comanda com4(55, "Alexandra", 27, 5, preturi);

	Comanda* vComenzi = new Comanda[5];
	vComenzi[0] = com;
	vComenzi[1] = com1;
	vComenzi[2] = com2;
	vComenzi[3] = com3;
	vComenzi[4] = com4;

	ofstream fEx("scrieObj.txt", ios::out);
	for (int i = 0; i < 4; i++)
	{
		fEx << vComenzi[i]<<endl;
	}
	fEx.close();

	Comanda::aplicaFiltruFisierText(5, vComenzi, 25);

	com.aplicaFiltruFisierText(25);
	com1.aplicaFiltruFisierText(25);
	com2.aplicaFiltruFisierText(25);
	com3.aplicaFiltruFisierText(25);
	com4.aplicaFiltruFisierText(25);
}