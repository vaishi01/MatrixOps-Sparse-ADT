/*
Name - Vaishnavi Jaligama
Student Id- 1936593
Course - CSE101
Quarter - Winter 2024
Professor - Mr. Patrick Tantalo
Programming assignment - 4
due date - Feb 15, 2024
File name - Matrix.h
*/
#ifndef _MATRIX_H_INCLUDE_
#define _MATRIX_H_INCLUDE_

#include "List.h" 

// Exported type 
typedef struct MatrixObj* Matrix;

// Constructors-Destructors 
Matrix newMatrix(int n);
void freeMatrix(Matrix* pM);

// Access functions 
int size(Matrix M);
int NNZ(Matrix M);
int equals(Matrix A, Matrix B);

// Manipulation procedures 
void makeZero(Matrix M);
void changeEntry(Matrix M, int i, int j, double x);

// Matrix Arithmetic operations 
Matrix copy(Matrix A);
Matrix transpose(Matrix A);
Matrix scalarMult(double x, Matrix A);
Matrix sum(Matrix A, Matrix B);
Matrix diff(Matrix A, Matrix B);
Matrix product(Matrix A, Matrix B);
void printMatrix(FILE* out, Matrix M);

#endif
