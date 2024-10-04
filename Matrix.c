/*
Name - Vaishnavi Jaligama
Student Id- 1936593
Course - CSE101
Quarter - Winter 2024
Professor - Mr. Patrick Tantalo
Programming assignment - 4
due date - Feb 15, 2024
File name - Matrix.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include <limits.h> 

typedef struct EntryObj* Entry;

typedef struct EntryObj {
    int col;
    double value;
} EntryObj;


typedef struct MatrixObj {
    List* rows; 
    int size;
} MatrixObj;


Entry newEntry(int col, double value) {
    Entry E = malloc(sizeof(EntryObj));
    E->col = col;
    E->value = value;
    return E;
}


void freeEntry(Entry* pE) {
    if (pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}


Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->rows = malloc((n + 1) * sizeof(List)); 
    for (int i = 1; i <= n; i++) {
        M->rows[i] = newList();
    }
    M->size = n;
    return M;
}


void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        for (int i = 1; i <= (*pM)->size; i++) {
            List L = (*pM)->rows[i];
            moveFront(L);
            while (index(L) >= 0) {
                Entry E = (Entry)get(L);
                freeEntry(&E);
                moveNext(L);
            }
            freeList(&((*pM)->rows[i]));
        }
        free((*pM)->rows);
        free(*pM);
        *pM = NULL;
    }
}


int size(Matrix M) {
    return M->size;
}

int NNZ(Matrix M) {
    int count = 0;
    for (int i = 1; i <= M->size; i++) {
        List L = M->rows[i];
        moveFront(L);
        while (index(L) >= 0) {
            count++;
            moveNext(L);
        }
    }
    return count;
}

int equals(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        printf("Matrix comparison error: One of the matrices is NULL.\n");
        return 0;
    }
    if (A->size != B->size) return 0; 

    for (int i = 1; i <= A->size; i++) {
        List listA = A->rows[i];
        List listB = B->rows[i];
        if (length(listA) != length(listB)) return 0; 

        moveFront(listA);
        moveFront(listB);
        while (index(listA) >= 0 && index(listB) >= 0) {
            Entry entryA = (Entry)get(listA);
            Entry entryB = (Entry)get(listB);
            if (entryA->col != entryB->col || entryA->value != entryB->value) return 0; 

            moveNext(listA);
            moveNext(listB);
        }
    }
    return 1; 
}

void makeZero(Matrix M) {
    for (int i = 1; i <= M->size; i++) {
        List L = M->rows[i];
        moveFront(L);
        while (index(L) >= 0) {
            Entry E = (Entry)get(L);
            freeEntry(&E);
            moveNext(L);
        }
        clear(L);
    }
}

void changeEntry(Matrix M, int i, int j, double x) {
    if (i < 1 || i > M->size || j < 1 || j > M->size) return; 

    List L = M->rows[i];
    moveFront(L);
    while (index(L) >= 0) {
        Entry E = (Entry)get(L);
        if (E->col == j) {
            if (x == 0) {
                freeEntry(&E);
                delete(L); 
                return;
            } else {
                E->value = x; 
                return;
            }
        } else if (E->col > j) {
            if (x == 0) return; 
            break; 
        }
        moveNext(L);
    }
    if (x != 0) {
        Entry E = newEntry(j, x);
        if (index(L) == -1) append(L, E);
        else insertBefore(L, E); 
    }
}

Matrix transpose(Matrix M) {
    Matrix T = newMatrix(M->size);
    for (int i = 1; i <= M->size; i++) {
        List row = M->rows[i];
        moveFront(row);
        while (index(row) >= 0) {
            Entry e = (Entry)get(row);
            changeEntry(T, e->col, i, e->value); 
            moveNext(row);
        }
    }
    return T;
}

Matrix copy(Matrix A) {
    Matrix B = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        List row = A->rows[i];
        moveFront(row);
        while (index(row) >= 0) {
            Entry e = (Entry)get(row);
            changeEntry(B, i, e->col, e->value);
            moveNext(row);
        }
    }
    return B;
}

Matrix scalarMult(double x, Matrix A) {
    Matrix M = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List L = A->rows[i];
        moveFront(L);
        while (index(L) >= 0) {
            Entry E = (Entry)get(L);
            int col = E->col;
            double val = E->value * x;
            changeEntry(M, i, col, val);
            moveNext(L);
        }
    }
    return M;
}

//sum
Matrix sum(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        printf("Matrix sizes do not match.\n");
        exit(EXIT_FAILURE);
    }

    Matrix S = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i]; 
        
        moveFront(rowA);
        if (A == B) {
            while (index(rowA) >= 0) {
                Entry entryA = (Entry)get(rowA);
                changeEntry(S, i, entryA->col, 2 * entryA->value);
                moveNext(rowA);
            }
        } else {
            moveFront(rowB);
            while (index(rowA) >= 0 || index(rowB) >= 0) {
                Entry entryA = (index(rowA) >= 0) ? (Entry)get(rowA) : NULL;
                Entry entryB = (index(rowB) >= 0) ? (Entry)get(rowB) : NULL;
                int colA = entryA ? entryA->col : INT_MAX;
                int colB = entryB ? entryB->col : INT_MAX;

                if (entryA && (!entryB || colA < colB)) {
                    changeEntry(S, i, colA, entryA->value);
                    moveNext(rowA);
                } else if (entryB && (!entryA || colB < colA)) {
                    changeEntry(S, i, colB, entryB->value);
                    moveNext(rowB);
                } else if (entryA && entryB && colA == colB) {
                    changeEntry(S, i, colA, entryA->value + entryB->value);
                    moveNext(rowA);
                    moveNext(rowB);
                }
            }
        }
    }
    return S;
}

// diff
Matrix diff(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        printf("Matrix sizes do not match.\n");
        exit(EXIT_FAILURE);
    }

    Matrix D = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        
        moveFront(rowA);
        moveFront(rowB);
        while (index(rowA) >= 0 || index(rowB) >= 0) {
            Entry entryA = (index(rowA) >= 0) ? (Entry)get(rowA) : NULL;
            Entry entryB = (index(rowB) >= 0) ? (Entry)get(rowB) : NULL;
            int colA = entryA ? entryA->col : INT_MAX; 
            int colB = entryB ? entryB->col : INT_MAX;

            if (entryA && entryB && colA == colB) {
                double difference = entryA->value - entryB->value;
                if (difference != 0) {
                    changeEntry(D, i, colA, difference);
                }
                moveNext(rowA);
                moveNext(rowB);
            }
            else if (entryA && colA < colB) {
                changeEntry(D, i, colA, entryA->value);
                moveNext(rowA);
            }
            else if (entryB && colB < colA) {
                changeEntry(D, i, colB, -entryB->value); 
                moveNext(rowB);
            }
        }
    }
    return D;
}

// product
double vectorDot(List P, List Q) {
    double dotProduct = 0.0;
    moveFront(P);
    moveFront(Q);

    while (index(P) >= 0 && index(Q) >= 0) {
        Entry E_P = (Entry)get(P);
        Entry E_Q = (Entry)get(Q);

        if (E_P->col < E_Q->col) {
            moveNext(P);
        } else if (E_P->col > E_Q->col) {
            moveNext(Q);
        } else { 
            dotProduct += E_P->value * E_Q->value;
            moveNext(P);
            moveNext(Q);
        }
    }
    return dotProduct;
}

Matrix product(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        printf("Matrix sizes do not match. Unable to compute product.\n");
        exit(EXIT_FAILURE);
    }

    Matrix P = newMatrix(size(A));
    Matrix T = transpose(B); 

    for (int i = 1; i <= size(A); i++) {
        List rowA = A->rows[i];
        if (length(rowA) == 0) continue; 

        for (int j = 1; j <= size(T); j++) {
            List rowT = T->rows[j];
            if (length(rowT) == 0) continue; 

            double dot = vectorDot(rowA, rowT);
            if (dot != 0.0) { 
                changeEntry(P, i, j, dot);
            }
        }
    }

    freeMatrix(&T); 
    return P;
}

void printMatrix(FILE* out, Matrix M) {
    for (int i = 1; i <= size(M); i++) {
        List row = M->rows[i];
        if (length(row) > 0) {
            fprintf(out, "%d: ", i);
            moveFront(row);
            while (index(row) >= 0) {
                Entry E = (Entry)get(row);
                fprintf(out, "(%d, %.1f) ", E->col, E->value);
                moveNext(row);
            }
            fprintf(out, "\n");
        }
    }
}
