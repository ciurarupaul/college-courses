/*
Definiti clase care sa permita abstractizarea conceptului de frizerie (denumire, numar frizeri, tipFrizerie, etc), folosind membri de tip public, private, protected, const, static. Clasa va permite urmatoarele apeluri in programul principal:

    Frizerie f1;
    Frizerie f2 ("La Mihai", tipFrizerie::barberShop, 3); // denumire char*, tipul este un enum definit anterior (salon, clasica, barbrShop)
    Frizerie f3 = f2;
    Frizerie::setLungimeMinimaDenumire(5);
    c3.setDenumire("El Saloon"); // va valida lungimea pe baza setarii anterioare
    cout << c3.getDenumire();

    - Supraincarcati operatorii de citire si afisare la consola. Operatorul de citire permite utilizarea de siruri de caractere cu spatii;
    - Sa se exemplifice conceptul de clasa abstracta (Serviciu) si derivare (Tuns, Frezat, Barbierit). Clasa abstracta impune o metoda de calcul a pretului
    - Exemplificati conceptul de virtualizare in clasa de frizerie prin utilizarea unui vector de pointeri la servicii. Se va adauga o metoda ce calculeaza pretul total al serviciilor solicitate;
    - Supraincarcati operatorii += si -= pentru a adauga si sterge servicii;
    - Sa se utilizeze un container STL adecvat ce ajuta la gasirea rapida a pretului unui serviciu pe baza denumirii acestuia;

*/

using namespace std;
#include <iostream>     
#include <fstream>
#include <cstring>      // strlen

class Frizerie{
public:
    enum class TipFrizerie {salon, clasica, barber_shop};

protected:
    const int id_frizerie;

private:
    const char* denumire; // must be a const char since string literals ("") are immutable
    int numar_frizeri;
    TipFrizerie tip_frizerie;
    static int lungime_minima_denumire;
    static int nr_frizerii;

public:
    // constructor
    Frizerie(const char *denumire = nullptr, int nr_frizeri = 1, TipFrizerie tip_frizerie = TipFrizerie::salon);

    // destructor
    ~Frizerie();

};

// initialize statics
int Frizerie::nr_frizerii {0};
int Frizerie::lungime_minima_denumire {10};

// constructor
Frizerie::Frizerie(const char *denumire_in, int nr_frizeri_in, TipFrizerie tip_frizerie_in)
    : id_frizerie{++nr_frizerii}, denumire{nullptr}, numar_frizeri{nr_frizeri_in}, tip_frizerie{tip_frizerie_in}
{
    cout << "Creating a new frizerie" << endl;

    if(denumire_in != nullptr){
        size_t len = strlen(denumire_in);

        char* temp = new char[len + 1];
        strcpy(temp, denumire_in);
        denumire = temp;                    // point here
    }
}

// destructor
Frizerie::~Frizerie(){
    delete [] denumire;
}

// overload = operator

// setLungimeMinimaDenumire

// f1.setDenumire() cu validare de min

// overload << >> 

int main(){
    Frizerie f1;
    Frizerie f2 ("El Saloon", 3, Frizerie::TipFrizerie::barber_shop);

    return 0;
}


