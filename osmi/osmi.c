#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct _cvor;

typedef struct _cvor * Pozicija;

typedef struct _cvor{

    int broj;

    Pozicija lijevo;
    Pozicija desno;


}cvor;


Pozicija stvori_cvor(int br);
Pozicija unesi_broj(int br, Pozicija root);
Pozicija pronadi_element(int br, Pozicija root);
Pozicija brisi(int br, Pozicija root);
Pozicija pronadi_najmanji(Pozicija root);

int ispis_inorder(Pozicija root);
int ispis_postorder(Pozicija root);
int ispis_preorder(Pozicija root);
int ispisi_opcije();
int odabir();
int meni(Pozicija root);



int main(){

    Pozicija root = NULL;

    meni(root);

    printf("Kraj programa.");

    return 0;
}


Pozicija stvori_cvor(int br){                       // prima broj a vraća novi čvor stabla
    
    Pozicija novi_cvor = NULL;

    novi_cvor = malloc(sizeof(cvor));

    if(novi_cvor == NULL){
        perror("\n Neuspjela alokacija memorije!\n");
        return NULL;
    }

    novi_cvor ->broj = br;
    novi_cvor ->desno = NULL;
    novi_cvor ->lijevo = NULL;

    return novi_cvor;
}


Pozicija unesi_broj(int br, Pozicija root){         // prima broj i pokazivač na root i unosi broj

    if(root == NULL){
        root = stvori_cvor(br);
        return root;
    }
    else if(root->broj == br){
        return root;
    }
    else if(root->broj < br){
        unesi_broj(br, root->desno);
    }
    else{
        unesi_broj(br, root->lijevo);
    }
}


Pozicija pronadi_element(int br, Pozicija root){    // prima broj, pokazivač na root, vraća pokazivač na traženi broj, ako nije unesen vraća NULL
    if(root == NULL){
        return root;
    }
    else if(root->broj == br){
        return root;
    }
    else if(root->broj < br){
        pronadi_element(br, root->desno);
    }
    else if(root->broj > br){
        pronadi_element(br, root->lijevo);
    }
}


Pozicija pronadi_najmanji(Pozicija root){           // prima root i vraća pokazivač na najmanji broj

    while(root->lijevo != NULL){
        root = root->lijevo;
    }

    return root;

}


int ispis_inorder(Pozicija root){                   // prima broj pokazivač na root i ispisuje brojeve od manjeg ka većem

    if(root == NULL){
        printf(" %d", root->broj);
    }
    else{
        ispis_inorder(root->lijevo);
        printf(" %d", root->broj);
        ispis_inorder(root->desno);
    }
    return 0;
}


int ispis_postorder(Pozicija root){                   // prima broj pokazivač na root i ispisuje brojeve od većeg ka manjem

    if(root == NULL){
        printf(" %d", root->broj);
    }
    else{
        ispis_inorder(root->desno);
        printf(" %d", root->broj);
        ispis_inorder(root->lijevo);
    }
    return 0;
}


int ispis_preorder(Pozicija root){                  // prima broj pokazivač na root i ispisuje brojeve od manjeg ka većem

    if(root == NULL){
        printf(" %d", root->broj);
    }
    else{printf(" %d", root->broj);
        ispis_inorder(root->lijevo);
        ispis_inorder(root->desno);
    }
    return 0;
}


Pozicija brisi(int br, Pozicija root){              // prima broj i root, te briše taj broj iz stabla

    if(root == NULL){

        return root;
    }
    else if(root->broj < br){

        root->lijevo = brisi(root->broj, root->lijevo);
    }
    else if(root->broj > br){

        root->desno = brisi(root->broj, root->desno);
    }
    else{

        if(root->desno == NULL && root->lijevo == NULL){

            free (root);
            root = NULL;
            return root;
        }
        else if(root->lijevo == NULL){

            Pozicija temp = root;
            root = root->desno;
            free(temp);
            return root;
        }
        else if(root->desno == NULL){

            Pozicija temp = root;
            root = root->lijevo;
            free(temp);
            return root;
        }
        else{

            Pozicija temp = pronadi_najmanji(root->desno);
            root->broj = temp->broj;
            root->desno = brisi(temp->broj, root->desno);
            return root;
        }
    }
}


int ispisi_opcije(){                                // ispisuje opcije

    printf("\n 1 - Unesi broj\n 2 - Pronadi element\n 3 - Brisi broj\n 4 - Ispisi stablo(inorder)\n 5 - Ispisi stablo(preorder)\n 6 - Ispisi stablo(postorder)\n 7 - Izlaz\n");
    
    return 0;
}


int odabir(){                                       // vraća korisnikov odabir

    int broj =  0;

    printf("\n Unesite opciju: ");
    scanf(" %d", &broj);

    if(broj < 1 || broj > 7 ){

        printf("\n Nepostojeca opcija! Unesite opciju ponovo!\n");
        return odabir();
    }
    else{

        return broj;
    }
}


int meni(Pozicija root){

    while(1){

        int opcija = 0;

        ispisi_opcije();

        opcija = odabir();

        if(opcija == 1){
            int br;
            printf("\n Koji broj zelite unijeti? \n");
            scanf(" %d", &br);
            unesi_broj(br, root);
        }
        else if(opcija == 2){
            if(root == NULL){
                printf("\n Stablo je prazno!\n");
            }
            else{
                int br;
                Pozicija broj;
                printf("\n Koji broj zelite pronaci? \n");
                scanf(" %d", &br);
                broj = pronadi_element(br, root);
                if(broj){
                    printf("\n Broj se nalazi u stablu, njegova adresa je %p\n", broj);
                }
                else{
                    printf("\n Broj se ne nalazi u stablu.\n");
                }
            }
        }
        else if(opcija == 3){
            int br;
            printf("\n Koji broj zelite obrisati? \n");
            scanf(" %d", &br);
            brisi(br, root);
        }
        else if(opcija == 4){
            if(root == NULL){
                printf("\n Stablo je prazno!");
            }
            else{
                ispis_inorder(root);
            }
        }
        else if(opcija == 5){
            if(root == NULL){
                printf("\n Stablo je prazno!");
            }
            else{
                ispis_preorder(root);
            }
        }
        else if(opcija == 6){
            if(root == NULL){
                printf("\n Stablo je prazno!");
            }
            else{
            ispis_postorder(root);
            }
        }
        else{
            break;
        }
    }

    return 0;
}












