#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "unidef.h"
#include "concat.h"

#define c2(a, b) C2(a, b)
#define C2(a,b) a ## b
#define c3(a,b,c) C3(a,b,c)
#define C3(a,b,c) a ## b ## c
#define c4(a,b,c,d) C4(a,b,c,d)
#define C4(a,b,c,d) a ## b ## c ## d
#define c5(a,b,c,d,e) C5(a,b,c,d,e)
#define C5(a,b,c,d,e) a ## b ## c ## d ## e
#define c6(a,b,c,d,e,f) C6(a,b,c,d,e,f)
#define C6(a,b,c,d,e,f) a ## b ## c ## d ## e ## f




#define _expand_vectordef(VAR) VAR
#define _to_cstr_vectordef(VAR) _to_text_vectordef(VAR)
#define _to_text_vectordef(VAR) #VAR

#ifndef T
#pragma message "vector element type is " _to_cstr_vectordef(T)
#error vector element type (preprocessor macro T) not defined!
#endif



typedef struct c3(_,T,_vector_base)
{
	T *dat_ptr;
	T *end_ptr;
	T *cap_ptr;
} c2(T,_vector_t);

#define vector_t c2(T,_vector_t)

typedef void (* c3(_,T,_destructor_vectordef))(T *);
typedef void (* c3(_,T,_constructor_vectordef))(T *);

// constructors

static vector_t * c3(new_,T,_vector) (void)
{
	vector_t *ptr = malloc(sizeof(vector_t));
	ptr->dat_ptr = malloc(sizeof(T));
	ptr->end_ptr = ptr->dat_ptr;
	ptr->cap_ptr = ptr->dat_ptr + 1;
	return ptr;
}

static vector_t * c3(new_,T,_vector_n) (index_t n)
{
	vector_t *ptr = malloc(sizeof(vector_t));
	index_t cap = 1;
	while (cap < n) cap <<= 1;
	T *dat_ptr = malloc(sizeof(T) * cap);
	ptr->dat_ptr = dat_ptr;
	ptr->end_ptr = dat_ptr + n;
	ptr->cap_ptr = dat_ptr + cap;
	return ptr;
}

static vector_t * c3(new_,T,_vector_init) (index_t n, T elem)
{
	vector_t *ptr = c3(new_,T,_vector_n) (n);
	T *eptr = ptr->dat_ptr;
	for (index_t i = 0; i < n; i++)
	{
		eptr[i] = elem;
	}
	return ptr;
}

static vector_t * c3(new_,T,_vector_ref_init) (index_t n, T *elem_ptr)
{
	vector_t *ptr = c3(new_,T,_vector_n) (n);
	T *eptr = ptr->dat_ptr;
	for (index_t i = 0; i < n; i++)
	{
		memcpy(&eptr[i], elem_ptr, sizeof(T));
	}
	return ptr;
}

static vector_t * c3(new_,T,_vector_hijack) (T *elem_ptr, index_t end, index_t cap)
{
	vector_t *ptr = malloc(sizeof(vector_t));
	ptr->dat_ptr = elem_ptr;
	ptr->end_ptr = elem_ptr + end;
	ptr->end_ptr = elem_ptr + cap;
	return ptr;
}

// destructors

static void c3(delete_,T,_vector) (vector_t *ptr)
{
	free(ptr->dat_ptr);
	free(ptr);
}

static void c3(delete_,T,_vector_obj) (vector_t *ptr, c3(_,T,_destructor_vectordef) destr)
{
	T *it, *end;
	for (it = ptr->dat_ptr, end = ptr->end_ptr; it != end; it++)
	{
		destr(it);
	}
	c3(delete_,T,_vector) (ptr);
}

// member access

static T c2(T,_vector_get_n) (vector_t *vec, index_t n)
{
	return vec->dat_ptr[n];
}

static T* c2(T,_vector_get_ptr_n) (vector_t *vec, index_t n)
{
	return vec->dat_ptr + n;
}

static void c2(T,_vector_set_n) (vector_t *vec, index_t n, T val)
{
	vec->dat_ptr[n] = val;
}

