
#ifndef TYPE_DATA_H
#define TYPE_DATA_H

#include "unidef.h"
#include "utils.h"

extern const index_t n_primitive_types = 12;
extern type_data_t primitive_types[];

extern type_data_t_vector_t* struct_types;
extern type_data_t_vector_t* enum_types;
extern type_data_t_vector_t* union_types;
extern type_data_t_vector_t* typedefed_types;

extern enum_value_t_vector_t* enum_values;

void init_type_resolution(void);

void finalize_type_resolution(void);

index_t find_primitive_type_data(const char* name);

index_t find_struct_type_data(const char* name);

index_t find_enum_type_data(const char* name);

index_t find_union_type_data(const char* name);

int get_type_data(const char* full_name, type_data_t* data);

void insert_enum_def(const char* id, long long val);

int resolve_enum_def(const char* id, long long* lpvalue);


#endif