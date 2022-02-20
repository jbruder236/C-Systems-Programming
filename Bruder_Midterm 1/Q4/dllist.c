#include "dllist.h"
#include <stdio.h>


void initList(DLList* list)
{
    list->head = NULL;
    list->tail = NULL;
}

void clearList(DLList* list)
{
    DLNode* node = list->head;
    while(node != NULL){
        DLNode* next = node->next;
        free(node);
        node = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

void insertFrontList(DLList* list,int v)
{
    DLNode* node = (DLNode*)malloc(sizeof(DLNode));
    node->value = v;
    
    if(list->head == NULL || list->tail == NULL){
        list->head = node;
        list->tail = node;
        node->next = NULL;
        node->prv = NULL;
        return;
    }
    
    node->next = list->head;
    node->prv = NULL;
    
    list->head->prv = node;
    list->head = node;
}

void insertBackList(DLList* list,int v)
{
    DLNode* node = (DLNode*)malloc(sizeof(DLNode));
    node->value = v;
    
    if(list->head == NULL){
        list->head = node;
        list->tail = node;
        node->next = NULL;
        node->prv = NULL;
        return;
    }
    
    node->prv = list->tail;
    node->next = NULL;
    
    list->tail->next = node;
    list->tail = node;
}

void insertInListBehind(DLList* list,int key,int v)
{
    DLNode* newNode = (DLNode*)malloc(sizeof(DLNode));
    newNode->value = v;
    
    if(list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
        return;
    }
    //make condition for if head is tail
    //if(node->next == list->tail){
    DLNode* node = list->head;
    
    while(node){
        if(node == list->tail){
            node->next = newNode;
            newNode->prv = node;
            list->tail = newNode;
            newNode->next = NULL;
            return;
        }
        if(node->value == key){
            if(node == list->head){
                newNode->prv = node;
                newNode->next = node->next;
                node->next->prv = newNode;
                node->next = newNode;
                return;
            }
            else{
                newNode->prv = node;
                newNode->next = node->next;
                node->next->prv = newNode;
                node->next = newNode;
                return;
            }
        }
        DLNode* next = node->next;
        node = next;
    }
}

void removeFromList(DLList* list,int key)
{
    if(list->head == NULL || list->tail == NULL){
        return;
    }
    
    DLNode* node = list->head;
    while(node){
        if(node == list->head && node->value == key){
           list->head = node->next;
           node->next->prv = NULL;
           free(node);
           return; 
        }
        else if(node == list->tail && node->value == key){
            list->tail = node->prv;
            node->prv->next = NULL;
            free(node);
            return;
        }
        else if(node->value == key){
            node->prv->next = node->next;
            node->next->prv = node->prv;
            free(node);
            return;
        }

        DLNode* next = node->next;
        node = next;
    }
    
}

void printListForward(DLList* list)
{
    if(list->head == NULL){
        printf("\n");
        return;
    }
    DLNode* node = list->head;
    while(node){
        printf("%i ", node->value);
        DLNode* next = node->next;
        node = next;
    }
    printf("\n");
}

void printListBackward(DLList* list)
{
    if(list->tail == NULL){
        printf("\n");
        return;
    }
    DLNode* node = list->tail;
    while(node){
        printf("%i ", node->value);
        DLNode* prev = node->prv;
        node = prev;
    }
    printf("\n");
}
