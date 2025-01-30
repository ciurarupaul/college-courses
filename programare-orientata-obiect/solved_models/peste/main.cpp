/*
Se considera o aplicatie pentru gestionarea activitatii unui magazin care vinde peste si produse din peste. Se vor urmari atribute specifice, precum: tipuri produse (peste proaspat, congelat, produse din peste), specie, data expirarii, pret, etc. Datele membre sunt private si sunt puse la dispozitie metode de acces. Clasa contine cel putin patru campuri, dintre care unul este alocat dinamic, constructori, metodele specifice claselor cu membri alocati dinamic si operatorul de afisare. Folositi un membru static sau const.
    - Se va defini operatorul *= care permite acordarea unei reduceri produselor care expira in ziua urmatoare
    - Definiti operatorul == care compara doua produse si returneaza true daca toate valorile atributelor sunt egale intre ele.
    - Definiti o clasa pentru a gestiona produsele existente in stoc. Operatorul += permite adaugarea unui produs nou (daca exista, se actualizeaza stocul), iar operatorul functie() va elimina toate produsele care nu sunt in stoc
    - Explicati conceptele de early binding si late biding
    - Propuneti un container STL care permite regasirea tuturor produselor unei specii de peste
*/

using namespace std;
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <unordered_map>    // pentru container stl

enum Tip { proaspat, congelat, produseDinProduct};

string tipToString(Tip tip) {
    switch (tip) {
        case Tip::proaspat:
            return "proaspat";
        case Tip::congelat:
            return "congelat";
        case Tip::produseDinProduct:
            return "produseDinProduct";
        default:
            return "Unknown";
    }
} 

class Product{
    friend ostream &operator<<(ostream &os, const Product &Product);

private:
    Tip tip;
    string specie;
    char* data_expirare;
    float pret;
    unsigned int stoc;
    static int numar_produse;

public:
    // constructor
    Product(Tip tip = Tip::proaspat, string specie = "", char *data_expirare = nullptr, float pret = 0, int stoc = 0);

    // copy constructor
    Product(const Product &source);

    // destructor
    ~Product(){
        if(data_expirare != nullptr){
            delete [] data_expirare;
            data_expirare = nullptr;
        }
    }

    // overload operators
    Product &operator=(const Product &source);
    bool operator==(const Product &source) const;

    
    // gettere
    Tip getTip() {return tip;}
    string getSpecie() const {return specie;}
    const char* getDataExpirare() {return data_expirare;}
    float getPret() const {return pret;}
    static int getNumarPesti() {return numar_produse;}

};

int Product::numar_produse = 0;

// constructor
Product::Product(Tip tip, string specie, char* data_expirare, float pret, int stoc) 
    : tip{tip}, specie{specie}, pret{pret}, stoc{stoc}
    {
        if(data_expirare){
            this->data_expirare = new char[strlen(data_expirare) + 1];
            strcpy(this->data_expirare, data_expirare);
        }else{
            // must use this for some reason
            this->data_expirare = nullptr;
        }

        ++numar_produse;
}

// copy constructor
Product::Product(const Product &source)
    : Product {source.tip, source.specie, source.data_expirare, source.pret, source.stoc}{}

// overload =
Product &Product::operator= (const Product &source){
    if(this == &source) return *this;

    delete [] this->data_expirare;

    tip = source.tip;
    specie = source.specie;
    pret = source.pret;
    stoc = source.stoc;

   if(data_expirare){
        this->data_expirare = new char[strlen(data_expirare) + 1];
        strcpy(this->data_expirare, data_expirare);
    }else{
        // must use this for some reason
        this->data_expirare = nullptr;
    }

    return *this;

}

// overload << >>
ostream &operator<<(ostream &os, const Product &Product) {
    os << endl;
    os << "tip: " << tipToString(Product.tip) << endl;
    os << "specie: " << Product.specie << endl;

    // only print data_expirare if it is not nullptr
    if (Product.data_expirare) {
        os << "data_expirare: " << Product.data_expirare << endl;
    } else {
        os << "data_expirare: N/A" << endl;
    }

    os << "pret: " << Product.pret << endl;
    os << "stoc: " << Product.stoc << endl;
    os << endl;

    return os;
}

// 1. n am chef sa manipulez stringuri ca data

// 2.
// overload == (comparare pesti)
bool Product::operator==(const Product &source) const{
    return (tip == source.tip &&
            specie == source.specie &&
            pret == source.pret &&
            stoc == source.stoc &&
            strcmp(data_expirare, source.data_expirare) == 0);
}

// 3.
// clasa gestionare produse
class Stoc{
private:
    vector<Product> products;

public:
    // display all products
    void display() const {
        for (const auto& product : products) {
            cout << product << endl;
        }
    }
};

// 4.
// late binding vs early biding
/*
EARLY BINDING
    - occurs when the function to be called is determined at COMPILE TIME
    - static polymorphism, NOT marked as virtual
LATE BINDING
    - occurs when the function to be called is determined at RUN TIME, based on the object's acutal type
    - requires functions to be declared as virtual
*/

// 5. 
// container pentru regasirea tuturor produselor unei specii de peste
unordered_map<string, vector<Product>> productMap;

void addProduct(const Product &product) {
    productMap[product.getSpecie()].push_back(product);
}

vector<Product> getProductsBySpecie(const string &specie) {
    if (productMap.find(specie) != productMap.end()) {
        return productMap[specie];
    }
    return {};
}


int main(){
    /*
    // test basics
    Product p1;
    Product p2(Tip::proaspat, "Somon", nullptr);
    Product p3(Tip::proaspat, "Somon", "20 martie", 99.99);
    Product p4 = p3;
    Product p5 {p1};
    Product p6;
    p6 = p1;

    // cout << p1 << p2 << p3 << p4 << p5 << p6;
    bool test = p3 == p4;
    cout << boolalpha << test << endl;
    */

    // test container 
    Product p1(Tip::proaspat, "Salmon", "2025-01-28", 15.5, 10);
    Product p2(Tip::congelat, "Salmon", "2025-01-28", 12.3, 5);
    Product p3(Tip::produseDinProduct, "Tuna", "2025-02-01", 8.9, 20);
    Product p4(Tip::proaspat, "Salmon", "2025-01-28", 13.0, 8); 
    Product p5(Tip::congelat, "Tuna", "2025-02-01", 10.2, 15); 

    addProduct(p1);
    addProduct(p2);
    addProduct(p3);
    addProduct(p4);
    addProduct(p5);

    // test salmon
    cout << "Products of specie 'Salmon':" << endl;
    vector<Product> salmonProducts = getProductsBySpecie("Salmon");
    for (const auto &product : salmonProducts) {
        cout << "Product: " << product.getSpecie() << " - Price: " << product.getPret() << endl;
    }

    // test tuna
    cout << "\nProducts of specie 'Tuna':" << endl;
    vector<Product> tunaProducts = getProductsBySpecie("Tuna");
    for (const auto &product : tunaProducts) {
        cout << "Product: " << product.getSpecie() << " - Price: " << product.getPret() << endl;
    }

    // test none
    vector<Product> mackerelProducts = getProductsBySpecie("Mackerel");
    if (mackerelProducts.empty()) {
        cout << "No products found for 'Mackerel'" << endl;
    }


    return 0;
}