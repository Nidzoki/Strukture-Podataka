#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct _cvor;

typedef struct _cvor * pozicija;

typedef struct _cvor{

    int broj;

    pozicija lijevo;
    pozicija desno;

}cvor;

pozicija dodaj(int br, pozicija element);
pozicija brisi(int br, pozicija element);
pozicija trazi_najmanji(pozicija element);
pozicija trazi_broj(int br, pozicija element);

int inorder(pozicija trenutni);
int preorder(pozicija trenutni);
int postorder(pozicija trenutni);

int izbornik(pozicija root);


int main(){

    pozicija root = NULL;

    izbornik(root);

    return 0;
}

pozicija dodaj(int br, pozicija element){

    if(element == NULL){
        element = (pozicija)malloc(sizeof(cvor));

        element->broj = br;

        element->lijevo = NULL;
        element->desno = NULL; 

    }
    else if(br > element->broj){
        element->desno = dodaj(br, element->desno);
    }
    else if(br < element->broj){
        element->lijevo = dodaj(br, element->lijevo);
    }
    
    return element;
}

pozicija brisi(int br, pozicija element){

    pozicija temp = NULL;
    if(NULL == element){

        printf(" Element ne postoji!");
    }

    else if(br > element->broj){

        element->desno = brisi(br, element->desno);
    }

    else if(br < element->broj){

        element->lijevo = brisi(br, element->lijevo);
    }
    
    else if(element->lijevo != NULL && element->desno != NULL){

        temp = trazi_najmanji(element->desno);

        element->broj = temp->broj;

        element->desno = brisi(element->broj, element->desno);
    }
    else{

        temp= element;

        if(NULL == element->lijevo){

            element = element->desno;
        }

        else{
            
            element = element->lijevo;

            free(temp);
        }
    }
    return element;
}

int inorder(pozicija trenutni){

	if(trenutni == NULL){

		return 0; 
    }

	inorder(trenutni->lijevo);

	printf(" %d ", trenutni->broj);

	inorder(trenutni->desno);

	return 0;
}


int preorder(pozicija trenutni){

	if(trenutni == NULL){

		return 0; 
    }

	printf(" %d ", trenutni->broj);

	inorder(trenutni->lijevo);

	inorder(trenutni->desno);

	return 0;
}


int postorder(pozicija trenutni){

	if(trenutni == NULL){

		return 0; 
    }

    inorder(trenutni->lijevo);

	inorder(trenutni->desno);

	printf(" %d ", trenutni->broj);

	return 0;
}



pozicija trazi_broj(int br, pozicija element){

    if (element == NULL){

        return NULL;
    }

    else if(br > element->broj){

        return trazi_broj(br, element->desno);
    }

    else if(br < element->broj){

        return trazi_broj(br, element->lijevo);
    }

    else{

        return element;
        }
}

pozicija trazi_najmanji(pozicija element){

    if(NULL == element){

        return NULL;
    }

    else if(NULL == element->lijevo){

        return element;
    }

    else{

        return trazi_najmanji(element->lijevo);
    }
}




int izbornik(pozicija root)
{
    int br, i, odabir;
    pozicija pos = NULL;

    printf(

    "\n 1 - Dodaj broj\n"
    " 2 - Izbrisi broj\n"
    " 3 - Pronadi broj\n"
    " 4 - Inorder ispis\n"
    " 5 - Preorder ispis\n"
    " 6 - Postorder ispis\n"
    " 7 - izlaz\n"
    );
    while(odabir < 1  || odabir > 7){
    printf(" Opcija: ");
    scanf(" %d", &odabir);

    if(odabir < 1  || odabir > 7)
    printf(" Nepostojeca opcija!\n");

    printf("\n");
    }
    switch (odabir){
    case 1:
        printf(" Koji broj zelite dodati:");
		scanf(" %d", &br);

        root = dodaj(br, root);

        izbornik(root);

        break;

    case 2:
        printf(" Koji broj zelite izbrisati: ");
        scanf(" %d", &br);

        root = brisi(br, root);

        izbornik(root);

        break;

    case 3:
        printf(" Koji broj zelite pronaci:");
        scanf(" %d", &br);

        if(trazi_broj(br, root) !=  NULL){
            printf(" Broj se nalazi u stablu.\n", br );
        }
        else{
            printf(" Broj se ne nalazi u stablu.\n", br);
        }

        izbornik(root);

        break;

    case 4:  

        printf(" Inorder ispis: ");

        inorder(root);

        izbornik(root);

        break;

    case 5:  

        printf(" Preorder ispis: ");

        preorder(root);

        izbornik(root);

        break;

    case 6:  

        printf(" Postorder ispis: ");

        postorder(root);

        izbornik(root);

        break;

    case 7:

        return 0;
    }
    return 1;
}

