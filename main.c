#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct studentsMarks{
    char group[35];
    char surname[35];
    char name[35];
    int mark1, mark2, mark3;
}studMarks;

typedef struct listElement{
    studMarks data;
    struct listElement *next, *prev;
} listElement;

void readListFromFile(listElement**, const char*);
void addInTail(listElement**,struct studentsMarks);
void printList(listElement*);
int averageSum(studMarks);
void sortList(struct listElement*);
void removeFromHead(listElement**);
void freeList(listElement**);
void deleteBySurname(struct listElement**, char []);
void writeListIntoFile(listElement* infData, const char *fileName);
void writeListIntoFileOrderByGroupAndSurname(listElement*);
void printListBadStudents(struct listElement*);
void sortByGroupAndSurname(struct listElement*);


int main() {

    listElement * infData = NULL;
    char fileName[255];

    printf("File name > ");
    scanf("%s", fileName);

    readListFromFile(&infData, fileName);
    printList(infData);

    int menu = -1;

    while(menu != 0){
        fflush(stdin); //system("cls");
        printList(infData);

        printf("\nMenu:\n\n");
        printf("1. Add new student & marks\n");
        printf("2. Remove student\n");
        printf("3. Sort students by marks\n");
        printf("4. Remember list of marks in new file\n");
        printf("5. Sort list order by group and surname\n");
        printf("6. Write list into file ordered by group and surname\n");
        printf("7. Print bad student\n");
        printf("0. Exit\n\n Choose action number:> ");

        scanf("%d",&menu);

        if(menu == 1){
            studMarks marks;
            printf("\n\nAdding new student and marks:\n\n");

            printf("Group > ");
            scanf("%s",marks.group);

            printf("Surname > ");
            scanf("%s",marks.surname);

            printf("Name > ");
            scanf("%s",marks.name);

            printf("mark 1 > ");
            scanf("%d",&marks.mark1);

            printf("mark 2 > ");
            scanf("%d",&marks.mark2);

            printf("mark 3 > ");
            scanf("%d",&marks.mark3);

            addInTail(&infData, marks);

        } else if(menu == 2) {
            char temp[35];
            temp[35]='\0';
            //temp[] = (char)malloc(sizeof(char)*20);
            studMarks marks;
            printf("Print surname of a student:");
            scanf("%s", temp);
            deleteBySurname(&infData, temp);

        } else if(menu == 3) {
            sortList(infData);

        } else if(menu == 4) {
            printf("File name > ");
            scanf("%s", fileName);
            writeListIntoFile(infData,fileName);

        } else if(menu == 5) {
            sortByGroupAndSurname(infData);

        } else if(menu == 6) {
            writeListIntoFileOrderByGroupAndSurname(infData);

        } else if(menu == 7) {
            printListBadStudents(infData);
            system("pause");

        } else if(menu == 0) {
            freeList(&infData);
        }
    }
    return 0;
}

void readListFromFile(listElement** infData, const char *fileName) {

    //char i = 0;
    FILE* file = fopen(fileName,"r");
    if(!file)
        return;
    while(!feof(file)) {
        struct studentsMarks studentsMark;

        fscanf(file,"%s %s %s %d %d %d", (studentsMark.group), (studentsMark.surname),
               (studentsMark.name), &(studentsMark.mark1), &(studentsMark.mark2), &(studentsMark.mark3));

        if(!feof(file))
            addInTail(infData, studentsMark);
    }
    fclose(file);
}

void addInTail(listElement ** head, struct studentsMarks data) {
    if(head != NULL){
        if(*head == NULL){
            *head = (listElement*)malloc(sizeof(listElement));
            (*head)->data = data;
            (*head)->next = NULL;
            (*head)->prev = NULL;
        }else{
            listElement* current = *head;
            while(current->next != NULL){
                current = current->next;
            }
            current->next = (listElement*)malloc(sizeof(listElement));
            current->next->prev = current;
            current = current->next;
            current->next = NULL;
            current->data = data;
        }
    }
}

void printList(struct listElement* head){
    printf("Marks list:\n\n");
    printf("X-------------------------------------------------------------------------X\n");
    printf("| Group      | Surname       | Name         | Mark 1  | Mark 2  | Mark 3  |\n");
    printf("X-------------------------------------------------------------------------X\n");

    int i = 0;
    for(listElement * current = head;current!=NULL;current = current->next){
        printf("| %-10s | %-14s| %-13s| %-8d| %-8d| %-8d|\n",current->data.group,current->data.surname, current->data.name,
               current->data.mark1, current->data.mark2, current->data.mark3);
        printf(" -------------------------------------------------------------------------\n");
    }
    printf("\n");
}



