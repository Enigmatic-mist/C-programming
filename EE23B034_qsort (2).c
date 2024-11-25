//Name: Keerthi Vasukhi Kamaraju
//Roll number: EE23B034
//Version 1.0
//Read from a data file (argv[1]) of integers into a linked list and print out the integers using quick sort of the list
#include <stdio.h>
#include <stdlib.h>

// Define a structure for a doubly linked list node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Defining different functions used in the program
void append(struct Node** head, int new_data);
void swap(int* a, int* b);
void quickSort(struct Node* head);
struct Node* lastNode(struct Node* last);
struct Node* partition(struct Node* low, struct Node* high);
void printList(struct Node* head);

int main(int argc, char* argv[]) {

    struct Node* head = NULL;
    char* fname = argv[1];
    FILE* file = fopen(fname, "r");
    int data;

    // Read numbers from the file and insert them into the linked list
    while (fscanf(file, "%d,", &data) != EOF) {
        append(&head, data);
    }

    fclose(file);
    quickSort(head);
    printList(head);

    return 0;
}

// Function to insert a new node at the end of the linked list
void append(struct Node** head, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*head == NULL) {
        *head = new_node;
    } 
    else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        new_node->prev = current;
    }
}

// Function to swap two integers
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Function to find the last node in the linked list
struct Node* lastNode(struct Node* last) {
    while (last && last->next) {
        last = last->next;
    }
    return last;
}

// Function to partition the linked list for quicksort
struct Node* partition(struct Node* low, struct Node* high) {
    int x = high->data;
    struct Node* i = low->prev;

    for (struct Node* j = low; j != high; j = j->next) {
        if (j->data <= x) {
            i = (i == NULL) ? low : i->next;
            swap(&(i->data), &(j->data));
        }
    }

    i = (i == NULL) ? low : i->next;
    swap(&(i->data), &(high->data));
    return i;
}

// Function to perform the quicksort on the linked list
void _quickSort(struct Node* low, struct Node* high) {
    if (high != NULL && low != high && low != high->next) {
        struct Node* p = partition(low, high);
        _quickSort(low, p->prev);
        _quickSort(p->next, high);
    }
}

// Function to initiate quicksort on the linked list
void quickSort(struct Node* head) {
    struct Node* high = lastNode(head);
    _quickSort(head, high);
}

// Function to print the linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
}

