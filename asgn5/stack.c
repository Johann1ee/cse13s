#include "stack.h"

#include <stdlib.h>
#include <assert.h>

typedef struct stack{
	uint32_t capacity;
	uint32_t top;
	uint32_t *items;
} Stack;

Stack *stack_create(uint32_t capacity){
	//Attempt to allocate memory for a stack
	//Cast it to a stack pointer too
	Stack *s = (Stack *) malloc(sizeof(Stack));
	s->capacity = capacity;
	s->top = 0;
	//We ened enough memory for <capacity> numbers
	s->items = calloc(s->capacity, sizeof(uint32_t));
	//we created our stack, return it
	return s;
}

void stack_free(Stack **sp){
	if (sp != NULL && *sp != NULL){

		if((*sp)->items){
			free((*sp)->items);
			(*sp)->items = NULL;
		}
		
		free(*sp);
	}
	if (sp != NULL){
		*sp = NULL;
	}
}

bool stack_push(Stack *s, uint32_t val){
	if (stack_full(s)){
		return false;
	}
	
	s->items[s->top] = val;
	s->top++;
	return true;
}

bool stack_pop(Stack *s, uint32_t *val){
	if (stack_empty(s)){
		return false;
	}

	*val = s->items[(s->top) - 1]; 
	s->top--;
	return true;
}

bool stack_peek(const Stack *s, uint32_t *val){
	if (stack_empty(s)){
		return false;
	}

	*val = s->items[(s->top) - 1];
	return true;
}

bool stack_empty(const Stack *s){
	if (s->top == 0){
		return true;
	} else{
		return false;
	}
}

bool stack_full(const Stack *s){
	if (s->top >= s->capacity){
		return true;
	} else{
		return false;
	}
}

uint32_t stack_size(const Stack *s){
	return (s->top) - 1;
}

void stack_copy(Stack *dst, const Stack *src){
	assert(dst->capacity >= src->top);

	for (uint32_t i = 0; i < src->top; i++){
		dst->items[i] = src->items[i];
	}

	dst->top = src->top;
}

void stack_print(const Stack *s, FILE *f, char *vals[]){
	for (uint32_t i = 0; i < s->top; i += 1){
		fprintf(f, "%s\n", vals[s->items[i]]);
	}
}