static void c2(T,_vector_set_ptr_n) (vector_t *vec, index_t n, T *val_ptr)
{
	memcpy(vec->dat_ptr, val_ptr, sizeof(T));
}

static T c2(T,_vector_get_back) (vector_t *vec)
{
	return *(vec->end_ptr - 1);
}

static T* c2(T,_vector_get_back_ref) (vector_t *vec)
{
	return vec->end_ptr - 1;
}

// other

static void c2(T,_vector_clear) (vector_t *vec)
{
	free(vec->dat_ptr);
	memset(vec, 0, sizeof(vector_t));
}

static void c2(T,_vector_clear_obj) (vector_t* vec, c3(_,T,_destructor_vectordef) destr)
{
	while (vec->end_ptr != vec->dat_ptr)
	{
		vec->end_ptr--;
		destr(vec->end_ptr);
	}
	free(vec->dat_ptr);
	memset(vec, 0, sizeof(vector_t));
}

static int c2(T,_vector_empty) (vector_t *vec)
{
	return vec->end_ptr == vec->dat_ptr;
}

static index_t c2(T,_vector_size) (vector_t *vec)
{
	return ((index_t)(vec->end_ptr - vec->dat_ptr));
}

static index_t c2(T,_vector_capacity) (vector_t *vec)
{
	return ((index_t)(vec->cap_ptr - vec->dat_ptr));
}

static void c2(T,_vector_push_back) (vector_t *vec, T elem)
{
	if (vec->end_ptr != vec->cap_ptr)
	{
		(*(vec->end_ptr++)) = elem;
		return;
	}
	index_t vec_cap = vec->cap_ptr - vec->dat_ptr;
	T *new_dat_ptr = malloc(sizeof(T) * 2 * vec_cap);
	T *new_end_ptr = new_dat_ptr + vec_cap;
	T *new_cap_ptr = new_end_ptr + vec_cap;
	(*new_end_ptr) = elem;
	new_end_ptr++;
	memcpy(new_dat_ptr, vec->dat_ptr, sizeof(T) * vec_cap);
	free(vec->dat_ptr);
	vec->dat_ptr = new_dat_ptr;
	vec->end_ptr = new_end_ptr;
	vec->cap_ptr = new_cap_ptr;
}

static void c2(T,_vector_push_back_ref) (vector_t *vec, T *elem_ptr)
{
	if (vec->end_ptr != vec->cap_ptr)
	{
		memcpy(vec->end_ptr++, elem_ptr, sizeof(T));
		return;
	}
	ptrdiff_t vec_cap = vec->cap_ptr - vec->dat_ptr;
	T *new_dat_ptr = malloc(sizeof(T) * 2 * vec_cap);
	T *new_end_ptr = new_dat_ptr + vec_cap;
	T *new_cap_ptr = new_end_ptr + vec_cap;
	memcpy(new_end_ptr, elem_ptr, sizeof(T));
	new_end_ptr++;
	memcpy(new_dat_ptr, vec->dat_ptr, sizeof(T) * vec_cap);
	free(vec->dat_ptr);
	vec->dat_ptr = new_dat_ptr;
	vec->end_ptr = new_end_ptr;
	vec->cap_ptr = new_cap_ptr;
}

static void c2(T,_vector_push_back_n) (vector_t *vec, T *elem_ptr, index_t n)
{
	ptrdiff_t vec_left = vec->cap_ptr - vec->end_ptr;
	if (vec_left >= n)
	{
		memcpy(vec->end_ptr, elem_ptr, sizeof(T) * n);
		vec->end_ptr += n;
		return;
	}
	ptrdiff_t vec_cap = (vec->cap_ptr - vec->dat_ptr);
	ptrdiff_t vec_size = (vec->end_ptr - vec->dat_ptr);
	ptrdiff_t new_vec_size = vec_size + n;
	ptrdiff_t new_vec_cap = 2 * vec_cap;
	while (new_vec_cap < new_vec_size)
	{
		printf("h\n");
		new_vec_cap *= 2;
	}
	T *new_dat_ptr = malloc(sizeof(T) * new_vec_cap);
	T *new_end_ptr = new_dat_ptr + vec_size;
	T *new_cap_ptr = new_dat_ptr + new_vec_cap;
	memcpy(new_dat_ptr, vec->dat_ptr, sizeof(T) * vec_size);
	memcpy(new_end_ptr, elem_ptr, n * sizeof(T));
	new_end_ptr += n;
	free(vec->dat_ptr);
	vec->dat_ptr = new_dat_ptr;
	vec->end_ptr = new_end_ptr;
	vec->cap_ptr = new_cap_ptr;
}

