#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>
using namespace std;

namespace Exemplu
{
	int suma(int x, int y)
	{
		x++;
		return x + y;
	}

	template <typename T>
	T add(T x, T y)
	{
		x++; 
		y++;
		return x + y;
	}
}

int suma(int x, int y)
{
	return x + y;
}

//FUNCTII TEMPLATE

template <typename T>
T add(T x, T y)
{
	return x + y;
}

template <class T1, class T2>
T1 add(T1 x, T2 y)
{
	return x + y;
}

template <class T, int n>
class CustomVector2
{
	T elemente[n];
};

//CALSE TEMPLATE
template <class T>
class CustomVector
{
	T* elemente;
	int dimensiune;
public:
	CustomVector(int dim)
	{
		if (dim > 0)
		{
			dimensiune = dim;
			elemente = new T[dimensiune];
		}
		else
		{
			dimensiune = 0;
			elemente = nullptr;
		}
	}

	CustomVector(const CustomVector& cv)
	{
		if (cv.elemente != nullptr && cv.dimensiune > 0)
		{
			this->dimensiune = cv.dimensiune;
			this->elemente = new T[this->dimensiune];
			for (int i = 0; i < this->dimensiune; i++)
			{
				this->elemente[i] = cv.elemente[i];
			}
		}
		else
		{
			this->dimensiune = 0;
			this->elemente = nullptr;
		}
	}

	CustomVector& operator=(const CustomVector&);

	~CustomVector()
	{
		if (elemente)
		{
			delete[] elemente;
			elemente = nullptr;
		}
	}

	T& operator[](int index)
	{
		if (index >= 0 && index < dimensiune)
		{
			return elemente[index];
		}
		else
		{
			throw exception("Invalid index!");
		}
	}

	void afisare()
	{
		if (dimensiune > 0 && elemente != nullptr)
		{
			for (int i = 0; i < dimensiune; i++)
			{
				cout << elemente[i] << " ";
			}
			cout << endl;
		}
	}
};

template <class T>
CustomVector<T>& CustomVector<T>::operator=(const CustomVector<T>& obiect)
{
	if (this != &obiect)
	{
		if (elemente)
		{
			delete[] elemente;
		}
		if (obiect.elemente != nullptr && obiect.dimensiune > 0)
		{
			dimensiune = obiect.dimensiune;
			elemente = new T[dimensiune];
			for (int i = 0; i < dimensiune; i++)
			{
				elemente[i] = obiect.elemente[i];
			}
		}
		else
		{
			dimensiune = 0;
			elemente = nullptr;
		}
	}
	return *this;
}

class Student
{
	string nume;
public:
	Student(){}
	Student(string nume) { this->nume = nume; }
	friend ostream& operator<<(ostream&, Student);
};

ostream& operator<<(ostream& out, Student s)
{
	out << "Nume: " << s.nume << endl;
	return out;
}

class Persoana
{
public:
	string nume;
	int varsta;
	float inaltime;

	Persoana(string n, int v, float i)
	{
		nume = n;
		varsta = v;
		inaltime = i;
	}

	bool operator<(Persoana p) const
	{
		return this->inaltime < p.inaltime;
	}
};

int main()
{
	int a = 3, b = 7;

	string x = "ceva";
	string y = " altceva";

	cout << add<string>(x, y) << endl;

	cout << suma(a, b) << endl;

	cout << add<int>(a, b) << endl;

	double c = 2.5;
	cout << add<float, int>(c, b) << endl;

	CustomVector<int> cv(5);
	cv[0] = 7;
	cv[1] = 70;
	cv[2] = 17;
	cv[3] = 23;
	cv[4] = 5;

	cv.afisare();
	CustomVector<Student> cv3(2);
	Student s1("Gigel");
	Student s2("Ionel");
	cv3[0] = s1;
	cv3[1] = s2;
	cv3.afisare();

	CustomVector2<int, 2> cv2;
	cout << Exemplu::suma(a, b) << endl;
	double d = 22.5, e = 7.75;
	cout << Exemplu::add<double>(d, e) << endl;

	//STL
	vector<int> v;
	v.push_back(6);
	v.push_back(7);
	v.push_back(17);
	v.push_back(278);
	v.push_back(34);
	v.push_back(16);
	v.push_back(56);

	cout << "" << endl;
	cout << "v: ";
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
	v.pop_back();

	cout << "v: ";
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	list<double> l;
	l.push_back(2.4);
	l.push_front(1.3);
	l.insert(++l.begin(), 1.5);

	cout << "l: ";
	for (list<double>::iterator i = l.begin(); i != l.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;

	map<string, long> m;
	m.insert(pair<string, long>("Ion", 234567435));
	m.insert(pair<string, long>("Ionut", 214508935));

	cout << "nume: ";
	string nume; 
	cin >> nume;

	map<string, long>::iterator i = m.find(nume);
	if (i != m.end())
	{
		cout << "Persoana " << i->first << " are nr. de telefon " << i->second << endl;
	}
	else
	{
		cout << "Nu s-a gasit persoana" << endl;
	}

	set<Persoana> s;
	Persoana p1("Marian", 20, 175);
	Persoana p2("Maria", 18, 158);
	Persoana p3("Andrei", 24, 188);

	s.insert(p1);
	s.insert(p2);
	s.insert(p3);

	for (set<Persoana>::iterator i = s.begin(); i != s.end(); i++)
	{
		cout << i->nume << " ";
	}
	cout << endl;

	return 0;
}