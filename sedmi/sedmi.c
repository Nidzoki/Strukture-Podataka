#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define max_dir_ime 255						// direktorij može imati ime od 255 znakova

struct _direktorij;

typedef struct _direktorij* pozicija;

typedef struct _direktorij {

	char ime[max_dir_ime];	

	pozicija next;
	pozicija djeca;
	pozicija nazad;

}direktorij;


pozicija alociranje_direktorija(char* ime_novog_direktorija, pozicija trenutni_direktorij);


int sortirani_unos_u_listu(pozicija head, pozicija novi_direktorij); 
int ispis_liste(pozicija head);
int izbornik();
int pozivatelj_funkcija(int opcija, pozicija trenutni);

// 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz

int mkdir(pozicija trenutni);
int dir(pozicija trenutni);
pozicija cd_tocka_tocka(pozicija trenutni);
pozicija cd_dir(pozicija trenutni);

int main() {

	direktorij C = { .djeca = NULL, .ime = "C", .next = NULL };		// deklaracija root direktorija

	pozicija trenutni = &C;											// pokazivač na trenutni direktorij (u početku na root direktorij)

	pozivatelj_funkcija(izbornik(), trenutni);


	return 0;
}


pozicija alociranje_direktorija(char* ime_novog_direktorija, pozicija trenutni_direktorij) {	

	pozicija novi_direktorij = NULL;

	novi_direktorij = malloc(sizeof(direktorij));

	if (!novi_direktorij) {
		perror("\nNeuspjesna alokacija memorije za direktorij!\n");
		return NULL;
	}

	novi_direktorij->djeca = NULL;						// nakon alokacije novi direktorij nema djece
	novi_direktorij->next = NULL;
	novi_direktorij->nazad = trenutni_direktorij;

	trenutni_direktorij->djeca->next = novi_direktorij;

	strcpy(novi_direktorij->ime, ime_novog_direktorija);

	return novi_direktorij;
}

int mkdir(pozicija trenutni) {

	pozicija novi_direktorij = NULL;

	char ime_direktorija[max_dir_ime];

	printf("\n Unesite ime direktorija: ");

	scanf_s(" %s", ime_direktorija, max_dir_ime);

	novi_direktorij = alociranje_direktorija(ime_direktorija, trenutni);

	sortirani_unos_u_listu(trenutni->djeca, novi_direktorij);

	return 0;

}


int sortirani_unos_u_listu(pozicija head, pozicija novi_direktorij) {

	while (head->next != NULL) {

		if (strcmp(head->ime, novi_direktorij->ime)) {
			novi_direktorij->next = head->next;
			head->next = novi_direktorij;
			return 0;
		}

		head = head->next;
	}

	head->next = novi_direktorij;

	return 0;

}


int ispis_liste(pozicija head) {				// ispisuje listu

	head = head->next;
	
	while(head != NULL)
		{
		printf("\n\t- %s \n", head->ime);
	} 

		return 0;

}

int dir(pozicija trenutni) {									// ispisuje direktorije koje se nalaze u trenutnom direktoriju

	printf("\n %s: \n", trenutni->ime);
	ispis_liste(trenutni->djeca);
	return 0;
}


int izbornik() {
	int opcija = 0;
					// 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz
	do{
		printf("\n\n 1 - md/mkdir (stvaranje novog direktorija),\n 2 - cd dir (otvaranje određenog direktorija),\n)");
		printf("3 - cd.. (povratak u prethodni direktorij),\n 4 - dir (ispis direktorija koji se nalaze u trenutnom direktoriju),\n");
		printf("5 – izlaz \n \n Unesite opciju: ");

		scanf_s(" %d", &opcija, 1);
		
		if (opcija < 1 || opcija > 5) {

			printf("\n \n Opcija nije valjana! Pokusajte ponovo! \n\n");

		}
	} while (opcija < 1 || opcija > 5);

	return opcija;

}



pozicija cd_tocka_tocka(pozicija trenutni) {

	return trenutni->nazad;

}


int pozivatelj_funkcija(int opcija, pozicija trenutni) {		// 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz

	switch (opcija) {
	case 1:		mkdir(trenutni);					pozivatelj_funkcija(izbornik(), trenutni);	break;
	case 2:		cd_dir(trenutni);					pozivatelj_funkcija(izbornik(), trenutni);	break;
	case 3:		cd_tocka_tocka(trenutni);			pozivatelj_funkcija(izbornik(), trenutni);	break;
	case 4:		dir(trenutni);						pozivatelj_funkcija(izbornik(), trenutni);	break;
	case 5:		printf("\n\n Program ugasen!\n\n");												break;
	default:	break;
	}

	return 0;
}


pozicija cd_dir(pozicija trenutni) {

	pozicija djeca_head = trenutni->djeca;

	char ime_direktorija[max_dir_ime];


	printf("\n Unesite ime direktorija u koji želite uci: ");

	scanf_s(" %s", ime_direktorija, max_dir_ime);

	while (djeca_head != NULL) {

		if (strcpy(ime_direktorija, djeca_head->ime) == 0) {
			return djeca_head;
		}

		djeca_head = djeca_head->next;
	}

	printf("\n Direktorij ne postoji!\n");

	return trenutni;

}
