using namespace std;
#include <iostream>
#include <vector>

/*
**********************************
        *** general ***
**********************************

- local variables overwrite global ones
- signed - can represent both positive and negative numbers
- unsigned - only positives
- dont use #define to declare constants (legacy c++)
- size_t is the correct type for looping indexes (for (size_t i{0};;))

**********************************
    *** arrays and vectors***
**********************************

- arrays are NOT vectors. vectors were added in modern cpp
- not initializing an array fully (not providing a value for each element) will result in the other elements being assigned 0
- vectors are part of the C++ StandardTemplateLibrary
- vectors are objects with methods (such as sort)
- vectors will automatically allocate the required space, as they are NOT fixed in size, like arrays

*/

int test_scores [5] {100, 87, 94, 60, 89}; // declare array, assign values

int high_score_per_level [10] { 3, 5 }; // init elements with 0 (besides first two)

const unsigned long days_in_year { 365 };
double high_temperatures [days_in_year] {0}; // init all elements with 0

int another_array [] {1, 2, 3, 4, 5}; // size automatically calculated by compiler

// multi-dimensional arrays

int movie_rating [3][4]{
    {0, 4, 3, 5},
    {2, 3, 3, 5},
    {1, 4, 4, 5}
};

// vectors

vector <char> vowels1; // automatically sets the value to 0
vector <char> vowels2 (5); // automatically sets the value to 0 as well
vector <double> high_temps (365, 80.0); // 365 elements initialized with 80.0

// accessing elements in vectors
vector <int> test_scores {100, 95, 99, 97, 88};

// test_scores[1] // doesnt have jackshit
// test_scores.at(1) // has out of bounds checking

// test_scores.push_back(80); // adds another element at the back of the vector

// multi-dimensional vectors
vector <vector <int>> movie_ratings{
    {0, 4, 3, 5},
    {2, 3, 3, 5},
    {1, 4, 4, 5}
};

// vector functions
/*
    - .at(idx) -> gets the element from the specified index and has out-of-bounds checking
    - .push_back(value) -> adds 'value' at the end of the vector, allocation memory dynamically, during run-time !!! 
    - .size() -> returns the size of the vector
*/

