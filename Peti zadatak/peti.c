#include <stdio.h>
#include <malloc.h>
#include <math.h>

struct _stog;

typedef struct _stog * Pozicija;

typedef struct _stog{
    int broj;
    Pozicija next;
}stog;


int citaj_datoteku(Pozicija head);

int stavi_na_pocetak(Pozicija head, int broj);

int skini_sa_pocetka(Pozicija head);

Pozicija stvori_element(int broj);


int main(){

    stog s = {.broj = 0, .next = NULL};

    Pozicija head = &s;

    citaj_datoteku(head);

    if(head->next->next != NULL){
        printf("Postfix neispravan");
        return -1;
    }

    printf("Rezultat je %d.", head->next->broj);

    return 0;
}


int citaj_datoteku(Pozicija head){
    
    FILE * datoteka = NULL;
    char temp;
    datoteka = fopen("datoteka.txt", "r");
    
    if(!datoteka){

        printf("\nPogreska pri otvaranju datoteke! \n");
        return -1;
    }

    while(!feof){
        int i = -1;
        int br = 0;
        do{ temp = fgetc(datoteka);
            if(temp == '+'){
                int a, b;
                a = skini_sa_pocetka(head);
                b = skini_sa_pocetka(head);

                stavi_na_pocetak(head, a + b);
            }
            else if(temp == '-'){
                int a, b;
                a = skini_sa_pocetka(head);
                b = skini_sa_pocetka(head);

                stavi_na_pocetak(head, a - b);
            }
            else if(temp == '*'){
                int a, b;
                a = skini_sa_pocetka(head);
                b = skini_sa_pocetka(head);

                stavi_na_pocetak(head, a * b);
            }
            else if(temp == '/'){
                int a, b;
                a = skini_sa_pocetka(head);
                b = skini_sa_pocetka(head);

                if(b == 0){
                    printf("Postfix neispravan! Nemoguće dijeliti nulom!");
                    return -1;
                }

                stavi_na_pocetak(head, a - b);
                
            }
            i++;
            
            if(temp >= '0' && temp <= '9'){
                br += ((int)temp - 48) * pow(10, i);
            }

            else{printf("Postfix neispravan!");
                return -1;
            }

        }
        while(temp != ' ');
        
        if(i != 0){
            stavi_na_pocetak(head, br);
        }
    }
}

int skini_sa_pocetka(Pozicija head){
    int a;
    Pozicija element = head->next;
    head->next = element->next;
    a = element->broj;
    free(element);
    return a;
}
