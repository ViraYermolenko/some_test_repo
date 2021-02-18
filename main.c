#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct studentsMarks{
    char surname[35];
    char name[35];
    int mark1, mark2, mark3;
}studMarks;

struct studentsMarks data[20];

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
//listElement *deleteElement(listElement **head, listElement* pdel)
//void deleteBySurname(struct listElement* , char);
listElement *deleteElement(listElement**, listElement*);
void freeElementMemory(listElement*);

//listElement *listBegin, *listEnd;

int main() {

    listElement * infData = NULL;
    char fileName[255];

    printf("File name > ");
    scanf("%s", fileName);

    readListFromFile(&infData, fileName);
    printList(infData);

    int menu = -1;

    while(menu != 0){
        fflush(stdin);
        printList(infData);

        printf("\nMenu:\n\n");
        printf("1. Add new student & marks\n");
        printf("2. Remove student\n");
        printf("3. Sort students by marks\n");
        printf("4. Remember list of marks in new file\n");
        printf("0. Exit\n\n > ");

        scanf("%d",&menu);

        if(menu == 1){
            studMarks marks;
            printf("\n\nAdding new student and marks:\n\n");

            printf("Surname > ");
            scanf("%s",&marks.surname);

            printf("Name > ");
            scanf("%s",&marks.name);

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
        }
        else if(menu == 3)
        {
            sortList(infData);
        }
        else if(menu == 0)
        {
            freeList(&infData);
        }
    }


    return 0;
}

void readListFromFile(listElement** infData, const char *fileName) {

    char i = 0;
    FILE* file = fopen(fileName,"r");
    if(!file)
        return;

    int numberX, numberY, numberZ;
    while(!feof(file)) {
        fscanf(file,"%s %s %d %d %d", &(data[i].surname), &(data[i].name), &(data[i].mark1), &(data[i].mark2), &(data[i].mark3));
        if(!feof(file))
            addInTail(infData, data[i]);
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
    printf("Marks list:\n\nSurname       Name           Mark 1   Mark 2   Mark 3\n");

    int i = 0;
    for(listElement * current = head;current!=NULL;current = current->next){
        printf("%-13s %-10s %8d %8d %8d \n",current->data.surname, current->data.name,
               current->data.mark1, current->data.mark2, current->data.mark3);
    }
    printf("\n");
}


int averageSum(studMarks marks){
    int average = 0;
     average= (marks.mark1 + marks.mark2 + marks.mark3)/3;
     return average;
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
    if(head != NULL && *head != NULL)
    {
        listElement* current = *head;

        while(current != NULL && strcmp(current->data.surname,temp) != 0)
        {
            current = current->next;
        }

        if(current != NULL)
        {
            if(current == *head)
            {
                *head = (*head)->next;
                (*head)->prev = NULL;

                free(current);
            }
            else
            {
                current->prev->next = current->next;
                if(current->next != NULL)
                    current->next->prev = current->prev;

                free(current);
            }
        }
    }
}

void freeElementMemory(listElement * pel) {
    free(pel->data.surname);
    free(pel);
}
/*void deleteBySurname(struct listElement** head, char temp[]) {
    listElement * pel = head;
    printf("%s, %s\n", pel->data.surname, temp);
    while (pel != NULL)
        if(strcmp(pel->data.surname, temp)==0)
               // pel-> data.surname == temp)
            pel = deleteElement(&pel, pel);
        else
            pel = pel->next;
}




listElement *deleteElement(listElement **head, listElement * pdel) {
    if (head != NULL) {
        if (*head != NULL) {
            if (pdel == *head) {    //delete first element from list
                *head = (*head)->next;
                (*head)->prev = NULL;
                freeElementMemory(pdel);
                return head;
                //return NULL;
            }}}
            listElement  *tail;
            if (pdel == tail) {      //delete first element from list
                tail = tail->prev;
                tail->next = NULL;
                freeElementMemory(pdel);
                return NULL;
            } else {                    //delete middle element from list
                listElement *pnext;
                pdel->next->prev = pdel->prev;
                pnext = pdel->prev->next = pdel->next;
                freeElementMemory(pdel);
                return NULL;
                //return pnext;
    }
}*/





// C:\Users\ThinkPad\CLionProjects\progDoubleList\file.txt
//
//
// /*listElement * temp = head;
//    while ((temp != NULL) && (temp->data != surname[20]))
//        temp = temp->next;
//    if (temp == NULL)
//        return;
//
//    listElement * prev = temp->prev;
//    listElement * next = temp->next;
//    if (prev != NULL)
//        prev->next = next;
//    if (next != NULL)
//        next->prev = prev;
//
//    free(temp);
//}*/

/*listElement *deleteElement(listElement* pdel) {
    if (pdel == listBegin){    //delete first element from list
        listBegin = listBegin->next;
        listBegin->prev = NULL;
        freeElementMemory(pdel);
        return listBegin;
    }
    if (pdel == listEnd){      //delete first element from list
        listEnd = listEnd->prev;
        listEnd->next = NULL;
        freeElementMemory(pdel);
        return NULL;
    } else {                    //delete middle element from list
        listElement  *pnext;
        pdel->next->prev = pdel->prev;
        pnext = pdel->prev->next = pdel->next;
        freeElementMemory(pdel);
        return pnext;
    }
}*/