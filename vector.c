#include "vector.h"

void init_vector(struct vector* v)
{
	v->data = malloc(sizeof(int) * INIT_VECTOR_SIZE);
	v->size = 0;
	v->capacity = INIT_VECTOR_SIZE;
}

int access_element_vector(struct vector* v, size_t index)
{
	if(index >= v->size)
		exit(OUT_OF_BOUNDS);
	return v->data[index];
}

void insert_element_vector(struct vector* v, int element_to_insert)
{
	if(v->capacity == v->size)
	{
		v->data = realloc(v->data, sizeof(int) * v->capacity * 2);
		v->capacity *= 2;
	}
	v->data[v->size] = element_to_insert;
	v->size += 1;
}


int* vector_get_ptr(struct vector* v)
{
	return v->data;
}

//int get_value_and_clear_vector(struct vector_value* v) {
//	int value;
//
//	v->data[v->size] = '\0';
//	value = atoi(v->data);
//
//	memset(v->data, '\0', v->size*sizeof(char));
//	v->size = 0;
//
//	return value;
//}

void free_vector(struct vector* v)
{
	free(v->data);
	v->size = 0;
}
