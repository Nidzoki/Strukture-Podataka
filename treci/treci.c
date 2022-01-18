#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_IME 30


struct _osoba;
typedef struct _osoba * pozicija;
typedef struct _osoba{

	char ime[MAX_IME];
	char prezime[MAX_IME];

	int godiste;

	pozicija next;

}osoba;

int dodaj_na_pocetak(pozicija head, char * ime, char * prezime, int godiste);
int dodaj_na_kraj(pozicija head, char * ime, char * prezime, int godiste);
int dodaj_iza(pozicija ref, pozicija osoba);
int umetni_iza(pozicija head, char * ime, char * prezime, int godiste, char * sljedeci_p);
int umetni_ispred(pozicija head, char * ime, char * prezime, int godiste, char * prethodni);
int dodaj_ispred(pozicija head, pozicija ref, pozicija osoba);
int izbrisi_iza(pozicija head, char * prezime);
int ispisi(pozicija head);
int ucitaj_txt(pozicija head, char * datoteka);
int ispisi_txt(pozicija head, char * dat);
int sortirano(pozicija head, pozicija osoba);
int izbornik(pozicija head);

pozicija stvori_osobu(char * ime, char * prezime, int godiste);
pozicija pronadi_zadnjeg(pozicija head);
pozicija pronadi_ispred(pozicija head, char * prezime);
pozicija pretrazi_prezime(pozicija head, char * prezime);

int main(){

	osoba head = {.ime ={0}, .prezime ={0}, .godiste = 0, .next = NULL};

	while(!izbornik(&head)){};

	return 0;}

pozicija stvori_osobu(char * ime, char * prezime, int godiste){
	pozicija novi = (pozicija)malloc(sizeof(osoba));
	
	if(novi == NULL){
		printf("Pogreska pri alociranju memorije!");
		return NULL;
	}

	strcpy(novi->ime,ime);
	strcpy(novi->prezime,prezime);
	novi->godiste = godiste;
	novi->next = NULL;

	return novi;

}

int dodaj_iza(pozicija ref, pozicija osoba){
	osoba->next = ref->next;
	ref->next = osoba->next;

	return 0;
}
int dodaj_ispred(pozicija head, pozicija ref, pozicija osoba){
	pozicija novi = NULL, sljedeci = NULL;

	novi = stvori_osobu(osoba->ime, osoba->prezime, osoba->godiste);

	if(novi == NULL)
		return -1;
	
	sljedeci = pronadi_ispred(head, ref->prezime);

	dodaj_iza(sljedeci, novi);

}

int dodaj_na_pocetak(pozicija head, char * ime, char * prezime, int godiste){

	pozicija novi = NULL;
	novi = stvori_osobu(ime, prezime, godiste);

	if(novi == NULL)
		return -1;

		dodaj_iza(head, novi);
		
}

pozicija pronadi_zadnjeg(pozicija head){
	while(head->next != NULL){
		head = head->next;
	}

	return head;
}

int dodaj_na_kraj(pozicija head, char * ime, char * prezime, int godiste){
	
	pozicija zadnji = NULL, novi = NULL;
	
	zadnji = pronadi_zadnjeg(head);
	novi = stvori_osobu(ime, prezime, godiste);

	if(novi == NULL)
		return -1;
	
	dodaj_iza(zadnji, novi);

	return 0;

}

pozicija pronadi_ispred(pozicija head, char * prezime){

	pozicija osoba = NULL;
	osoba = pretrazi_prezime(head, prezime);

	if(osoba == NULL){
		printf("Osoba ne postoji!");
		return 0;
	}

	while(head->next != NULL && head->next != osoba){
		head = head->next;
	}

	if(head->next == osoba)
		return head;
	
	else
	return NULL;

}


pozicija pretrazi_prezime(pozicija head, char * prezime){

	head = head->next;

	while(head != NULL){
		if(strcmp(head->prezime, prezime) == 0){
			return head;
		}
		head = head->next;
	}

	return NULL;

}


int izbrisi_iza(pozicija head, char * prezime){

	pozicija prije = NULL, osoba = NULL;

	prije = pronadi_ispred(head, prezime);

	osoba = prije->next;

	prije->next = osoba ->next;

	free(osoba);

	return 0;
}

int ispisi(pozicija head){
	head = head->next;
	while(head != NULL){
		printf(" \nIme: %s\n Prezime: %s\n Godiste: %d\n" , head->ime, head->prezime, head->godiste);
		head = head->next;
	}

	return 0;
}