int averageSum(studMarks marks){
    int average = 0;
     average= (marks.mark1 + marks.mark2 + marks.mark3)/3;
     return average;
}

void printListBadStudents(struct listElement* head)
{
    printf("Bad students list:\n\n");
    printf("X-------------------------------------------------------------------------X\n");
    printf("| Group      | Surname       | Name         | Mark 1  | Mark 2  | Mark 3  |\n");
    printf("X-------------------------------------------------------------------------X\n");

    int i = 0;
    for(listElement * current = head;current!=NULL;current = current->next){
        if(averageSum(current->data) < 60)
        {
            printf("| %-10s | %-14s| %-13s| %-8d| %-8d| %-8d|\n",current->data.group,current->data.surname, current->data.name,
                   current->data.mark1, current->data.mark2, current->data.mark3);

            printf(" -------------------------------------------------------------------------\n");
        }
    }
    printf("\n");
}


void sortList(struct listElement* head){
    for(listElement * current = head; current!=NULL;current = current->next){
        for(listElement * scurrent = current->next;scurrent!=NULL;scurrent = scurrent->next){
            if(averageSum(current->data) < averageSum(scurrent->data)) {
                studMarks buffer = current->data;
                current->data = scurrent->data;
                scurrent->data = buffer;
            }
        }
    }
}


void removeFromHead(listElement ** head){
    if(head != NULL){
        if(*head != NULL){
            listElement * current = *head;
            *head = (*head)->next;
            free(current);
            if(*head != NULL){
                (*head)->prev = NULL;
            }
        }
    }
}

void freeList(listElement ** head){
    if(head != NULL){
        while(*head != NULL){
            removeFromHead(head);
        }
    }
}

void deleteBySurname(struct listElement** head, char temp[]) {
    if(head != NULL && *head != NULL) {

        listElement* current = *head;

        while(current != NULL && strcmp(current->data.surname,temp) != 0) {
            current = current->next;
        }
        if(current != NULL) {
            if(current == *head) {
                *head = (*head)->next;
                (*head)->prev = NULL;
                free(current);
            } else {
                current->prev->next = current->next;
                if(current->next != NULL)
                    current->next->prev = current->prev;
                free(current);
            }
        }
    }
}

void sortByGroupAndSurname(struct listElement* head) {

    for(listElement * current = head; current!=NULL;current = current->next) {

        for(listElement * scurrent = current->next;scurrent!=NULL;scurrent = scurrent->next) {

            if(strcmp(current->data.group, scurrent->data.group) > 0 ||
               strcmp(current->data.group, scurrent->data.group) == 0 &&
               strcmp(current->data.surname, scurrent->data.surname) > 0) {

                studMarks buffer = current->data;
                current->data = scurrent->data;
                scurrent->data = buffer;
            }
        }
    }
}

void writeListIntoFile(listElement* infData, const char *fileName) {

    FILE* file = fopen(fileName,"w");

    if(!file)
        return;

    listElement* current = infData;

    while(current != NULL) {
        fprintf(file,"%s %s %s %d %d %d\n",current->data.group,current->data.surname,current->data.name,
                current->data.mark1,current->data.mark2,current->data.mark3);
        current = current->next;
    }
    fclose(file);
}

void writeListIntoFileOrderByGroupAndSurname(listElement* infData) {
    //copy list (if list non-sorted)
    listElement* bufferList = NULL;
    listElement* current = infData;

    while(current != NULL) {
        addInTail(&bufferList, current->data);
        current = current->next;
    }
    //sorting order group
    sortByGroupAndSurname(bufferList);
    //writing in files
    current = bufferList;
    while(current != NULL) {
        char fileName[255];
        fileName[0] = '\0';

        strcat(fileName, current->data.group);
        strcat(fileName, ".txt");

        FILE* file = fopen(fileName ,"w");

        do {
            fprintf(file,"%s %s %d %d %d\n",current->data.surname,current->data.name,
                    current->data.mark1,current->data.mark2,current->data.mark3);

            current = current->next;
        } while(current != NULL && strcmp(current->data.group,current->prev->data.group) == 0);
        fclose(file);
    }
    freeList(&bufferList);
}




// C:\Users\ThinkPad\CLionProjects\progDoubleList\file.txt
