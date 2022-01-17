#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_POLINOM 1024

struct _polinom;
typedef struct _polinom * pozicija;

typedef struct _polinom{

    int koeficijent;
    int eksponent;

    pozicija next;

}polinom;

pozicija stvori_polinom(int koeficijent, int eksponent);

int ucitaj(char *datoteka, pozicija head1, pozicija head2); 
int dodaj_u_listu(pozicija head, char *string); 

int sortirano(pozicija head, pozicija novi); 

int zbroji(pozicija head1, pozicija head2, pozicija head_zbrajanje);
int mnozi(pozicija head1, pozicija head2, pozicija head_mnozenje); 

int ispisi(pozicija head); 
 
int dodaj_iza(pozicija ref, pozicija novi); 
int brisi_iza(pozicija prosli); 

int gasi_struju_motaj_kablove(pozicija head); 

int main(){

    polinom head1 = { .koeficijent = 0, .eksponent = 0, .next = NULL}, head2 = { .koeficijent = 0, .eksponent = 0, .next = NULL};
    polinom head_zbrajanje = { .koeficijent = 0, .eksponent = 0, .next = NULL};
    polinom head_mnozenje = { .koeficijent = 0, .eksponent = 0, .next = NULL};

    char dat[MAX_POLINOM] = { 0 };

    printf(" Upisite ime datoteke: ");

    scanf(" %s", dat);

    ucitaj(dat, &head1, &head2);


    printf(" Polinomi: \n");
    ispisi(&head1);
    printf("\n ");
    ispisi(&head2);

    printf("\n Zbroj:\n ");
    zbroji(&head1, &head2, &head_zbrajanje);
    ispisi(&head_zbrajanje);

    printf(" Umnozak:\n ");
    mnozi(&head1, &head2, &head_mnozenje);
    ispisi(&head_mnozenje);

    gasi_struju_motaj_kablove(&head1);
    gasi_struju_motaj_kablove(&head2);

    gasi_struju_motaj_kablove(&head_zbrajanje);
    gasi_struju_motaj_kablove(&head_mnozenje);

    
    return 0;
    
}

int ucitaj(char * datoteka, pozicija head1, pozicija head2)
{
    FILE * dat = NULL;
    char string[MAX_POLINOM] = { 0 }; 

    dat = fopen(datoteka, "r");
    if(dat == NULL)
    {
        printf("Nemoguce otvoriti datoteku!\n");
		return -1;
    }

    fgets(string, MAX_POLINOM, dat); 
    dodaj_u_listu(head1, string); 
    
    fgets(string, MAX_POLINOM, dat); 
    dodaj_u_listu(head2, string); 

    fclose(dat);

    return 0;
}



int dodaj_u_listu(pozicija head, char * string)
{
    char* str = string;
    int koeficijent = 0;
    int eksponent = 0;
    int br = 0;

    pozicija novi = NULL;

    while(strlen(str) > 1) {
        
        if(sscanf(str, " %d %d %n", &koeficijent, &eksponent, &br)){            
            printf("Format polinoma nije valjan.");
            return -1;
        }
        
        novi = stvori_polinom(koeficijent, eksponent);

        if (novi == NULL){
			return -1;
		}
        sortirano(head, novi);
        
        str += br;

    }
    return 0;
}

int sortirano(pozicija head, pozicija novi){

    while(head->next!=NULL && head->next->eksponent < novi->eksponent){

        head = head->next;
    }
   
    if(head->next == NULL || head->next->eksponent != novi->eksponent){

       dodaj_iza(head, novi);
    }
    else  {

        if(head->next->koeficijent + novi->koeficijent == 0)
            brisi_iza(head);

        else
            head->next->koeficijent = head->next->koeficijent + novi->koeficijent;
    }
    return 0;
}


int mnozi(pozicija head1, pozicija head2, pozicija head_mnozenje)
{
	pozicija i = NULL, j = NULL, novi = NULL;

	for (i = head1->next; i != NULL; i = i->next){

		for (j = head2->next; j != NULL; j = j->next){
            
			novi = stvori_polinom(i->koeficijent * j->koeficijent, i->eksponent + j->eksponent);

			if (novi == NULL){
				return -1;
			}
            sortirano(head_mnozenje, novi);
		}
	}
	return 0;
}


int zbroji(pozicija head1, pozicija head2, pozicija head_zbrajanje){

	pozicija i = NULL, j = NULL, novi = NULL;

	for (i = head1->next; i != NULL; i = i->next){
		novi = stvori_polinom(i->koeficijent, i->eksponent);

		if (novi == NULL){

			return -1;
		}

		sortirano(head_zbrajanje, novi);
        
	}
	for (j = head2->next; j != NULL; j = j->next){

		novi = stvori_polinom(j->koeficijent, j->eksponent);

		if (novi == NULL){
			return -1;
		}
		sortirano(head_zbrajanje, novi);
    }

	return 0;
    
}


int ispisi(pozicija head){

    while(head->next != NULL){

        if(head->next->next == NULL)
        printf("%d x ^ (%d)\n", head->next->koeficijent, head->next->eksponent); 

        else
        printf("%d x ^ (%d) + ", head->next->koeficijent, head->next->eksponent);

        head = head->next;
    }
    return 0;
}

pozicija stvori_polinom(int koeficijent, int eksponent){
    pozicija novi = (pozicija)malloc(sizeof(polinom));

    if(novi == NULL){

        printf("Neuspjesna alokacija memorije!\n");

        return NULL;
    }

    novi->eksponent = eksponent;
    novi->koeficijent = koeficijent;
    novi->next = NULL;

    return novi;
}

int dodaj_iza(pozicija ref, pozicija novi){

    novi->next = ref->next;
    ref->next = novi;

    return 0;
}

int brisi_iza(pozicija prosli){

	pozicija pol = prosli->next;
	prosli->next = pol->next;

	gasi_struju_motaj_kablove(pol);

	return 0;
}

int gasi_struju_motaj_kablove(pozicija head){

	while (head->next != NULL){

		brisi_iza(head);
	}
    
	return 0;
}
