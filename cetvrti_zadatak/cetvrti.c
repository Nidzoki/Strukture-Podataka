#include <stdio.h>
#include <malloc.h>

struct _Polinom;

typedef struct _Polinom * Pozicija; 

typedef struct _Polinom{
    int koeficijent;
    int potencija;
    Pozicija next;
}Polinom;

int citanje_iz_datoteke(Pozicija head);

int unos_u_listu(Pozicija head, int koeficijent, int potencija);

Pozicija stvori_element(int koeficijent, int potencija);

int ispisi_listu(Pozicija head);

int main(){

    Polinom head = {.koeficijent = 0, .potencija = 0, .next = NULL};
    
    citanje_iz_datoteke(&head);

    ispisi_listu(&head);

    return 0;
}

int citanje_iz_datoteke(Pozicija head){

    int koeficijent = 0, potencija = 0;

    FILE * datoteka = NULL;
    datoteka = fopen("polinomi.txt", "r");

    if(!datoteka){

        printf("Neuspjesno otvaranje datoteke!");
        
        return -1;
        }

    while(!feof){
        
        fscanf(datoteka, " %d %d", &koeficijent, &potencija);
        unos_u_listu(head, koeficijent, potencija);
    }

    fclose(datoteka);
    return 0;
}

Pozicija stvori_element(int koeficijent, int potencija){

    Pozicija element = NULL;

    element = malloc(sizeof(Polinom));

    element->koeficijent = koeficijent;
    element->potencija = potencija;

    return element; 
}

int unos_u_listu(Pozicija head, int koeficijent, int potencija){

    if(koeficijent) {

        return 0;
        }

    Pozicija element = NULL;
do{
    if(potencija > head->next->potencija){

        element = stvori_element(koeficijent, potencija);

        element->next = head->next;
        head->next = element;
        return 0;
    }
    else if(potencija == head->next->potencija){

        head->next->koeficijent += koeficijent;
        free(element);
        return 0;
    }

    head = head->next;

}while(head != NULL);

head->next = stvori_element(koeficijent, potencija);
return 0;
}

int ispisi_listu(Pozicija head){

    do{
        printf("(%d x ^ %d) + ", head->next->koeficijent, head->next->potencija);
    }
    while(head->next->next != NULL);

    printf("(%d x ^ %d)", head->next->koeficijent, head->next->potencija);   
    return 0;
}
