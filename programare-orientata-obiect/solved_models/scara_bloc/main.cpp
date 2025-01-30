/*
(3p)Se considera o aplicatie care permite gestiunea unei scari de bloc. Se vor urmari aspecte comune privind denumire, adresa, apartamente, locatari, etc. Definiti o clasa care modeleaza un aspect propriu acestei activitati. Datele membre sunt private si sunt puse la dispozitie metode de acces. CLasa contine cel putin patru campuri, dintre care unul este alocat dinamic, constructori, metode specifice claselor cu membri alocati dinamic si operatorul de afisare. Folositi un membru static sau const.
    - (1p) supraincarcati operator[] oentru accesarea elementelor din vectorul alocat dinamic al clasei. Operatorul poate di dolosit si pentru citire si pentru modificare
    - (1p) creati o noua clasa Bloc, care sa contina mai multe obiecte de tipul Scara. Elementele pot fi gestionate si prin pointeri. Colectia de elemente de tip Scara este gestionata printr-un vector alocat dinamic
    - (2p) Oferiti posibilitatea ca prin operator+= sa fie adaugata o noua scara in cadrul unui obiect de tip Bloc
    - (2p) In cadrul clasei Bloc implementati doua metode: una returneaza scara cea mai productiva, iar cea de-a doua metoda returneaza scara cel mai putin productiva din cadrul blocului
    - (1p) Clasa Bloc trebuie sa contina o metoda care sa ofere posibilitatea de calculare a unei sume pentru toate obiectele gestionate
*/

using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Scara{
    friend ostream &operator<<(ostream &os, const Scara &scara);

private:
    string *denumire;
    const string adresa;
    unsigned int nr_apartamente;
    unsigned int *locatari_per_apartament; // pentru supraincarcare []

public:
    // constructor, copy constructor, destructor
    Scara(string *denumire = nullptr, string adresa = "", unsigned int nr_apartamente = 0, unsigned int *locatari_per_apartament = nullptr);
    Scara(const Scara &source);
    ~Scara();

    // operators
    unsigned int &operator[](size_t idx);

    // getters
    string getDenumire() const {return *denumire;}
    string getAdresa() const {return adresa;}
    int getNrApartamente() const {return nr_apartamente;}
    int getNrLocatariScara(){
        unsigned int sum{0};
        for(size_t i{0}; i < nr_apartamente; i++){
            sum += locatari_per_apartament[i];
        }

        return sum;
    }
};

// constructor
Scara::Scara(string *denumire, string adresa, unsigned int nr_apartamente, unsigned int *locatari_per_apartament)
    : denumire{nullptr}, adresa{adresa}, nr_apartamente{nr_apartamente}, locatari_per_apartament{nullptr}{
        if(denumire != nullptr)
            this->denumire = new string(*denumire);
        else
            this->denumire = new string("");

        if(locatari_per_apartament != nullptr && nr_apartamente > 0){
            this->locatari_per_apartament = new unsigned int [nr_apartamente];

            for(size_t i {0}; i < nr_apartamente; i++){
                this->locatari_per_apartament[i] = locatari_per_apartament[i];
            }
        }
    }

// copy constructor
Scara::Scara(const Scara &source)
    : Scara {source.denumire, source.adresa, source.nr_apartamente, source.locatari_per_apartament}{}

// destructor
Scara::~Scara(){
    delete denumire;
    denumire = nullptr;

    delete locatari_per_apartament;
    locatari_per_apartament = nullptr;
}

//  <<
ostream &operator<< (ostream &os, const Scara &scara){
    cout << endl;
    os << "denumire " << *scara.denumire << endl;       // dereference !!!!
    os << "adresa " << scara.adresa << endl;
    os << "nr_apartamente " << scara.nr_apartamente << endl;

    os << "locatari_per_apartament ";
    for(size_t i {0}; i < scara.nr_apartamente; i++){
        os << scara.locatari_per_apartament[i] << " ";
    }

    cout << endl;
    return os;
}

// 
//      - (1p) supraincarcati operator[] oentru accesarea elementelor din vectorul alocat dinamic al clasei. Operatorul poate fi folosit si pentru citire si pentru modificare
//

// return & to allow direct modification
unsigned int &Scara::operator[](size_t idx){
    if(idx >= nr_apartamente || locatari_per_apartament == nullptr){}
        // throw ex
    return locatari_per_apartament[idx];
}

