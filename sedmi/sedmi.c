#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_DIR_IME 255
#define MAX 1024

struct _Cvor;

typedef struct _Cvor * pozicija_cvor;

typedef struct _Cvor{

	char ime[MAX_DIR_IME];

	pozicija_cvor braca;
	pozicija_cvor djeca;

}Cvor;

struct _Stog;

typedef struct _Stog * pozicija_stog;

typedef struct _Stog{

	pozicija_cvor direktorij;
	pozicija_stog next;

}Stog;

pozicija_cvor mkdir(char* ime, pozicija_cvor trenutni);
pozicija_cvor umetni_direktorij(pozicija_cvor trenutni, pozicija_cvor novi);
pozicija_cvor cd(pozicija_stog head, pozicija_cvor trenutni, char* ime);

pozicija_stog pronadi_zadnjeg(pozicija_stog head);
pozicija_stog pronadi_predzadnjeg(pozicija_stog head);

int stavi_na_stog(pozicija_stog head, pozicija_cvor direktorij);
int skini_sa_stoga(pozicija_stog head);
int dir(pozicija_cvor trenutni);
int Exit(pozicija_cvor trenutni);
int path(pozicija_stog head);
int izbornik(pozicija_cvor trenutni, pozicija_stog head);

int main(){	
	
	Stog head;

	Cvor root;
	
	strcpy(root.ime, "C:");

	root.djeca = NULL;
	root.braca = NULL;

	head.direktorij = NULL;
	head.next = NULL;

	stavi_na_stog(&head, &root);
	izbornik(&root, &head);

	return 0;
}


pozicija_cvor mkdir(char * ime, pozicija_cvor trenutni){

	pozicija_cvor novi = NULL;
	novi = (pozicija_cvor)malloc(sizeof(Cvor));

	if (novi == NULL)
	{
		printf("Neuspjela alokacija memorije!\n");

		return NULL;
	}

	strcpy(novi->ime, ime);

	novi->djeca = NULL;

	novi->braca = NULL;

	trenutni->djeca = umetni_direktorij(trenutni->djeca, novi); 

	return trenutni;
}


pozicija_cvor umetni_direktorij(pozicija_cvor trenutni, pozicija_cvor novi){

	if (trenutni == NULL){

		return novi;
	}
	else if (strcmp(trenutni->ime, novi->ime) < 0){

		trenutni->braca = umetni_direktorij(trenutni->braca, novi);
	}
	else if (strcmp(trenutni->ime, novi->ime) > 0){

		novi->braca = trenutni;

		return novi;
	}
	else{

	printf("Direktorij vec postoji!\n");

		free(novi);
	}

	return trenutni;
}

int path(pozicija_stog head){

	head = head->next;

	while (head != NULL){

		printf("%s\\", head->direktorij->ime);

		head = head->next;
	}

	printf("> ");

	return 0;
}


int dir(pozicija_cvor trenutni){

	if (trenutni->djeca == NULL){
	
		printf("Direktorij je prazan!\n");
	}

	while (trenutni->djeca != NULL){

		printf("<DIR>\t\t %s\n", trenutni->djeca->ime);

		trenutni->djeca = trenutni->djeca->braca;
	}

	return 0;
}

int stavi_na_stog(pozicija_stog head, pozicija_cvor direktorij){

	pozicija_stog novi = NULL;

	novi = (pozicija_stog)malloc(sizeof(Stog));

	if (novi == NULL){

		printf("Neuspjela alokacija memorije!\n");
		return -1;
	}
  
int skini_sa_stoga(pozicija_stog head){

	if (head->next == NULL){
		return 0;
	}

	pozicija_stog prethodni = pronadi_predzadnjeg(head);
	pozicija_stog element = NULL;

	element = prethodni->next;
	prethodni->next = element->next;

	free(element);
	
	return 0; 
}

	pozicija_stog zadnji = pronadi_zadnjeg(head);

	novi->next = zadnji->next;
	zadnji->next = novi;

	novi->direktorij = direktorij;

	return 0;
}

pozicija_stog pronadi_zadnjeg(pozicija_stog head){

	while (head->next != NULL){

		head = head->next;
	}
	return head;
}

pozicija_stog pronadi_predzadnjeg(pozicija_stog head){

	while (head->next->next != NULL){

		head = head->next;
	}
	return head;
}



int path(pozicija_stog head){

	head = head->next;

	while (head != NULL){

		printf("%s\\", head->direktorij->ime);

		head = head->next;
	}

	printf("> ");

	return 0;
}

pozicija_cvor cd(pozicija_stog head, pozicija_cvor trenutni, char * ime){

	if (NULL == trenutni->djeca){

		printf("Direktorij je prazan!\n");

		return trenutni;
	}

	while (trenutni->djeca != NULL && strcmp(trenutni->djeca->ime, ime)!=0){
		
		trenutni->djeca = trenutni->djeca->braca;
	}

	if (trenutni->djeca == NULL){

		printf("Nepostojeci direktorij!\n");

		return trenutni;
	}

	stavi_na_stog(head, trenutni->djeca);
	
	return trenutni->djeca;
}



int dir(pozicija_cvor trenutni){

	if (trenutni->djeca == NULL){
	
		printf("Direktorij je prazan!\n");
	}

	while (trenutni->djeca != NULL){

		printf("<DIR>\t\t %s\n", trenutni->djeca->ime);

		trenutni->djeca = trenutni->djeca->braca;
	}

	return 0;
}



int izbornik(pozicija_cvor trenutni, pozicija_stog head){

	pozicija_cvor prvi = trenutni;

	char ime[MAX] = { 0 };
	char str[MAX] = { 0 };
	char naredba[MAX] = { 0 };

	for(;;){

		path(head);

		fgets(str, MAX, stdin);

		sscanf(str, "%s %s", naredba, ime);

		if (strcmp(naredba, "md")==0 || strcmp(naredba, "mkdir")){

			trenutni = mkdir(ime, trenutni);
		}
		else if (strcmp(naredba, "dir")==0){

			dir(trenutni);
		}
		else if (strcmp(naredba, "cd..")==0){
			if(trenutni->ime == "C:"){
				continue;
			}
			else{
			skini_sa_stoga(head);

			trenutni = pronadi_zadnjeg(head)->direktorij;
			}
		}
		else if(strcmp(naredba, "cd")==0){

			trenutni = cd(head,trenutni,ime);
		}
		else if (strcmp(naredba, "exit")==0){

			return 0;
		}
		else{
			printf("Nepostojeca naredba!\n", naredba);
		}
	}
	return 0;
}