int ucitaj_txt(pozicija head, char * datoteka){
	FILE * dat = NULL;
	char str[MAX_IME] = {0};
	char * ime, * prezime;
	int godiste;
	pozicija osoba = NULL;

	dat = fopen(datoteka, "r");
	if(dat == NULL){
		printf("Nemoguce otvoriti datoteku!");
		return -1;
	}

	while(!feof(dat)){
		osoba = (pozicija)malloc(sizeof(osoba));
		fgets(str, MAX_IME, dat);
		if(sscanf(str, "%s %s %d", osoba->ime, osoba->prezime, osoba->godiste) == 3){
			sortirano(head, osoba);
		}
	}
	fclose(dat);

	return 0;
}


int sortirano(pozicija head, pozicija osoba){
	
	while(head != NULL && strcmp(head->prezime, osoba->prezime) < 0){
		head = head->next;
	}

	dodaj_iza(head, osoba);

	return 0;

}

int ispisi_txt(pozicija head, char * datoteka){
	FILE * dat = NULL;
	dat = fopen(datoteka, "w");

	if(dat != NULL){
		printf("Nemoguce otvoriti datoteku!");

		return -1;
	}

	while(head != NULL){
		fprintf(dat, "%s %s %d\n", head->ime, head->prezime, head->godiste);
		head = head->next;
	}

	fclose(dat);
	return 0;
}

int umetni_iza(pozicija head, char * ime, char * prezime, int godiste, char * sljedeci_p){

	pozicija sljedeci = NULL, novi = NULL;

	novi = stvori_osobu(ime, prezime, godiste);

	if(novi == NULL)return -1;

	sljedeci = pretrazi_prezime(head, sljedeci_p);

	dodaj_iza(sljedeci, novi);

	return 0;

}

int umetni_ispred(pozicija head, char * ime, char * prezime, int godiste, char * prethodni){
	pozicija prosli = NULL, novi = NULL;

	novi = stvori_osobu(ime, prezime, godiste);

	if(novi == NULL)return -1;

	prosli = pretrazi_prezime(head, prethodni);

	dodaj_iza(prosli, novi);

	return 0;
}

int izbornik(pozicija head){

	int odabir = 0;

	char ime[MAX_IME] = {0};
	char prezime[MAX_IME] = {0};
	int godiste = 0;
	char ref[MAX_IME] ={0};
	char dat[256];

	pozicija osoba = NULL;

	while(odabir > 10 || odabir < 1) {
		printf( " 1.  Dodaj osobu na pocetak \n"
				" 2.  Dodaj osobu na kraj \n"
				" 3.  Izbrisi osobu \n"
				" 4.  Ispisi listu \n"
				" 5.  Ucitaj tekstualnu datoteku \n"
				" 6.  Ispisi u tekstualnu datoteku \n"
				" 7.  Sortirano unosenje \n"
				" 8.  Dodaj iza studenta po prezimenu \n"
				" 9.  Dodaj prije studenta po prezimenu \n"
				" 10. Izlaz\n\n");

		scanf(" %d", &odabir);

	}

	switch(odabir){
		case 1: 	printf("\n Unesite podatke u formatu [ime] [prezime] [godiste]:\n");
					scanf(" %s %s %d", ime, prezime, &godiste);
					dodaj_na_pocetak(head, ime, prezime, godiste);
					break;
		case 2: 	printf("\n Unesite podatke u formatu [ime] [prezime] [godiste]");
					scanf(" %s %s %d", ime, prezime, &godiste);
					dodaj_na_kraj(head, ime, prezime, godiste);
					break;				
		case 3: 	printf("\nUnesite prezime osobe koju zelite obrisati:\n");
					scanf(" %s", prezime);
					izbrisi_iza(head, pronadi_ispred(head, prezime)->prezime);
					break;
		case 4:		 ispisi(head);
					break;
		case 5:		 printf("\n Unesite ime datoteke:\n");
					scanf(" %s",dat);
					ucitaj_txt(head, dat);
					break;
		case 6: 	printf("\n Unesite ime datoteke:\n");
					scanf(" %s",dat);
					ispisi_txt(head, dat);
					break;
		case 7: 	printf("Unesite podatke u formatu [ime] [prezime] [godiste]: \n");
					scanf(" %s %s %d", ime, prezime, &godiste);
					osoba = stvori_osobu(ime, prezime, godiste);
					sortirano(head, osoba);
					break;
		case 8: printf("\n Unesite podatke u formatu [ime] [prezime] [godiste] [prezime referentne osobe]");
					scanf(" %s %s %d %s", ime, prezime, &godiste, ref);
					umetni_iza(head, ime, prezime, godiste, ref);
					break;	
		case 9: printf("\n Unesite podatke u formatu [ime] [prezime] [godiste] [prezime referentne osobe]");
					scanf(" %s %s %d", ime, prezime, &godiste, ref);
					umetni_ispred(head, ime, prezime, godiste, ref);
					break;	
		case 10: return -1;
		
		}
		return 0;

}
