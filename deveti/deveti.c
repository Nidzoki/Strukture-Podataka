#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<malloc.h>

#define MAX_STR 1024
#define N 10

struct _element;

typedef struct _element * cvor;

typedef struct _element {

    int br;

    cvor lijevo;
    cvor desno;

}element;



struct element_liste;

typedef struct element_liste * pozicija;

typedef struct element_liste{

    int broj;

    pozicija next;

}el;


cvor dodaj(int broj, cvor node);

int replace(cvor trenutni);

int dodaj_u_listu(pozicija head, cvor node);
int dodaj_broj_u_listu(pozicija head, int br);
pozicija pronadi_zadnji(pozicija head);

int ispisi_u_datoteku(pozicija trenutni);
int ispisi_listu(pozicija head);
int inorder(cvor node);

cvor brisi_stablo(cvor root);
int brisi_listu(pozicija head);



int main(){

    int niz[N] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };

    int i = 0;
    int n = 0;

    char ime_datoteke[MAX_STR];

    cvor root = NULL;
    el head = { .next = NULL, .broj = 0};

    for(i = 0; i < N; i++){

        root = dodaj(niz[i], root);
    }
    

    printf(" Inorder: ");
    inorder(root);

    dodaj_u_listu(&head, root);

    ispisi_u_datoteku(&head);

    brisi_listu(&head); 

    replace(root);

    printf("\br Zamijenjeno inorder: ");

    inorder(root);

    dodaj_u_listu(&head, root);

    ispisi_u_datoteku(&head);

    srand((unsigned) time(NULL));

    printf("\br Upisite kolicinu brojeva: ");

    scanf(" %d", &n);
    
    root = brisi_stablo(root);

    for(i = 0; i < n; i++){

        root = dodaj(rand()%(90-10+1) + 10, root); 
    }

    printf("\br Nasumicno inorder: ");
    
    inorder(root);

    return 0;
}

cvor dodaj(int broj, cvor node){

    if(node == NULL){

        node = (cvor)malloc(sizeof(element));

        node->br = broj;

        node->lijevo = NULL;

        node->desno = NULL;

    }
    else if( broj >= node->br ){

        node->lijevo = dodaj( broj, node->lijevo );

    }
    else if( broj < node->br ){

        node->desno = dodaj( broj, node->desno );

    }
    return node;
}



int inorder(cvor node){

    if(node == NULL){

        return 0;
    }

    inorder(node->lijevo);

    printf("%d ", node->br);

    inorder(node->desno);

    return 0;
}



pozicija pronadi_zadnji(pozicija head){

    pozicija temp = head;

    while(temp->next != NULL)
        temp = temp->next;
        
    return temp;

}



int replace(cvor trenutni){

    if(trenutni->lijevo == NULL && trenutni->desno == NULL){

        trenutni->br = 0;

    }

    else if(trenutni->lijevo == NULL && trenutni->desno != NULL){

        trenutni->br = replace(trenutni->desno) + trenutni->desno->br;

    }

    else if(trenutni->lijevo != NULL && trenutni->desno == NULL){
        
        trenutni->br = trenutni->lijevo->br + replace(trenutni->lijevo);

    }

    else{

        trenutni->br = trenutni->lijevo->br + trenutni->desno->br + replace(trenutni->lijevo) + replace(trenutni->desno);

    }

    return trenutni->br; 
}






int dodaj_broj_u_listu(pozicija head, int br){

    pozicija novi = NULL;
    pozicija zadnji = NULL;

    novi = (pozicija)malloc(sizeof(el));

    if(novi == NULL){

        printf("Nemoguce alocirati memoriju!");

        return 0;
    }
    
    zadnji = pronadi_zadnji(head);

    novi->broj = br;

    novi->next = zadnji->next; 

    zadnji->next = novi;

}



int dodaj_u_listu(pozicija head, cvor node){

    if(NULL == node){
        return 0;
    }

    dodaj_u_listu(head, node->lijevo);

    dodaj_broj_u_listu(head, node->br);

    dodaj_u_listu(head, node->desno);

    return 0;
}



int ispisi_u_datoteku(pozicija head){

    FILE * datoteka = NULL;

    datoteka = fopen("datoteka.txt", "a");

    while(head->next!= NULL){

        fprintf(datoteka, " %d ", head->next->broj);

        head = head->next;
    }

    fprintf(datoteka, "\n");

    fclose(datoteka);

    return 0;
}

int ispisi_listu(pozicija head){

    while(head->next!= NULL){

        printf("%d ", head->next->broj);

        head = head->next;
    }

    return 0;
}

int brisi_listu(pozicija head){

    pozicija temp = NULL;

    while(head->next != NULL){

        temp = head->next;

        head->next = temp->next;

        free(temp);
    }
}

cvor brisi_stablo(cvor node){

    if(node != NULL){    

        brisi_stablo(node->lijevo);

        brisi_stablo(node->desno);

        free(node);
    }

    return NULL;
}


