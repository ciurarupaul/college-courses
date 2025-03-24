/*
stiva si coada sunt particularitati ale listelor simplu inlantuite
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>

typedef struct Nod Nod;
typedef struct Restaurant Restaurant;

struct Restaurant{
    char* nume;
    int capacitate;
    char* specific;
};

struct Nod {
    Restaurant info;
    Nod* next;
};

Restaurant initRestaurant(const char* nume, int capacitate, const char* specific){
    Restaurant r;

    if(nume != NULL && specific != NULL){
        r.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
        strcpy(r.nume, nume);
        r.capacitate = capacitate;
        r.specific = (char*)malloc(sizeof(char) * strlen(specific) + 1);
        strcpy(r.specific, specific);
    }

    return r;
}

Restaurant pop(Nod** varf){
    // daca stiva e goala, returnez un restaurant gol
    if(*varf == NULL){
        return initRestaurant(NULL, 0, NULL);
    }

    // daca nu, extrag informatia utila din varf
    Restaurant r;
    r = (*varf)->info;  // shallow copy util
    Nod* temp = *varf;
    *varf  = (*varf)->next;

    free(temp);

    return r;
}

// pentru stiva
void push(Nod** varf, Restaurant r){
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = r;
    nou->next = *varf;
    *varf = nou;
}

void displayRestaurant(Restaurant r){
    printf("Nume: %s, Capacitate: %d, Specific: %s\n", r.nume, r.capacitate, r.specific);
}

// pentru coada
// coada reprezinta adresa primului nod din structura coada
void put(Nod** coada, Restaurant r){
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = r;
    nou->next = NULL;

    if(*coada == NULL){
        *coada = nou;
    }else{
        Nod* copie = *coada;
        while(copie->next != NULL){
            copie = copie->next;
        }
        // stiu sigur ca sunt pe ultimul nod
        copie->next = nou;
    }
}

int main (){
    Nod* stiva = NULL;
    
    Restaurant r1 = initRestaurant("Mitza Biciclista", 54, "romanesc");
    Restaurant r2 = initRestaurant("Socului", 13, "shaormerie");
    Restaurant r3 = initRestaurant("MC Romana", 54, "fast food");

    push(&stiva, r1);
    push(&stiva, r2);
    push(&stiva, r3);
    
    printf("\ntraversare stiva\n");
    Restaurant r4;
    while(stiva != NULL)
    {
        r4 = pop(&stiva);
        displayRestaurant(r4);
        
        free(r4.nume);
        free(r4.specific);
    }

    Nod* coada = NULL;

    put(&coada, initRestaurant("Mitza Biciclista", 54, "romanesc"));
    put(&coada, initRestaurant("Socului", 13, "shaormerie"));
    put(&coada, initRestaurant("MC Romana", 54, "fast food"));

    printf("\ntraversare coada\n");
    while(stiva != NULL)
    {
        // functia pop e si functia get in cazul de fata
        r4 = pop(&coada);
        displayRestaurant(r4);

        free(r4.nume);
        free(r4.specific);
    }

    displayRestaurant(r1);


    return 0;
}