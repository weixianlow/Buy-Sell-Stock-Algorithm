#ifndef H_VECTOR_H
#define H_VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INIT_VECTOR_SIZE 512

enum vector_errors
{
	OUT_OF_BOUNDS = 0,
};

struct vector
{
	int* data;
	int size;
	int capacity;
};

void init_vector(struct vector* v);
int access_element_vector(struct vector* v, size_t index);
void insert_element_vector(struct vector* v, int element_to_insert);
void free_vector(struct vector* v);
int get_value_and_clear_vector(struct vector* v);

#endif
