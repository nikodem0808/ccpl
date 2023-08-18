#include "main.h"




int ic(int* a, int* b)
{
	return *a - *b;
}

int main(int argc, char** argv)
{
	if (argc > 3) // wrong inequality for testing
	{
		printf("Too few arguments, need at least one input and one output file path.\n");
		return 1;
	}
	//
	int hel[] = { -1, -2, -4 };
	int* hel2[] = { hel, hel + 1, hel + 2 };
	int_vector_t* ptr = new_int_vector();
	int_vector_push_back(ptr, 3);
	int_vector_push_back(ptr, 4);
	int_vector_push_back(ptr, 1);
	int_vector_push_back(ptr, -3);
	int_vector_push_back(ptr, 5);
	int_vector_push_back(ptr, 13);
	int_vector_push_back(ptr, 0);
	int_vector_push_back(ptr, 0);
	qsort(ptr->dat_ptr, int_vector_size(ptr), sizeof(int), ic);
	int_vector_insert_n_ref(ptr, 3, hel2, 3);
	for (int* p = ptr->dat_ptr; p != ptr->end_ptr; p++)
	{
		printf("%d ", *p);
	}
	//
	return 0;
}

