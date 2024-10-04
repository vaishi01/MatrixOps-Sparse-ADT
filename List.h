/*
 Name - Vaishnavi Jaligama
 Student Id- 1936593
 Course - CSE101
 Quarter - Winter 2024
 Professor - Mr. Patrick Tantalo
 Programming assignment - 4
 Cruz id - vjaligam
 due date - feb 15, 2024
 File name - List.h
*/

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

#include <stdbool.h>
#include <stdio.h>

// List type
typedef struct ListObj* List;

// Constructors-Destructors
List newList(void);                 
void freeList(List* pL);  

// Access functions
int length(List L);                 
int index(List L);                   
void* front(List L);                   
void* back(List L);                    
void* get(List L);                     
     

// Manipulation procedures
void clear(List L);                  
void set(List L, void* x);             
void moveFront(List L);              
void moveBack(List L);               
void movePrev(List L);               
void moveNext(List L);               
void prepend(List L, void* x);         
void append(List L, void* x);          
void insertBefore(List L, void* x);    
void insertAfter(List L, void* x);     
void deleteFront(List L);            
void deleteBack(List L);             
void delete(List L); 

// Other operations 
List copyList(List L);               
List concatList(List A, List B);     

#endif


