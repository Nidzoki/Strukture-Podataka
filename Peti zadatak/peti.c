#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE 1024

struct _znak;
typedef struct _znak * pozicija;

typedef struct _znak {

    double br;

    pozicija next;
}znak;

pozicija stvori_element(double br);

int dodaj_iza(pozicija pos, pozicija novi);
int stavi_na_stog(pozicija head, double br);
int izbrisi_iza(pozicija pos);
int skini_sa_stoga(double* rez_final, pozicija head);
int izracunaj(pozicija head, char operator);
int ucitaj_iz_datoteke(double* rez_final, char* ime_datoteke);
int brisi_sve(pozicija head);


int main(){

    char ime_datoteke[MAX_LINE] = {0};
    double rezultat;

    printf("Unesite ime_datoteke:\n ");
    scanf(" %s", ime_datoteke);
    
    ucitaj_iz_datoteke(&rezultat, ime_datoteke);
    printf("Rezultat = %f \n", rezultat);

	return 0;
}


pozicija stvori_element(double br){

    pozicija novi = NULL;

    novi = (pozicija)malloc(sizeof(znak));
    if(novi == NULL){
        printf("Nemoguce alocirati memoriju!\n");
        return NULL;
    }

    novi->br=br;
    novi->next=NULL;

    return novi;
}


int dodaj_iza(pozicija pos, pozicija novi){

    novi->next = pos->next;
    pos->next = novi;

    return 0;
}


int stavi_na_stog(pozicija head, double br){

    pozicija novi = NULL;

    novi = stvori_element(br);

    if(novi == NULL){

        return -1;
    }
    dodaj_iza(head, novi);

    return 0;
}
 
int izbrisi_iza(pozicija pos){

    pozicija element = pos->next;

    if(element == NULL){
        return 0;
    }
    pos->next = element->next;

    free(element);

    return 0;
}


int skini_sa_stoga(double * rez_final, pozicija head){

    pozicija prvi = head->next;

    if(prvi == NULL){

        printf("Postfiks nije valjan!");
        return -1;
    }

    *rez_final = prvi->br;

    izbrisi_iza(head);

    return 0;
}

int izracunaj(pozicija head, char operator){

    double operand1 = 0;
    double operand2 = 0;
    double rezultat = 0;

    skini_sa_stoga(&operand2, head);

    skini_sa_stoga(&operand1, head);


    switch (operator)
    {
    case '+':

        rezultat = operand1 + operand2;         break;
    case '-':
        rezultat = operand1 - operand2;         break;
    case '*':
        rezultat = operand1 * operand2;         break;
    case '/':
        if(operand2 == 0){
            perror("Nemoguce dijeliti nulom!\n");
            return -1;
        }
    rezultat = operand1 / operand2;             break;
    
    default:                                    break;

    return stavi_na_stog(head, rezultat);
    }
}



int ucitaj_iz_datoteke(double* rez_final, char* ime_datoteke){

   FILE * datoteka = NULL;
   int duljina = 0;
   int broj_bajtova = 0;

   char * string = NULL;
   char * str = NULL;
   char operacija = 0;

   double br = 0;
   
   znak head = {.next = NULL, .br =0};

    datoteka = fopen(ime_datoteke, "rb");
    if(datoteka == NULL){
        printf("Nemoguce otvoriti datoteku!\n");
        return -1;
    }

    fseek(datoteka, 0, SEEK_END); 

    duljina = ftell(datoteka);

    string = (char *)calloc(duljina +1, sizeof(char));

    if(string == NULL){

        printf("Nemoguce alocirati memoriju!");
        return -1;
    }

    rewind(datoteka);

    fread(string, sizeof(char), duljina, datoteka);

    printf(" %s\n", string);

    fclose(datoteka);

    str = string;

    while(strlen(str)>0){

        ;

        if(sscanf(str, " %lf %n", &br, &broj_bajtova)){

            ;
            if(stavi_na_stog(&head, br) != 0){

                free(string);

                brisi_sve(&head);

                return -1;
            }
            str = str + broj_bajtova;
        }

        else {
            sscanf(str, " %c %n", &operacija, &broj_bajtova);
            
            if(izracunaj(&head, operacija) != 0){

                free(string);

                brisi_sve(&head);

                return -1;
            }
            str = str + broj_bajtova;
        }

    }

    free(string);

    ;

    if(skini_sa_stoga(rez_final, &head) != 0)
    {
        brisi_sve(&head);

        return -1;
    }

    if(head.next){
        printf("Postfiks nije valjan!");

        brisi_sve(&head);

        return -1;
    }

    return 0;
}


int brisi_sve(pozicija head){
    
    while(head->next != NULL){

        izbrisi_iza(head);
    }
}
