/*
Dodati funkciju za sortiranje liste.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50
 
struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;
 
int PrependList(Position head, char* name, char* surname, int birthYear);
int AppendList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
Position FindSurname(Position first, char* surname);
Position FindBefore(Position, Position);
int DeleteAfter(Position head, char* surname);

int swap(Position head, Position one, Position two);
int CountList(Position head);
int SortList(Position head);

 
int main(int argc, char** argv) {
	
	Person p = {"","", 0, NULL};
    Position head = &p;

    printf("a");

    AppendList(head, "Jure", "Juric", 1990);            printf("a");
    AppendList(head, "Ante", "Anic", 1990);             printf("a");
    AppendList(head, "Jakov", "Cosic", 1990);           printf("a");
    AppendList(head, "Mate", "Horvat", 1990);           printf("a");
    AppendList(head, "Matea", "Kraljevic", 1990);       printf("a");
    AppendList(head, "Stipe", "Lovric", 1990);          printf("a");
    AppendList(head, "Ilija", "Manderalo", 1990);       printf("a");

    SortList(head);                                     printf("a");

    PrintList(head->next);                              printf("a");

	return 0;
}
 
int PrependList(Position head, char* name, char* surname, int birthYear) {
 
	Position newPerson = NULL;
 
	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}
 
	InsertAfter(head, newPerson);
 
	return EXIT_SUCCESS;
}
 
int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;
 
	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}
 
	last = FindLast(head);

    newPerson->next = last->next;
	last->next = newPerson;
 
 
	return EXIT_SUCCESS;
}
 
int PrintList(Position first)
{
	Position temp = first;
 
	while (temp) {
		printf("Name: %s, surname: %s, birthyear: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
 
	return EXIT_SUCCESS;
}
 
Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
 
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Can't allocate memory!\n");
		return NULL;
	}
 
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;
 
	return newPerson;
}
 
int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;
 
	return EXIT_SUCCESS;
}
 
Position FindLast(Position head)
{
	Position temp = head;
 
	while (temp->next != NULL) {continue;}
 
	return temp;
}
 
Position FindSurname(Position first, char* surname)
{
	Position temp = first;
	while (temp) {
		if (strcmp(temp->surname, surname) == 0) {
			return temp;
		}
	}
}

Position FindBefore(Position first, Position final)
{
	Position temp = first;
	while (temp) {
		if (temp->next == final) {
			return temp;
		}
	}
    return NULL;
}

int DeleteAfter(Position head, char* surname){
    	Position temp = head;
	while (temp) {
		if (strcmp(temp->next->surname, surname) == 0) {
			temp->next = temp->next->next;
            free(temp);
            return EXIT_SUCCESS;
		}
	}
}

int CountList(Position head){

    int counter = 0;


    while(head->next){
        counter++;
        head = head->next;
    }

return counter;
}

int swap(Position head, Position one, Position two){
    Position temp1 = NULL, temp2 = NULL, temp3 = NULL, temp4 = NULL;

    temp1 = one;
    temp2 = two;
    temp3 = one->next;
    temp4 = two->next;

    FindBefore(head, one)->next = temp2;
    FindBefore(head, two)->next = temp1;
    one->next = temp4;
    two->next = temp3;

}


int SortList(Position head){
    Position pok_i = NULL, pok_j = NULL;
    

    pok_i = head;
    pok_j = head;

    do{

        pok_i = pok_i->next;
        pok_j = pok_i->next;

        do{

            if (strcmp(pok_i->surname, pok_j->surname) < 0){

                swap(head, pok_i, pok_j);
            }

            pok_j = pok_j->next; 

        }while(pok_j->next);

    }while(pok_i->next);

return EXIT_SUCCESS;

}
