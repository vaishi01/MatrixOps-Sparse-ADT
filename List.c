/*
 Name - Vaishnavi Jaligama
 Student Id- 1936593
 Course - CSE101
 Quarter - Winter 2024
 Professor - Mr. Patrick Tantalo
 Programming assignment - 4
 Cruz id - vjaligam
 due date - Feb15, 2024
 File name - List.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj {
    void* data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int cursorIndex;
} ListObj;

// Helper functions
Node newNode(void* data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return N;
}
void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}
// Constructors-Destructors
List newList() {
    List L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->cursorIndex = -1;
    return L;
}

void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        while ((*pL)->length > 0) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}
// Access functions
int length(List L) {
    if (L == NULL) {
        printf("Error: calling length()\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}
int index(List L) {
    if (L == NULL) {
        printf("Error: calling index()\n");
        exit(EXIT_FAILURE);
    }
    return L->cursorIndex;
}

void* front(List L) {
    if (L == NULL || L->length == 0) {
        printf("Error: calling front()\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

void* back(List L) {
    if (L == NULL || L->length == 0) {
        printf("Error: calling back()\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

void* get(List L) {
    if (L == NULL || L->cursor == NULL || L->cursorIndex < 0) {
        printf("Error: calling get()\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}


// Manipulation procedures
void clear(List L) {
    while (L->length > 0) deleteFront(L);
    L->cursor = NULL;
    L->cursorIndex = -1;
}

void set(List L, void* x) {
    if (L == NULL || L->cursor == NULL || L->cursorIndex < 0) {
        printf("Error: calling set()\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

void moveFront(List L) {
    if (L != NULL && L->length > 0) {
        L->cursor = L->front;
        L->cursorIndex = 0;
    }
}

void moveBack(List L) {
    if (L != NULL && L->length > 0) {
        L->cursor = L->back;
        L->cursorIndex = L->length - 1;
    }
}

void movePrev(List L) {
    if (L == NULL) {
        printf("Error: calling movePrev()\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL && L->cursor != L->front) {
        L->cursor = L->cursor->prev;
        L->cursorIndex -= 1;
    } else {
        L->cursorIndex = -1;
        L->cursor = NULL;
    }
}
void moveNext(List L) {
    if (L == NULL) {
        printf("Error: calling moveNext()\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL && L->cursor != L->back) {
        L->cursor = L->cursor->next;
        L->cursorIndex += 1;
    } else {
        L->cursorIndex = -1;
        L->cursor = NULL;
    }
}


void prepend(List L, void* x) {
    if (L == NULL) {
        printf("Error: calling prepend()\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->length == 0) { 
        L->front = L->back = N; 
    } else {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
    }
    if (L->cursorIndex != -1) L->cursorIndex++;
    L->length++;
}

void append(List L, void* x) {
    if (L == NULL) {
        printf("Error: calling append()\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->length == 0) { 
        L->front = L->back = N; 
    } else {
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
    L->length++;
}

void insertBefore(List L, void* x) {
    if (L == NULL || L->cursor == NULL || L->cursorIndex < 0) {
        printf("Error: calling insertBefore()\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursorIndex == 0) {
        prepend(L, x);
    } else {
        Node N = newNode(x);
        N->prev = L->cursor->prev;
        N->next = L->cursor;
        L->cursor->prev->next = N;
        L->cursor->prev = N;
        L->length++;
        L->cursorIndex++;
    }
}

void insertAfter(List L, void* x) {
    if (L == NULL || L->cursor == NULL || L->cursorIndex < 0) {
        printf("Error: calling insertAfter()\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursorIndex == L->length - 1) {
        append(L, x);
    } else {
        Node N = newNode(x);
        N->next = L->cursor->next;
        N->prev = L->cursor;
        L->cursor->next->prev = N;
        L->cursor->next = N;
        L->length++;
    }
}

void deleteFront(List L) {
    if (L == NULL || L->length == 0) {
        printf("Error: calling deleteFront()\n");
        exit(EXIT_FAILURE);
    }
    Node N = L->front;
    if (L->length > 1) {
        L->front = L->front->next;
        L->front->prev = NULL;
    } else {
        L->front = L->back = NULL;
    }
    if (L->cursorIndex == 0) {
        L->cursor = NULL;
        L->cursorIndex = -1;
    } else if (L->cursorIndex != -1) {
        L->cursorIndex--;
    }
    L->length--;
    freeNode(&N);
}

void deleteBack(List L) {
    if (L == NULL || L->length == 0) {
        printf("Error: calling deleteBack()\n");
        exit(EXIT_FAILURE);
    }
    Node N = L->back;
    if (L->length > 1) {
        L->back = L->back->prev;
        L->back->next = NULL;
    } else {
        L->front = L->back = NULL;
    }
    if (L->cursorIndex == L->length - 1) {
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
    L->length--;
    freeNode(&N);
}

void delete(List L) {
    if (L == NULL || L->cursor == NULL || L->cursorIndex < 0) {
        printf("Error: calling delete()\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == L->front) {
        deleteFront(L);
    } else if (L->cursor == L->back) {
        deleteBack(L);
    } else {
        Node N = L->cursor;
        N->prev->next = N->next;
        N->next->prev = N->prev;
        L->length--;
        freeNode(&N);
    }
    L->cursor = NULL;
    L->cursorIndex = -1;
}
// Other operations


List copyList(List L) {
    List newL = newList();
    Node N = NULL;

    if (L == NULL) {
        printf("Error: calling copyList()\n");
        exit(EXIT_FAILURE);
    }

    for (N = L->front; N != NULL; N = N->next) {
        append(newL, N->data);
    }

    return newL;
}

List concatList(List A, List B) {
    List newL = copyList(A);
    Node N = NULL;

    if (A == NULL || B == NULL) {
        printf("Error: calling concatList()\n");
        exit(EXIT_FAILURE);
    }

    for (N = B->front; N != NULL; N = N->next) {
        append(newL, N->data);
    }

    return newL;
}