/*

**********************************
*** expressions and statements ***
**********************************

static_cast<double>(value) -> use for type conversions (c++ style)
(double)value (c style)

std::boolalpha -> will display true/false instead of 0/1 for booleans
std::noboolalpha -> back to 0/1

12.0 IS THE SAME AS 11.9999999999999 to the computer because these are stored as aproximations

**********************************
    *** selection, looping ***
**********************************

- switch statement

    switch (){
        case
        case

        default: 
    }

- range based for loop (C++11)

int scores [] {100, 90, 97};

for (auto score : scores)
    cout << score << endl;

continue -> go directly at the beginning of the loop for the next iteration
break -> loop is immediately terminated

for(;;) -> infinite loop
while (true) -> infinite loop

**********************************
  *** strings and characters ***
**********************************

- cctype library
    isalpha, isalnum, isdigit, islower, isprint, ispunct, isupper, isspace
    tolower(c), toupper(c)

- cstring library
    all the functions rely on the null termination at the end of the string
    strcpy, strcat, strcmp

- c style strings
    sequence of characters, implemented as an array of characters
    terminated by a null character
    called zero or null terminated strings ('\0')

    char my_name [8] {"Frank"}; -> Frank\0\0\0

    always initialize a string, since there will be no null characters

- c++ style strings
    dynamic size
    there is already a function
    safer, provide auto out-of-bounds cheks
    always initialized, dont hold garbage
    on these you can use the assignement operator! string = "something";

    functions:
        - .find() -> will return the index of the start position
            returns string::npos if nothing is found
        - .erase()
        - .clear()
        - .length()

**********************************
        *** functions ***
**********************************

double calc_cost (double base_cost, double tax_rate = 0.06); -> provide default value

**********************************
        *** pointers ***
**********************************

definition: int *pointer;
how to initialize: var_type *pointer {nullptr}; -> else it will hold garbage
!! Always initialize pointers!!! nullptr C++11 !
& -> address operator -> holds the address of the variable (the location in memory in hexadecimals)

no matter what type they point to, pointers are a simple 4bytes variable that hold an address
losing a pointer will result in a MEMORY LEAK
arrays are just pointers

- allocating memory at run time
    int_ptr = new int;  // allocate an integer on the heap
    delete int_ptr;     // frees the allocated storage
    
    // for arrays
    array_ptr = new int[size];
    delete [] array_ptr;

- arrays are pointers
    array[idx] is the same as pointer[idx]
    *(pointer + idx) is the same as *(array + idx)

- const pointers
    int high_score {100};
    int low_score {65};

    // type 1
    const int *score_ptr {&high_score};
    *score_ptr = 86;            // err
    score_ptr = &low_score;     // ok

    // type 2
    int *const score_ptr {&high_score};
    *score_ptr = 86;            // ok
    score_ptr = &low_score;     // err

**********************************
*** object oriented programming ***
**********************************

- declarations
    class Class_Name{
        // attributes and methods
    };

    ClassName instance;

    ClassName *pointer = new Class_Name();
    delete pointer;

in a class, everything is private by default

there is a default 'given by the compiler' constructor, as long as no other constructors are declared. as soon as you declare a specific constructor, you need to provide the default one as well

you can overload constructors as much as you like, but they need an UNIQUE signature (param list)

- initialize constructors like this (w/ initialization lists):

Player::Player(std::string name_val, int health_val, int xp_val)
    : name{name_val}, health{health_val}, xp{xp_val} {
}

// delegating constructors
// call the most complex constructor on all the other constructors, so there is no duplicate code ; Player:: for player class scope
// both their bodies will be executed - keep in mind!
Player::Player()
    : Player {"None", 0, 0}{
}

// ********************
// best way to declare and initialize constructors
// ********************
// 
// default params for constructors -- only one constructor

// -- in class:
public:
    Player(std::string name_val = 'None', int health_val = 0, int xp_val = 0);
}; -- end class declaration

Player(str::string name_val, int health_val, int xp_val)
    : name{name_val}, health{health_val}, xp{xp_val}{
}

// copy constructor

    Player::Player(const Player &source)
        :   name{source.name},
            health {source.health},
            xp {source.xp}{
    }

- shallow copy - pointing to the same memory area as the pointer that was copied instead of copying the data the og pointer was pointing at in another location and pointing there with the copy pointer
!issue - if the original memory is freed, the copy pointer will point to invalid data
    
- deep copy - copies the data that is being pointed at, not the memory address of the data

// the difference between the two is a *


// shallow copy 
// allocate mamory for an int pointer (data) and initialize it with the value from d
Shallow::Shallow(int d){
    data = new int;
    *data = d;
}

// now the pointer data of the current object points to the same memory location as source.data
Shallow::Shallow(const Shallow &source)
    :data(source.data){
}

// deep copy
// same as the shallow one
Deep::Deep(int d) {
    data = new int;
    *data = d;
}

// use the regular constructor to create a new Deep object with the value stored in source.data
Deep::Deep(const Deep &source)
    : Deep {*source.data} {
}

- this contains the address of the current object
    - can only be used in the class scope

void Account::set_balance(double balance){
    this->balance = balance;
}
// ----- instead of ----- 
void Account::set_balance(double bal){
    balance = bal;
}

// static class members - available for the whole class, not the instances of the class

// friends of a class - another class that has access to the private data of the friend class

**********************************
*** operator overloading ***
**********************************

- cannot overload :: :? .* . sizeof

**********************************
        *** exceptions ***
**********************************

destructors are designed to not throw exceptions

**********************************
            *** fml ***
**********************************

virtual destructors - first delete derived than delete base instance

*/