static void c2(T,_vector_push_back_n_ref) (vector_t *vec, T **elem_ref_ptr, index_t n)
{
	ptrdiff_t vec_left = vec->cap_ptr - vec->end_ptr;
	if (vec_left >= n)
	{
		for (index_t i = 0; i < n; i++)
		{
			memcpy(vec->end_ptr + i, elem_ref_ptr[i], sizeof(T));
		}
		vec->end_ptr += n;
		return;
	}
	ptrdiff_t vec_cap = (vec->cap_ptr - vec->dat_ptr);
	ptrdiff_t vec_size = (vec->end_ptr - vec->dat_ptr);
	ptrdiff_t new_vec_size = vec_size + n;
	ptrdiff_t new_vec_cap = 2 * vec_cap;
	while (new_vec_cap < new_vec_size)
	{
		new_vec_cap *= 2;
	}
	T *new_dat_ptr = malloc(sizeof(T) * new_vec_cap);
	T *new_end_ptr = new_dat_ptr + vec_size;
	T *new_cap_ptr = new_dat_ptr + new_vec_cap;
	memcpy(new_dat_ptr, vec->dat_ptr, sizeof(T) * vec_size);
	for (index_t i = 0; i < vec_size; i++)
	{
		memcpy(new_end_ptr + i, elem_ref_ptr[i], sizeof(T));
	}
	new_end_ptr += n;
	free(vec->dat_ptr);
	vec->dat_ptr = new_dat_ptr;
	vec->end_ptr = new_end_ptr;
	vec->cap_ptr = new_cap_ptr;
}

static void c2(T,_vector_pop_back) (vector_t *vec) // abortusz
{
	vec->end_ptr--;
}

static void c2(T,_vector_pop_back_obj) (vector_t *vec, c3(_,T,_destructor_vectordef) destr)
{
	vec->end_ptr--;
	destr(vec->end_ptr);
}

static void c2(T,_vector_pop_n) (vector_t *vec, index_t n)
{
	vec->end_ptr -= n;
}

static void c2(T,_vector_pop_n_obj) (vector_t *vec, index_t n, c3(_,T,_destructor_vectordef) destr)
{
	while (n > 0)
	{
		destr(--vec->end_ptr);
		n--;
	}
}

static void c2(T,_vector_hijack) (vector_t *vec, T *elem_ptr, index_t end, index_t cap)
{
	free(vec->dat_ptr);
	vec->dat_ptr = elem_ptr;
	vec->dat_ptr = elem_ptr + end;
	vec->dat_ptr = elem_ptr + cap;
}

static T * c2(T,_vector_release) (vector_t *vec)
{
	T * elem_ptr = vec->dat_ptr;
	vec->dat_ptr = malloc(sizeof(T));
	vec->end_ptr = vec->dat_ptr;
	vec->end_ptr = vec->dat_ptr + 1;
	return elem_ptr;
}

static T * c2(T,_vector_release_s) (vector_t *vec, index_t* end_ptr, index_t* cap_ptr)
{
	if (end_ptr != 0) (*end_ptr) = vec->end_ptr - vec->dat_ptr;
	if (cap_ptr != 0) (*cap_ptr) = vec->cap_ptr - vec->dat_ptr;
	T * elem_ptr = vec->dat_ptr;
	vec->dat_ptr = malloc(sizeof(T));
	vec->end_ptr = vec->dat_ptr;
	vec->end_ptr = vec->dat_ptr + 1;
	return elem_ptr;
}

