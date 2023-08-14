#include "type_data.h"


extern const index_t n_primitive_types = 12;
extern type_data_t primitive_types[] = {
    {
        .byte_size = 1,
        .full_name = L"char",
        .immediate_name = L"char",
        .next = 0,
        .param = 0,
        .real_name = L"char"
    },
    {
        .byte_size = 2,
        .full_name = L"short",
        .immediate_name = L"short",
        .next = 0,
        .param = 0,
        .real_name = L"short"
    },
    {
        .byte_size = 4,
        .full_name = L"int",
        .immediate_name = L"int",
        .next = 0,
        .param = 0,
        .real_name = L"int"
    },
    {
        .byte_size = 4,
        .full_name = L"long",
        .immediate_name = L"long",
        .next = 0,
        .param = 0,
        .real_name = L"long"
    },
    {
        .byte_size = 8,
        .full_name = L"long long",
        .immediate_name = L"long long",
        .next = 0,
        .param = 0,
        .real_name = L"long long"
    },
    {
        .byte_size = 1,
        .full_name = L"unsigned char",
        .immediate_name = L"unsigned char",
        .next = 0,
        .param = 0,
        .real_name = L"unsigned char"
    },
    {
        .byte_size = 2,
        .full_name = L"unsigned short",
        .immediate_name = L"unsigned short",
        .next = 0,
        .param = 0,
        .real_name = L"unsigned short"
    },
    {
        .byte_size = 4,
        .full_name = L"unsigned int",
        .immediate_name = L"unsigned int",
        .next = 0,
        .param = 0,
        .real_name = L"unsigned int"
    },
    {
        .byte_size = 4,
        .full_name = L"unsigned long",
        .immediate_name = L"unsigned long",
        .next = 0,
        .param = 0,
        .real_name = L"unsigned long"
    },
    {
        .byte_size = 8,
        .full_name = L"unsigned long long",
        .immediate_name = L"unsigned long long",
        .next = 0,
        .param = 0,
        .real_name = L"unsigned long long"
    },
    {
        .byte_size = 4,
        .full_name = L"float",
        .immediate_name = L"float",
        .next = 0,
        .param = 0,
        .real_name = L"float"
    },
    {
        .byte_size = 8,
        .full_name = L"double",
        .immediate_name = L"double",
        .next = 0,
        .param = 0,
        .real_name = L"double"
    }
};

extern type_data_t_vector_t* struct_types = 0;
extern type_data_t_vector_t* enum_types = 0;
extern type_data_t_vector_t* union_types = 0;
extern type_data_t_vector_t* typedefed_types = 0;

extern enum_value_t_vector_t* enum_values = 0;

void init_type_resolution(void)
{
    struct_types = new_type_data_t_vector_hijack(malloc(sizeof(type_data_t) * 128), 0, 128);
    enum_types = new_type_data_t_vector_hijack(malloc(sizeof(type_data_t) * 128), 0, 128);
    union_types = new_type_data_t_vector_hijack(malloc(sizeof(type_data_t) * 128), 0, 128);
    
    enum_values = new_enum_value_t_vector_hijack(malloc(sizeof(enum_value_t) * 128), 0, 128);
}

void finalize_type_resolution(void)
{
    delete_type_data_t_vector_obj(struct_types, type_data_t_destructor);
    delete_type_data_t_vector_obj(enum_types, type_data_t_destructor);
    delete_type_data_t_vector_obj(union_types, type_data_t_destructor);

    delete_type_data_t_vector_obj(enum_values, enum_value_t_destructor);
}

index_t find_primitive_type_data(const char* name)
{
    for (int i = 0; i < n_primitive_types; i++)
    {
        if (strcmp(name, primitive_types[i].full_name) == 0)
        {
            return i;
        }
    }
    return -1;
}

index_t find_struct_type_data(const char* name)
{
    for (int i = 0; i < type_data_t_vector_size(struct_types); i++)
    {
        if (strcmp(name, struct_types->dat_ptr[i].full_name) == 0)
        {
            return i;
        }
    }
    return -1;
}

index_t find_enum_type_data(const char* name)
{
    for (int i = 0; i < type_data_t_vector_size(enum_types); i++)
    {
        if (strcmp(name, enum_types->dat_ptr[i].full_name) == 0)
        {
            return i;
        }
    }
    return -1;
}

index_t find_union_type_data(const char* name)
{
    for (int i = 0; i < type_data_t_vector_size(union_types); i++)
    {
        if (strcmp(name, union_types->dat_ptr[i].full_name) == 0)
        {
            return i;
        }
    }
    return -1;
}

index_t find_typedefed_type_data(const char* name)
{
    for (int i = 0; i < type_data_t_vector_size(union_types); i++)
    {
        if (strcmp(name, typedefed_types->dat_ptr[i].full_name) == 0)
        {
            return i;
        }
    }
    return -1;
}

int get_type_data(const char* name, type_data_t* data)
{
    index_t index = -1;
    index = strstr(name, 0);
    // TODO parse type kind, then rest of data
    //
    index = find_primitive_type_data(name);
    if (index != -1)
    {
        memcpy(data, &primitive_types[index], sizeof(type_data_t));
        return TK_PRIMITIVE;
    }
    index = find_struct_type_data(name);
    if (index != -1)
    {
        memcpy(data, &struct_types->dat_ptr[index], sizeof(type_data_t));
        return TK_STRUCT;
    }
    index = find_enum_type_data(name);
    if (index != -1)
    {
        memcpy(data, &enum_types->dat_ptr[index], sizeof(type_data_t));
        return TK_ENUM;
    }
    index = find_union_type_data(name);
    if (index != -1)
    {
        memcpy(data, &union_types->dat_ptr[index], sizeof(type_data_t));
        return TK_UNION;
    }
    index = find_typedefed_type_data(name);
    if (index != -1)
    {
        memcpy(data, &typedefed_types->dat_ptr[index], sizeof(type_data_t));
        return TK_UNION;
    }
    memset(data, 0, sizeof(type_data_t));
    return TK_NA;
}

void insert_enum_def(const char* id, long long val)
{
    char* cid = malloc(strlen(id) + 1);
    strcpy(cid, id);
    enum_value_t kv = { .name = cid, .value = val };
    enum_value_t_vector_push_back(enum_values, kv);
}

int resolve_enum_def(const char* id, long long* lpvalue)
{
    for (enum_value_t* i = enum_values->dat_ptr; i < enum_values->end_ptr; i++)
    {
        if (strcmp(i->name, id) == 0)
        {
            (*lpvalue) = i->value;
            return 1;
        }
    }
    return 0;
}




