/*
 Name - Vaishnavi Jaligama
 Student Id- 1936593
 Course - CSE101
 Quarter - Winter 2024
 Professor - Mr. Patrick Tantalo
 Programming assignment - 4
 Cruz id - vjaligam
 due date - Feb15, 2024
 File name - MatrixTest.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

void testChangeEntryAndPrint(Matrix M) {
    printf("Testing changeEntry() and printMatrix()...\n");
    changeEntry(M, 1, 1, 1.0);
    changeEntry(M, 1, 2, 2.0);
    changeEntry(M, 2, 1, 3.0);
    changeEntry(M, 3, 3, 4.0);
    printMatrix(stdout, M);
    printf("NNZ: %d\n\n", NNZ(M));
}

void testArithmeticOperations(Matrix A, Matrix B) {
    printf("Testing Scalar Multiplication, Sum, Difference, and Product...\n");
    Matrix scalar = scalarMult(2.0, A);
    printMatrix(stdout, scalar);
    printf("NNZ: %d\n\n", NNZ(scalar));

    Matrix sumMat = sum(A, B);
    printMatrix(stdout, sumMat);
    printf("NNZ: %d\n\n", NNZ(sumMat));

    Matrix diffMat = diff(A, B);
    printMatrix(stdout, diffMat);
    printf("NNZ: %d\n\n", NNZ(diffMat));

    Matrix prodMat = product(A, B);
    printMatrix(stdout, prodMat);
    printf("NNZ: %d\n\n", NNZ(prodMat));

    freeMatrix(&scalar);
    freeMatrix(&sumMat);
    freeMatrix(&diffMat);
    freeMatrix(&prodMat);
}

void testTransposeAndCopy(Matrix A) {
    printf("Testing Transpose and Copy...\n");
    Matrix T = transpose(A);
    printMatrix(stdout, T);
    printf("NNZ: %d\n\n", NNZ(T));

    Matrix C = copy(A);
    printMatrix(stdout, C);
    printf("NNZ: %d\n", NNZ(C));

    printf("Equals A and C: %s\n\n", equals(A, C) ? "true" : "false");

    freeMatrix(&T);
    freeMatrix(&C);
}

void testMakeZero(Matrix M) {
    printf("Testing makeZero()...\n");
    makeZero(M);
    printMatrix(stdout, M);
    printf("NNZ: %d\n", NNZ(M));
}

int main() {
    Matrix A = newMatrix(3);
    Matrix B = newMatrix(3);

    testChangeEntryAndPrint(A);
    testChangeEntryAndPrint(B);

    testArithmeticOperations(A, B);
    testTransposeAndCopy(A);
    testMakeZero(A);

    freeMatrix(&A);
    freeMatrix(&B);

    return EXIT_SUCCESS;
}

/*
Expected Output -
Testing changeEntry() and printMatrix()...
1: (1, 1.0) (2, 2.0) 
2: (1, 3.0) 
3: (3, 4.0) 
NNZ: 4

Testing changeEntry() and printMatrix()...
1: (1, 1.0) (2, 2.0) 
2: (1, 3.0) 
3: (3, 4.0) 
NNZ: 4

Testing Scalar Multiplication, Sum, Difference, and Product...
1: (1, 2.0) (2, 4.0) 
2: (1, 6.0) 
3: (3, 8.0) 
NNZ: 4

1: (1, 2.0) (2, 4.0) 
2: (1, 6.0) 
3: (3, 8.0) 
NNZ: 4

NNZ: 0

1: (1, 7.0) (2, 2.0) 
2: (1, 3.0) (2, 6.0) 
3: (3, 16.0) 
NNZ: 5

Testing Transpose and Copy...
1: (1, 1.0) (2, 3.0) 
2: (1, 2.0) 
3: (3, 4.0) 
NNZ: 4

1: (1, 1.0) (2, 2.0) 
2: (1, 3.0) 
3: (3, 4.0) 
NNZ: 4
Equals A and C: true

Testing makeZero()...
NNZ: 0
*/
