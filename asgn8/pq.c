#include "pq.h"

#include <stdio.h>

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};

struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *new_pq = calloc(1, sizeof(PriorityQueue));
    if (new_pq == NULL) {
        return NULL;
    } else {
        new_pq->list = NULL;
        return new_pq;
    }
}

void pq_free(PriorityQueue **q) {
    if (*q != NULL) {
        ListElement *freebird = (*q)->list;
        while (freebird != NULL) {
            ListElement *nextbird = freebird->next;
            node_free(&freebird->tree);
            free(freebird);
            freebird = nextbird;
        }
        free(*q);
        *q = NULL;
    }
}

bool pq_is_empty(PriorityQueue *q) {
    if (q->list == NULL) {
        return true;
    } else {
        return false;
    }
}

bool pq_size_is_1(PriorityQueue *q) {
    if (q != NULL && q->list != NULL && q->list->next == NULL) {
        return true;
    } else {
        return false;
    }
}

bool pq_less_than(ListElement *e1, ListElement *e2) {
    if (e1 == NULL || e2 == NULL) {
        return false;
    }
    if (e1->tree->weight < e2->tree->weight) {
        return true;
    } else if (e1->tree->weight > e2->tree->weight) {
        return false;
    } else {
        return e1->tree->symbol < e2->tree->symbol;
    }
}

void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *new_element = calloc(1, sizeof(ListElement));
    if (new_element == NULL) {
        return;
    }

    new_element->tree = tree;

    if (pq_is_empty(q)) {
        q->list = new_element;
    } else if (pq_less_than(new_element, q->list)) {
        new_element->next = q->list;
        q->list = new_element;
    } else {
        ListElement *holder = q->list;

        while (holder->next != NULL && !pq_less_than(new_element, holder->next)) {
            holder = holder->next;
        }

        new_element->next = holder->next;
        holder->next = new_element;
    }
}

Node *dequeue(PriorityQueue *q) {
    if (q->list == NULL) {
        exit(1);
    }

    ListElement *holder = q->list;
    Node *holder2 = holder->tree;

    q->list = holder->next;

    free(holder);
    return holder2;
}

void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;

    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }

        node_print_tree(e->tree);
        e = e->next;
    }
    printf("=============================================\n");
}
