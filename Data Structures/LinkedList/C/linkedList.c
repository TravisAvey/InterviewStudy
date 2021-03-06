#include "linkedList.h"

// This method returns the length of the list
// by traversing the list
int length(struct Node *head) {
    // create a current node to traverse
    struct Node *current = head;
    // declare a counter
    int count;
    count = 0;
    // loop through list as long as current
    // is not NULL (which would be the end)
    while (current != NULL) {
        // increment the counter
        count++;
        // set current to the next
        current = current->next;
    }
    // return the count
    return count;
}

// This method loops through the list
// and prints out each datum at each node
void printList(struct Node *head) {
    // get the first node
    struct Node *current = head;
    // if the head is pointing to NULL
    if (head == NULL) {
        // output info and return
        printf("Linked List is empty\n");
        return;
    }
    // init a counter
    int node = 0;
    // while the current is not null
    while (current != NULL) {
        // output the current node and it's data
        printf("Node %i : %i\n", node, current->data);
        // move to next node
        current = current->next;
        // increment counter
        node++;
    }
}

// This method adds a new node to the first
// position.  Points head to this new node
// and points this new node's next to head's next
void pushFront(struct Node **head, int data) {
    // init a new node, and a pointer
    struct Node *newNode, *current;
    newNode = (struct Node *)malloc(sizeof(struct Node));
    // if new node is null
    if (!newNode) {
        // output error, memory
        error("pushFront");
        // return from method
        return;
    }
    // set the data on the new node
    newNode->data = data;
    // set the current node to head
    current = *head;
    // set new node's next to current (what head is pointing to)
    newNode->next = current;
    // point head to the new node
    *head = newNode;
} 

void pushBack(struct Node **head, int data) {

    // init new node and init pointers
    struct Node *newNode, *current, *prev;
    newNode = (struct Node *) malloc(sizeof(struct Node));

    // if new node is null, memory error and return
    if (!newNode) {
        error("pushBack");
        return;
    }

    // set p to head
    current = *head;
    // if the head is pointing at null
    // empty list, so call pushFron
    if (current == NULL) {
        pushFront(head, data);
        return;
    }
    // set the new node's data
    newNode->data = data;

    // traverse the list
    while (current != NULL) {
        // save current node
        prev = current;
        // set p to next
        current = current->next;
    }
    // set the prev node's next to the new node
    prev->next = newNode;
    // set the new node's next to current (should be null for tail)
    newNode->next = current;
}

// This method will insert a new node at the location
// specified as param loc, 0 based
void insertAt(struct Node **head, int loc, int data) {

    // initialize new node, declare pointers
    struct Node *newNode, *current, *prev;
    newNode = (struct Node *) malloc(sizeof(struct Node));

    // if new node is null, memory error
    if (!newNode) {
        // call helper method for debugging memory issues
        error("insertAt");
        // return from this method
        return;
    }

    // set the current to the head
    current = *head;

    // if user set loc as 0 or current (head) is null
    if (loc == 0 || current != NULL) {
        // add the node to the front
        pushFront(head, data);
        return;
    }

    // set the new node's data
    newNode->data = data;
    // init a pos counter
    int pos = 0;

    // while current is not null, and the pos is 
    // less than the location
    while (current != NULL && pos < loc) {
        // increment position
        pos++;
        // set the prev
        prev = current;
        // set current to next
        current = current->next;
    }
    // if the location is greater than how many nodes
    // this linked list has, this above while loop
    // will fall of, because checking current to be not null
    // if current is null, we are at the end of the list
    // and below it will properly set the node at the end

    // finally set the prev's next to the new node
    prev->next = newNode;
    // set the new node's next to the current
    newNode->next = current;
}

// This method removes the first node in
// the list, and returns the value
int popFront(struct Node **head) {
    // if head is pointing to nothing
    if ((*head) == NULL) {
        // output that list is empty
        printf("List is empty\n");
        // return a flag that list is empty
        return -1;
    } 
    // get the data from the head (dereference pointer to pointer)
    int data = (*head)->data;
    // set head to to the next, effectively next node is not accessable
    *head = (*head)->next;
    // return the data
    return data;
}
// This method removes the last node
// in the list, and returns that datum
int popBack(struct Node **head) {
    // if the head is pointing to null
    if ((*head) == NULL) {
        // output that list is empty
        printf("List is empty\n");
        // return a flag
        return -1;
    }
    // declare pointers for traversal
    struct Node *prev, *current;
    // set the current pointer to head
    current = *head;
    // declare var to hold the datum
    int data;
    // while the next is not null
    while (current->next != NULL) {
        // hold prev node
        prev = current;
        // set current to next
        current = current->next;
        // get the datum from last node
        data = current->data;
    }
    // set the previous node's next to NULL
    prev->next = NULL;
    // free up the memory of the current (which was last)
    free(current);
    // return the data
    return data;
}

// This method removes a specific node of the key specified
void removeNode(struct Node **head, int key) {
    // init an int(bool) if found
    short found = 0;
    // declare pointers for the previous and current
    struct Node *prev, *current;
    // set the current to the head
    current = *head;

    // while the next node is not the end
    while (current->next != NULL) {
        // if the current is the key
        if (current->data == key) {
            // set flag that found
            found = 1;
            // break from loop
            break;
        }
        // save current to prev
        prev = current;
        // advance to next node
        current = current->next;
    }
    // if key not in list
    if (!found) {
        // output error message
        printf("Node with data of %i is not in the list\n", key);
        // return from method
        return;
    }
    // set the next node, skipping node to delete
    prev->next = current->next;
    // free the memory of current
    free(current);
}

// This method deletes the entire linked list
void deleteList(struct Node **head) {
    // declare pointers to traverse list
    struct Node *iter, *aux;
    // set the iterator to the head
    iter = *head;
    // while the iterator is not pointing to NULL
    while (iter != NULL) {
        // set the auxillary node to the iter's next
        aux = iter->next;
        // free the iterator from memory
        free (iter);
        // set the auxillary to the iterator
        iter = aux;
    }
    // finally set the head to NULL
    *head = NULL;
}

// This method reverses the linked list
void reverse(struct Node **head) {
    // declare pointers for traversal/reversal
    struct Node *prev, *current, *next;
    // point current node to the head
    current = *head;
    // while current node is not null
    while (current) {
        // point the next to current's next
        next = current->next;
        // set the current next as prev (first time will be null)
        current->next = prev;
        // point prev to current
        prev = current;
        // point current to next
        current = next;
    }
    // finally point the head to previous
    *head = prev;
}

// helper method that prints out error memory
// param: string of method for debugging purposes
void error(char *method) {
    fprintf(stderr, "%s. Memory error: cannot initlize new node\n", method);
}
