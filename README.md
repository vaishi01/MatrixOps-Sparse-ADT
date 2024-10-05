

# MatrixOps-Sparse-ADT
Welcome to the **MatrixOps-Sparse-ADT**, a C program designed to perform efficient matrix operations on sparse matrices. Sparse matrices, where most entries are zero, can benefit from optimized data structures and algorithms to save both time and memory. This calculator leverages an array-of-lists structure to store only the non-zero elements, resulting in space-efficient storage and faster computations on large matrices.

## Features

- **Efficient Matrix Storage**: Uses a 1D array of lists to store only the non-zero elements of each row.
- **Matrix Operations**: Supports a variety of matrix operations, including:
  - **Addition**
  - **Subtraction**
  - **Scalar Multiplication**
  - **Matrix Transposition**
  - **Matrix Multiplication**
- **Space Efficiency**: Saves significant memory by representing only non-zero elements.
- **Time Optimization**: Reduces computational overhead by skipping operations on zero elements, ideal for large sparse matrices.

## Program Workflow

The program reads two sparse matrices from an input file, processes them, and outputs the result of various matrix operations. It follows these steps:

1. **Input Parsing**: Reads two matrices from a file, including the non-zero entries of each matrix.
2. **Matrix Representation**: Stores each matrix in an array of lists, where each list holds only the non-zero elements and their respective column positions.
3. **Matrix Operations**: Performs several matrix operations:
   - **Matrix Addition (A + B)**
   - **Matrix Subtraction (A - B)**
   - **Scalar Multiplication (x * A)**
   - **Matrix Transposition (A^T)**
   - **Matrix Multiplication (A * B)**
4. **Output Generation**: Writes the results of these operations to an output file in a clean, sorted format.

## Data Structures

The program uses the following key data structures:

- **List ADT**: A modified list implementation that stores generic pointers (`void*`), enabling it to store matrix entries in the form of `(column, value)` pairs.
- **Matrix ADT**: Represents the matrix as an array of lists. Each list corresponds to a row in the matrix, and only non-zero elements are stored with their column index.

## Input Format

The input file consists of two matrices, specified in a sparse matrix format:

- The first line contains three integers: `n` (the matrix size), `a` (number of non-zero entries in matrix A), and `b` (number of non-zero entries in matrix B).
- The next `a` lines represent the non-zero entries of matrix A, each containing three values: `row`, `column`, and `value`.
- After a blank line, the following `b` lines represent the non-zero entries of matrix B in the same format as matrix A.

**Example Input:**
```
3 9 5
1 1 1.0
1 2 2.0
1 3 3.0
2 1 4.0
2 2 5.0
2 3 6.0
3 1 7.0
3 2 8.0
3 3 9.0

1 1 1.0
1 3 1.0
3 1 1.0
3 2 1.0
3 3 1.0
```

## Output Format

The output file displays the matrices and their operations in the following format:

1. **Matrix A and B**: The non-zero entries of matrix A and B, listed row-wise.
2. **Matrix Operations**:
   - Scalar multiplication result: `(x) * A`
   - Addition result: `A + B`
   - Subtraction result: `B - A`
   - Transposed matrix: `Transpose(A)`
   - Matrix multiplication result: `A * B` and `B * B`

**Example Output:**
```
A has 9 non-zero entries:
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

B has 5 non-zero entries:
1: (1, 1.0) (3, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

(1.5)*A =
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

A+B =
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

A*A =
1: (1, 4.0) (2, 3.0) (3, 4.0)
2: (1, 10.0) (2, 6.0) (3, 10.0)
3: (1, 16.0) (2, 9.0) (3, 16.0)
```

## How to Build and Run

1. **Clone the repository**:
   ```bash
   git clone git@github.com:vaishi01/MatrixOps-Sparse-ADT.git
   cd MatrixOps-Sparse-ADT
   ```

2. **Build the project** using the provided `Makefile`:
   ```bash
   make
   ```

3. **Run the program**:
   ```bash
   ./Sparse <input-file> <output-file>
   ```

4. **Clean up**:
   ```bash
   make clean
   ```

## Example

Here’s how to run the program with an example input file:

```bash
./Sparse input.txt output.txt
```

The program will read `input.txt`, process the matrices, and output the results to `output.txt`.

## Testing

The repository includes basic testing files for both the List ADT and Matrix ADT:

- **ListTest.c**: Tests all public List operations to ensure correctness.
- **MatrixTest.c**: Tests all Matrix operations, including addition, subtraction, scalar multiplication, and matrix multiplication.

Run the tests using:

```bash
gcc -o ListTest ListTest.c List.c
./ListTest

gcc -o MatrixTest MatrixTest.c Matrix.c List.c
./MatrixTest
```


## License

This project is licensed under the MIT License.
