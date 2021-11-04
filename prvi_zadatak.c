
/* Prvi zadatak:

1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100

NAPOMENA: Potrebno je skinuti i datoteku studenti.txt čiji naziv morate sami upisati kada vas to program zatraži. Datoteka se treba nalaziti u istom direktoriju kao i program.

*/

// Biblioteke i konstante

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IME_MAX 128
#define STRING_MAX 1024
#define MAX_BOD 40

// Deklaracija strukture Student

typedef struct Student
{
    char ime[IME_MAX];
    char prezime[IME_MAX];
    double bod;
}_student;

// Prototipi funkcija

int brojanje_redaka(char *);    // Funkcija za brojanje redaka u tekstualnoj datoteci

_student * alokacija(char *, int);  //Funkcija za dinamičku alokaciju memorije za niz struktura Student

int ispis(int, _student *);     // Funkcija za ispis niza struktura Student

// Glavna funkcija

int main(){

    char ime_datoteke[IME_MAX];
    int broj_studenata = 0;
    _student * lista = NULL;

    printf("Upisite ime tekstualne datoteke sa nastavkom .txt :\n");

    scanf(" %s", ime_datoteke);

    broj_studenata = brojanje_redaka(ime_datoteke);

    lista = alokacija(ime_datoteke, broj_studenata);

    ispis(broj_studenata, lista);

    return 0;
}

// Definicija ostalih funkcija

int brojanje_redaka(char * dat){
    FILE * datoteka = NULL;
    int i = 0;
    char kolektor[STRING_MAX] = {0}; 
    

    datoteka = fopen(dat, "r");

    if(datoteka == NULL){
        printf("Neuspjelo otvaranje tekstualne datoteke!");
        return -1;
    }
    
    while(!feof(datoteka)){
        
        fgets(kolektor, STRING_MAX, datoteka);
        i++;
    }

    return i-1;
}

_student * alokacija(char * dat, int br_studenata){

    int i = 0;
    FILE * datoteka = NULL;
    _student * lista = NULL;

    lista = (_student *)malloc((sizeof(_student)) * ( br_studenata));

    datoteka = fopen(dat, "r");

    if(!datoteka){
        printf("Greska pri alokaciji memorije!");
        free(lista);
        return 0;
    }
    else{

        while (!feof(datoteka)){
            fscanf(datoteka, " %s %s %lf", &lista[i].ime, &lista[i].prezime, &lista[i].bod);
            i++;
        }
        fclose(datoteka);

    return lista;
    }
}

int ispis(int br_studenata, _student * lista){
    int i = 0;

    for(i = 0; i < br_studenata; i++){    
        printf("\n Ime : %s \n Prezime : %s \n Apsolutni broj bodova : %.2lf \n Relativni broj bodova : %.2lf \n \n", lista[i].ime, lista[i].prezime, lista[i].bod, (lista[i].bod/MAX_BOD * 100));

    }

}
