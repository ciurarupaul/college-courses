/*
Se considera o aplicatie pentru gestionarea activitatii unei firme de catering. Definiti o clasa cu numele/denumirea clientului, data si durata evenimentului, produse si cantitatile comandate, preturi ... . Aceasta contine cel putin patru campuri, dintre care unul este alocat dinamic, unul este static sau const, constructori, metodele specifice ...

    - Se va defini operatorul [] pentru a accesa un produs dupa pozitia data
    - Definiti operatorul ++ (post si pre incrementare) pentru cresterea cu o unitate a preturilor
    - Scrieti intr un fisier text comenzile care indeplinesc un criteriu dat, primit ca parametru
    - Exemplificati conceptul de virtualizare si late biding prin utilizarea unei clase abstracte
    - Propuneti un container STL care permite efectuarea  rapida a operatiilor de inserare/stergere
*/

using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>

// error handling class
class ComandaException : public exception {
    string message;

public:
    explicit ComandaException(const string &msg) : message(msg){}

   const char *what() const noexcept override {
        return message.c_str();
    }
};

class Comanda{
    friend class Comenzi;
    friend ostream &operator<<(ostream &os, const Comanda &comanda);
    friend istream &operator>>(istream &in, Comanda &comanda);

private:
    const int id_comanda;
    string nume_client;
    int zi_comanda;
    int nr_produse;
    float *preturi_produse;
    static int counter_comenzi;

public:
    // constructor declaration -- handle id_comanda in the implementation
    Comanda(string nume_client = "None", int zi_comanda = 0, int nr_produse = 0, float *preturi_produse = nullptr);

    // copy constructor declaration
    Comanda(const Comanda &source);

    // operator overloading function declarations
    Comanda &operator=(const Comanda &source);
    float &operator[](int idx);

    /*
        post and pre incrementation/decrementation logic
        pre-incrementation
            first increments the value of the obj
            returns a reference to the modified object
            ! does not involve temp copies of the obj. the obj is modified in-place
        
        post-incrementation
            a copy of the unaltered value is made
            the object is modified
            the unmodified version is returned
    */
    Comanda &operator++();      // pre-increment
    Comanda operator++(int);    // post-increment
    Comanda &operator--();      // pre-decrement
    Comanda operator--(int);    // post-decrement

    // destructor
    ~Comanda(){
        delete [] preturi_produse;  // delete[] is nullptr safe, no need to check
    }

    // setters
    void setZiComanda(int zi_comanda_in){ zi_comanda = zi_comanda_in; }

    // getters
    int getZiComanda(){ return zi_comanda; }
    int getIdComanda(){ return id_comanda; }
    int getNrProduse(){ return nr_produse; }
    static int getCounterComenzi(){ return counter_comenzi; }
};

int Comanda::counter_comenzi = 0;

// constructor
// initialize pointer to nullptr ;; will be overwritten is the incoming value is different
Comanda::Comanda(string nume_client_in, int zi_comanda_in, int nr_produse_in, float *preturi_produse_in) : id_comanda{++counter_comenzi}, nume_client{nume_client_in}, zi_comanda{zi_comanda_in}, nr_produse {nr_produse_in}, preturi_produse{nullptr}
{
    cout << "Trying to create order " << id_comanda << endl;

    if(nr_produse > 0 && preturi_produse_in != nullptr){
        nr_produse = nr_produse_in;
        preturi_produse = new float[nr_produse_in];
        
        for(int i {0}; i < nr_produse_in; i++)
            preturi_produse[i] = preturi_produse_in[i];
    }

    cout << "Order " << id_comanda << " created" << endl;
}

// copy constructor w/ deep copy for pointer
Comanda::Comanda(const Comanda &source)
    // delegate constructor
    : Comanda {source.nume_client, source.zi_comanda, source.nr_produse} {
        // pointer require deep copies to work with the delegated constructor
        if (source.preturi_produse != nullptr && source.nr_produse > 0) {
            preturi_produse = new float[source.nr_produse];
            for (int i = 0; i < source.nr_produse; ++i) 
                preturi_produse[i] = source.preturi_produse[i];
    }

}

// overload input output
ostream &operator<<(ostream &os, const Comanda &comanda) {
    cout << endl << endl << "**********************" << endl;
    os << "id_comanda: " << comanda.id_comanda << endl;
    os << "nume_client: " << comanda.nume_client << endl;
    os << "zi_comanda: " << comanda.zi_comanda << endl;
    os << "nr_produse: " << comanda.nr_produse << endl;
    os << "preturi_produse: ";

    for (int i {0}; i < comanda.nr_produse; i++) {
        os << comanda.preturi_produse[i] << ", ";
    }

    cout << endl << "**********************" << endl << endl;
    return os;
}