// 
//      - (1p) creati o noua clasa Bloc, care sa contina mai multe obiecte de tipul Scara. Elementele pot fi gestionate si prin pointeri. Colectia de elemente de tip Scara este gestionata printr-un vector alocat dinamic
// 
class Bloc{
    Scara** scari;          // dynamically allocated array of pointers to Scara objects
    static int nr_scari;

public:
    // constructor + destructor
    Bloc() : scari(nullptr){}
    ~Bloc() {
        for (int i = 0; i < nr_scari; ++i) {
            delete scari[i];
        }
        delete[] scari;
    }

    // overload +=
    Bloc &operator+=(const Scara &scara);

    // getters
    static int getNrScari() {return nr_scari;}
    Scara **getScari() {return scari;}

    // methods
    Scara* getMostProductive();
    Scara* getLeastProductive();

    unsigned int getTotalLocatariBloc();
};

int Bloc::nr_scari = 0;

// 
//      - (2p) Oferiti posibilitatea ca prin operator+= sa fie adaugata o noua scara in cadrul unui obiect de tip Bloc
// 
Bloc &Bloc::operator+=(const Scara &scara){
    // 1. increase the size of the arr
    Scara** newScari = new Scara*[nr_scari + 1];

    // 2. copy the old into the new one
    for (int i = 0; i < nr_scari; ++i) {
        newScari[i] = scari[i];
    }

    // 3. allocate memory for the new object
    newScari[nr_scari] = new Scara(scara); // uses the copy constructor from Scara

    // 4. update pointer to point at the right location
    delete[] scari;     // delete old
    scari = newScari;   // point to new location

    ++nr_scari;
    return *this;
}

// 
//      - (2p) In cadrul clasei Bloc implementati doua metode: una returneaza scara cea mai productiva, iar cea de-a doua metoda returneaza scara cel mai putin productiva din cadrul blocului
// 

Scara* Bloc::getMostProductive() {
    Scara* mostProductive = scari[0];
    for (size_t i{1}; i < nr_scari; ++i) {
        if (scari[i]->getNrLocatariScara() > mostProductive->getNrLocatariScara()) {
            mostProductive = scari[i];
        }
    }
    return mostProductive;
}

Scara* Bloc::getLeastProductive() {
    Scara* leastProductive = scari[0];
    for (size_t i{1}; i < nr_scari; ++i) {
        if (scari[i]->getNrLocatariScara() < leastProductive->getNrLocatariScara()) {
            leastProductive = scari[i];
        }
    }
    return leastProductive;
}

// 
//      - (1p) Clasa Bloc trebuie sa contina o metoda care sa ofere posibilitatea de calculare a unei sume pentru toate obiectele gestionate
//

unsigned int Bloc::getTotalLocatariBloc(){
    unsigned int totalLocatari{0};

    // scari[i] in acest caz e un pointer la o instanta Scara si actioneaza exact la this
    for(size_t i{0}; i < getNrScari(); i++){
        totalLocatari += scari[i]->getNrLocatariScara();
    }

    return totalLocatari;
}


int main (){
    string denumire = "Generic building";
    string adresa = "Generic address";
    int nr_apartamente = 12;
    unsigned int locatari_per_apt[] {1, 2 , 0, 3, 3, 2, 0, 1, 4, 1, 3, 2};
    int alt_nr_apartamente = 3;
    unsigned int alt_locatari[] {0, 2, 3};

    Scara s1(&denumire, adresa, nr_apartamente, locatari_per_apt);
    Scara s2(&denumire, adresa, alt_nr_apartamente, alt_locatari);
    Scara s3;

    Bloc bloc;
    bloc += s1;
    bloc += s2;
    bloc += s3;

/*
    cout << s1 << s2 << s3;

    // test getters
    cout << s1.getAdresa() << " " << s1.getDenumire() << " " << s1.getNrApartamente()<< endl;

    // test []
    cout << s1[2] << endl;;
    s1[2] = 5;
    cout << s1[2] << endl;

    test Bloc and += op
 

    cout << "Total scari: " << Bloc::getNrScari() << endl;

    for(size_t i{0}; i < Bloc::getNrScari(); i++){
        cout << *bloc.getScari()[i] << endl;
    }

    // test getNrLocatariScara
    cout << s1.getNrLocatariScara() << endl;

    // test most/least productive
    cout << *bloc.getMostProductive() << endl;
    cout << *bloc.getLeastProductive() << endl;
*/

    // test total locatari din bloc
    cout << bloc.getTotalLocatariBloc() << endl;

    return 0;
}