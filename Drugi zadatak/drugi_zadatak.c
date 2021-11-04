/*
U kod koji smo radili na laboratorijskim vježbama dodati zadnje dvije funkcije
i funkciju koja briše određeni element liste.
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

 
int main(int argc, char** argv) {
	
	Person Head = {"","", 0, NULL};

	return EXIT_SUCCESS;
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
	InsertAfter(last, newPerson);
 
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
 
	while (temp->next) {
 
	}
 
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