istream &operator>>(istream &in, Comanda &comanda) {
    cout << "Please input the data for a new order: " << endl;

    cout << "nume_client: ";
    getline(in, comanda.nume_client);

    cout << "zi_comanda: ";
    in >> comanda.zi_comanda;

    cout << "nr_produse: ";
    in >> comanda.nr_produse;

    if (comanda.nr_produse > 0) {
        comanda.preturi_produse = new float[comanda.nr_produse];
        cout << "preturi_produse (space separated): ";
        for (int i = 0; i < comanda.nr_produse; ++i) {
            in >> comanda.preturi_produse[i];
        }
    }

    return in;
}

// overload []
float &Comanda::operator[](int idx){
    if (idx < 0 || idx > getCounterComenzi())
        throw ComandaException("Please input a valid index for operator[]");

    return preturi_produse[idx];
}

// overload = - creates deep copy
Comanda &Comanda::operator= (const Comanda &source){
    if(this == &source) return *this; // check for self-assignment

    delete [] this-> preturi_produse; // clean up existing memory 

    nume_client = source.nume_client;
    zi_comanda = source.zi_comanda;
    nr_produse = source.nr_produse;

    // deep copy the dynamic memory
    if (source.preturi_produse != nullptr && source.nr_produse > 0) {
        preturi_produse = new float[source.nr_produse];
        for (int i = 0; i < source.nr_produse; ++i) {
            preturi_produse[i] = source.preturi_produse[i];
        }
    } else {
        preturi_produse = nullptr; // handle null case
    }

    return *this;
}

// overload ++ --
Comanda &Comanda::operator++(){
    for(int i {0}; i < nr_produse; i++)
        preturi_produse[i] += 1.0;

    return *this;
}

Comanda Comanda::operator++(int){
    Comanda temp = *this;
    ++(*this);
    return temp;
}

Comanda &Comanda::operator--(){
    for(int i {0}; i < nr_produse; i++)
        preturi_produse[i] -= 1.0;

    return *this;
}

Comanda Comanda::operator--(int){
    Comanda temp = *this;
    --(*this);
    return temp;
}

static void outputResultsInFile(int nr_comenzi, Comanda *comenzi, int nr_produse){
    ofstream outFile("results.out", ios::app);

    if(!outFile)
        throw ComandaException("Invalid output file!");
	
    cout << endl;

    for(int i {0}; i < nr_comenzi; i++){
        if(comenzi[i].getNrProduse() > 0)
            outFile << comenzi[i].getIdComanda() << " ";
    }

    cout << endl;
		
    outFile.close();
}

// 
// calls constructor for some reason
// 
// clasa comenzi
class Comenzi{
private:
    vector<Comanda> comenzi;

public:
    void addComanda(const Comanda &comanda){
        comenzi.push_back(comanda);
    }

    void writeResultsToFile(const string &filename) {
        ofstream outFile(filename, ios::app);
        if (!outFile)
            throw ComandaException("Invalid output file!");

        // write orders that have at least one product
        for (const auto& comanda : comenzi) {
            if (comanda.nr_produse > 0) {
                outFile << "id_comanda: " << comanda.id_comanda << ", nume_client: " << comanda.nume_client << endl;
            }
        }
        outFile.close();
    }
};

int main(){
    /*
    // test constructor (different param signature), copy constructor
    Comanda c1;
    Comanda c2{c1};
    Comanda c3("Paul", 23);
    cout << "The order was placed on the day: " << c3.getZiComanda() << endl;

    // test overloaded input/output operators
    cout << c3 << endl;
    Comanda c4;
    cin >> c4;
    cout << c4 << endl;

    // overload =
    float preturi[] = {11.6, 342.6, 100};
    Comanda c5("Paul", 24, 3, preturi);
    Comanda c6 = c5;
    cout << c5 << c6;

    // overload []
    Comanda c7("Paul", 24, 3, preturi);
    cout << c7[1] << endl;

    // test errors
    Comanda err1;
    Comanda err2 = err1;
    Comanda err3 {err1};

    cout << err1[6] << endl;

    // output in text file from vector collection in another class
    Comanda test1("Paul", 24, 3, preturi);
    Comenzi comenzi;
    comenzi.addComanda(test1);
    comenzi.writeResultsToFile("results.out");
    */

    // output in text file without another class

    return 0;
}