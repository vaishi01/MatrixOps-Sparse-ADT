/*
Name - Vaishnavi Jaligama
Student Id- 1936593
Course - CSE101
Quarter - Winter 2024
Professor - Mr. Patrick Tantalo
Programming assignment - 4
due date - Feb 15, 2024
File name - Sparse.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(int argc, char* argv[]) {
    FILE *in, *out;
    int n, a, b;

    
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

   
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        return EXIT_FAILURE;
    }
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        fclose(in); 
        return EXIT_FAILURE;
    }

    
    fscanf(in, "%d %d %d", &n, &a, &b);

    // Initialize 
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
 
    for (int i = 0; i < a; i++) {
        int row, col;
        double value;
        fscanf(in, "%d %d %lf", &row, &col, &value);
        changeEntry(A, row, col, value);
    }
    fscanf(in, "\n");

    
    for (int i = 0; i < b; i++) {
        int row, col;
        double value;
        fscanf(in, "%d %d %lf", &row, &col, &value);
        changeEntry(B, row, col, value);
    }

    //Print
    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");


// Scalar multiplication 
Matrix scalarA = scalarMult(1.5, A);
fprintf(out, "(1.5)*A =\n");
printMatrix(out, scalarA);
fprintf(out, "\n");

// Sum 
Matrix sumAB = sum(A, B);
fprintf(out, "A+B =\n");
printMatrix(out, sumAB);
fprintf(out, "\n");

Matrix sumAA = sum(A, A);
fprintf(out, "A+A =\n");
printMatrix(out, sumAA);
fprintf(out, "\n");

// Difference
Matrix diffBA = diff(B, A);
fprintf(out, "B-A =\n");
printMatrix(out, diffBA);
fprintf(out, "\n");

Matrix diffAA = diff(A, A);
fprintf(out, "A-A =\n");
printMatrix(out, diffAA);
fprintf(out, "\n");

// Transpose 
Matrix transposeA = transpose(A);
fprintf(out, "Transpose(A) =\n");
printMatrix(out, transposeA);
fprintf(out, "\n");

// Product 
Matrix productAB = product(A, B);
fprintf(out, "A*B =\n");
printMatrix(out, productAB);
fprintf(out, "\n");

Matrix productBB = product(B, B);
fprintf(out, "B*B =\n");
printMatrix(out, productBB);
fprintf(out, "\n");

// Free all matrices
freeMatrix(&A);
freeMatrix(&B);
freeMatrix(&scalarA);
freeMatrix(&sumAB);
freeMatrix(&sumAA);
freeMatrix(&diffBA);
freeMatrix(&diffAA);
freeMatrix(&transposeA);
freeMatrix(&productAB);
freeMatrix(&productBB);


fclose(in);
fclose(out);

return EXIT_SUCCESS;

}  