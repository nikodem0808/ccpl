#include "main.h"




int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("Too few arguments, need at least one input and one output file path.\n");
		return 1;
	}
	//
	lpstr_vector_t* filepaths = new_lpstr_vector_n(argc - 2);
	lpstr output_filename = argv[argc - 1];
	//
	// 
	for (int i = 1; i < argc; i++)
	{
		lpstr_vector_set_n(filepaths, i - 1, argv[i]);
	}
	for (int i = 0; i < lpstr_vector_size(filepaths); i++)
	{
		char buf[512] = { 0 };
		size_t n_read = 0;
		FILE* fl = fopen(lpstr_vector_get_n(filepaths, i), "r");
		do
		{
			n_read = fread(buf, sizeof(char), 512, fl);
			char_vector_push_back_n(file_content, buf, n_read);
		} while(n_read == 512);
		char_vector_push_back(file_content, '\0');
		fclose(fl);
		printf("From file '%s', this was read:\n%s\n", lpstr_vector_get_n(filepaths, i), file_content->dat_ptr);
	}
	//
	return 0;
}

