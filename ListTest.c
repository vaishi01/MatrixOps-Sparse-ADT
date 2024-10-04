/*
Name - Vaishnavi Jaligama
Student Id- 1936593
Course - CSE101
Quarter - Winter 2024
Professor - Mr. Patrick Tantalo
Programming assignment - 4
due date - Feb 15, 2024
File name - ListTest.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main() {
    List A = newList();
    List B = newList();
    List C;

    // Populating lists A and B
    for (int i = 1; i <= 10; i++) {
        append(A, (void*)(long)i);
        prepend(B, (void*)(long)i);
    }

    // Testing length(), front(), back(), and get() functions
    printf("Length of A: %d\n", length(A));
    printf("First element of A: %ld\n", (long)front(A));
    printf("Last element of A: %ld\n", (long)back(A));

    moveFront(A);
    printf("Current element (after moveFront): %ld\n", (long)get(A));

    // Testing set()
    set(A, (void*)(long)100);
    moveFront(A);
    printf("Element after set to 100: %ld\n", (long)get(A));

    // Testing moveNext(), movePrev()
    moveNext(A);
    printf("Next element: %ld\n", (long)get(A));
    movePrev(A);
    printf("Previous element (should be 100 again): %ld\n", (long)get(A));

    // Testing deleteFront(), deleteBack(), and delete()
    deleteFront(A);
    deleteBack(A);
    moveFront(A);
    moveNext(A); // Move to second element
    delete(A);
    printf("Length after deletions: %d (should be 7)\n", length(A));

    // Testing clear()
    clear(A);
    printf("Length after clear: %d (should be 0)\n", length(A));

    // Testing copyList()
    C = copyList(B);
    printf("Length of copy of B (C): %d\n", length(C));

    // Testing concatList()
    List D = concatList(B, C);
    printf("Length of B concatenated with C: %d (should be 20)\n", length(D));

    // Freeing lists
    freeList(&A);
    freeList(&B);
    freeList(&C);
    freeList(&D);

    return 0;
}

/*
Expected output -
Length of A: 10
First element of A: 1
Last element of A: 10
Current element (after moveFront): 1
Element after set to 100: 100
Next element: 2
Previous element (should be 100 again): 100
Length after deletions: 7 (should be 7)
Length after clear: 0 (should be 0)
Length of copy of B (C): 10
Length of B concatenated with C: 20 (should be 20)
*/