#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define MAX_LINE 1024

struct _element;

typedef struct _element* cvor;

typedef struct _element{

    int broj_stanovnika;

    char grad[MAX_LINE];

    cvor lijevo;
    cvor desno;

}element;
 

struct element_liste;

typedef struct element_liste* pozicija;

typedef struct element_liste{

    char drzava[MAX_LINE];

    cvor root;
    pozicija next;

}el;

cvor citaj_gradove(char * ime_datoteke);
cvor sortirani_unos(char * ime, int broj_stanovnika, cvor trenutni);

pozicija pronadi_drzavu(char * drzava, pozicija head);

int citaj_datoteku(char *ime_datoteke, pozicija head);
int ispisi_gradove(int broj, cvor trenutni);
int sortiraj(pozicija novi, pozicija head);
int dodaj_iza(pozicija temp, pozicija novi);
int ispisi_listu(pozicija head);
int ispisi_inorder(cvor trenutni);
int pronadi_veci(char * drzava, int broj, pozicija head);
int pronadi_najveci(cvor trenutni);




int main(){

    el head = { .drzava = 0 ,  .root = NULL, .next = NULL };

    char drzava[MAX_LINE] = { 0 };

    int broj = 0;

    citaj_datoteku("drzave.txt", &head);

    ispisi_listu(&head);

    printf("\n Upisite ime drzave: ");

    scanf(" %s", drzava);

    printf(" Unesite broj: ");

    scanf(" %d", &broj);

    pronadi_veci(drzava, broj, &head);

    return 0;
}



int citaj_datoteku(char * ime_datoteke, pozicija head){

    char string[MAX_LINE] = { 0 };
    char datoteka_grada[MAX_LINE] = { 0 };

    FILE * datoteka;

    datoteka = fopen(ime_datoteke, "r");

    pozicija temp = NULL;

    if(datoteka == NULL){

        printf("Greska pri ucitavanju datoteke!\n");
		return -1;
    }

    while(!feof(datoteka)){

        pozicija temp = NULL;

        temp = (el*)malloc(sizeof(el));
        temp->next = NULL;

        fgets(string, MAX_LINE, datoteka);

        if(sscanf(string, " %s %s",  temp->drzava, datoteka_grada) == 2){
            temp->root = NULL;
            temp->root = citaj_gradove(datoteka_grada);
            
            sortiraj(temp, head);
        }
    }

    fclose(datoteka);

    return 0;
}

cvor citaj_gradove(char * ime_datoteke){

    int broj_stanovnika = 0;

    char string[MAX_LINE] = { 0 };
    char ime[MAX_LINE] = { 0 };

    cvor root = NULL;

    FILE * datoteka = NULL;

    datoteka = fopen(ime_datoteke, "r");

    

    if(datoteka == NULL){

        perror("Greska pri otvaranju datoteke!\n");

		return NULL;
    }

    while(!feof(datoteka)){  

        fgets(string, MAX_LINE, datoteka);

        if(sscanf(string, " %s %d", ime, &broj_stanovnika) == 2){

            root = sortirani_unos(ime, broj_stanovnika, root);
        }
    }
    fclose(datoteka);

    return root; 
}

int dodaj_iza(pozicija temp, pozicija novi){

    novi->next = temp->next;
    temp->next = novi;

    return 0;
}

int sortiraj(pozicija novi, pozicija head){

    
    
    while (head->next != NULL && strcmp(head->next->drzava, novi->drzava) < 0){

        head = head->next;
    }

    if(head->next == NULL || strcmp(head->next->drzava, novi->drzava)){

        dodaj_iza(head, novi); 
    }
    else if(strcmp(head->next->drzava, novi->drzava) == 0){

        printf("Drzava je vec unesena!");

        return -1;
    }

    return 0;
}



cvor sortirani_unos(char * ime, int broj_stanovnika, cvor trenutni){

    if(trenutni == NULL){

        trenutni = (element*)malloc(sizeof(element));
        strcpy(trenutni->grad, ime);

        trenutni->broj_stanovnika = broj_stanovnika;

        trenutni->lijevo = NULL;
        trenutni->desno = NULL; 
    }
    else if(broj_stanovnika < trenutni->broj_stanovnika){

        trenutni->lijevo = sortirani_unos(ime, broj_stanovnika, trenutni->lijevo);
    }
    else if(broj_stanovnika > trenutni->broj_stanovnika){

        trenutni->desno = sortirani_unos(ime, broj_stanovnika, trenutni->desno);
    }
    else if(broj_stanovnika == trenutni->broj_stanovnika){

        if(strcmp(ime, trenutni->grad) < 0){

            trenutni->lijevo = sortirani_unos(ime, broj_stanovnika, trenutni->lijevo);
        }
        else if(strcmp(ime, trenutni->grad) > 0){

            trenutni->desno = sortirani_unos(ime, broj_stanovnika, trenutni->desno);
        }
        else{
            return trenutni;
        }   
    }
    else{

        free(trenutni);
    }
    return trenutni;
}

int ispisi_listu(pozicija head){

    head = head->next;

    while(head != NULL){
        
        printf(" %s\n", head->drzava);
        ispisi_inorder(head->root);

        head = head->next;

        printf("\n");
    }

    return 0;

}

int ispisi_inorder(cvor trenutni){

    if(trenutni == NULL){
        return 0;
    }

    ispisi_inorder(trenutni->lijevo);

    printf(" %s -  %d \n", trenutni->grad, trenutni->broj_stanovnika);

    ispisi_inorder(trenutni->desno);

    return 0;
}

pozicija pronadi_drzavu(char * drzava, pozicija head){

    while(head->next != NULL && strcmp(head->next->drzava, drzava)){

        head = head->next;
    }

    return head->next;
}

int pronadi_veci(char* drzava, int broj, pozicija head){

    pozicija drz = pronadi_drzavu(drzava, head);

    int najveci = 0;

    if(drz == NULL){

        printf("Drzava nije unesena!\n", drzava);

        return -1;
    }

    najveci = pronadi_najveci(drz->root);

    if (broj > najveci){

        printf("U %s nema vecih gradova!\n", drzava);

        return -2;
    }
    
    printf("\nGradovi veci od %d su:\n", drz->drzava, broj);

    ispisi_gradove(broj, drz->root);

    return 0;
}





int ispisi_gradove(int broj, cvor trenutni){

    if(trenutni == NULL){
        return 0;
    }

    ispisi_gradove(broj, trenutni->lijevo);

    if(trenutni->broj_stanovnika >= broj){
        printf(" %s - %d \n", trenutni->grad, trenutni->broj_stanovnika);
    }

    ispisi_gradove(broj, trenutni->desno);

    return 0;
}


int pronadi_najveci(cvor trenutni){

    int najveci = 0;

    if(trenutni == NULL){

        return 0;
    }
    if(trenutni->desno == NULL){

        return trenutni->broj_stanovnika;
    }

    najveci = pronadi_najveci(trenutni->desno);

    return najveci;
}
