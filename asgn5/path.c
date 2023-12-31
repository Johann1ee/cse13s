#include "path.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *createPath = (Path *) malloc(sizeof(Path));
    createPath->total_weight = 0;
    createPath->vertices = stack_create(capacity);
    return createPath;
}

void path_free(Path **pp) {
    if (*pp) {
        stack_free(&(*pp)->vertices);
        free(*pp);
        *pp = NULL;
    }
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    if (stack_empty(p->vertices)) {
        p->total_weight = 0;
        stack_push(p->vertices, val);
    } else {
        uint32_t holder = 0;
        stack_peek(p->vertices, &holder);
        stack_push(p->vertices, val);

        p->total_weight += graph_get_weight(g, holder, val);
    }
}

uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t holder = 0;
    stack_peek(p->vertices, &holder);

    if (stack_size(p->vertices) <= 2) {
        stack_pop(p->vertices, &holder);
        p->total_weight = 0;
    } else {
        uint32_t temp = 0;
        stack_pop(p->vertices, &temp);
        stack_peek(p->vertices, &temp);

        p->total_weight -= graph_get_weight(g, holder, temp);
    }

    return holder;
}

void path_copy(Path *dst, const Path *src) {
    dst->total_weight = src->total_weight;
    stack_copy(dst->vertices, src->vertices);
}

void path_print(const Path *p, FILE *f, const Graph *g) {
    stack_print(p->vertices, f, graph_get_names(g));
}
