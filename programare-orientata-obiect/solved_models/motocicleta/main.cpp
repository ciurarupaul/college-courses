/*
Definiti clase care sa permita gestiunea datelor aferente unei motociclete (producator, numar drumuri, distante parcurse) folosind membri de tip public, private, protected, const, static. Clasa va permite urmatoarele apeluri in programul principal:
	- Motocicleta m1;
	- Motocicleta m2 ("Suzuki", 3, new int[3] {100, 150, 120});
	- Motocicleta m3 = m2;
	- Motocicleta::tipPermis = 'B';
	- m2.setProducator("Yamaha");

	(1p) Supraincarcati o functie a clasei pentru a ilustra conceptul de early binding
	(2p) Sa se serializeze intr-un fisier binar detaliile legate de motocicleta. Sa se adauge si optiune de deserializare
	(2p) Sa se exemplifice utilizarea unei specilizari plecand de la ideea ca pot exista si motociclete electrice
	(1p) Adaugati clasei un membru pointer si ilustrati modul de apel al constructorului de copiere
	(1p) Sa se utilizeze o clasa STL adecvata ce permite cautarea rapida a unei motociclete dupa model
*/

// #DEFINE CRT_SECURE_NO_WARNINGS
using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Motocicleta {
protected:
	string producator;

private:
	int nr_drumuri;
	int* drumuri_parcurse;
	static unsigned int nr_motociclete;

public:
	// constructor, constructor copiere, destructor
	Motocicleta(string producator = "", int nr_drumuri = 0, int *drumuri_parcurse = nullptr);
	Motocicleta(const Motocicleta& source);
	~Motocicleta();

	// supraincarcare operatori
	friend ostream& operator<<(ostream& os, const Motocicleta& source);

	// gettere
	string getProducator() const { return producator; }
	int getNumarDrumuri() const { return nr_drumuri; }
	int* getDrumuriParcurse() const { return drumuri_parcurse; }
	unsigned int getNrMotociclete() const { return nr_motociclete; }
};

unsigned int Motocicleta::nr_motociclete = 0;

// constructor
Motocicleta::Motocicleta(string producator, int nr_drumuri, int* drumuri_parcurse)
	: producator{ producator }, nr_drumuri{ nr_drumuri }, drumuri_parcurse{ nullptr } 
{
	if (nr_drumuri > 0 && drumuri_parcurse != nullptr) {
		this->drumuri_parcurse = new int[nr_drumuri];
		for (int i{ 0 }; i < nr_drumuri; i++) {
			this->drumuri_parcurse[i] = drumuri_parcurse[i];
		}
	}

	++nr_motociclete;
}

// constructor copiere
Motocicleta::Motocicleta(const Motocicleta& source)
	: Motocicleta{ source.producator, source.nr_drumuri, source.drumuri_parcurse } {}

// destructor
Motocicleta::~Motocicleta() {
	delete[] drumuri_parcurse;
	drumuri_parcurse = nullptr;
}

// supraincarcare <<
ostream& operator<<(ostream& os, const Motocicleta& source) {
	cout << endl;
	os << "producator: " << source.getProducator() << endl;
	os << "nr_drumuri: " << source.nr_drumuri << endl;
	
	os << "drumuri_parcurse: ";
	if (source.nr_drumuri > 0 && source.drumuri_parcurse != nullptr) {
		for (size_t i{ 0 }; i < source.nr_drumuri; i++) {
			os << source.drumuri_parcurse[i] << " ";
		}
	}
	os << endl;

	return os;
}
int main() {
	Motocicleta m1;
	cout << m1;

	return 0;
}
