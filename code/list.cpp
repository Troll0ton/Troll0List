#include "../include/list.h"

//-----------------------------------------------------------------------------

int list_ctor_ (List *lst,             int capacity_ctor, const char* lst_name,
                const char* file_name, int lst_line                            )
{
    lst->capacity = capacity_ctor + 1;
    lst->size = 3;

    lst->List_info.name = lst_name;
    lst->List_info.file = file_name;
    lst->List_info.dbg_file = fopen ("../dump/list_dump.txt", "w+");
    lst->List_info.line = lst_line;
    lst->List_info.error_codes = 0;
    lst->List_info.cur_status = "OK";

    if (capacity_ctor >= 0)
    {
        lst->buffer = (double*) calloc (1, (capacity_ctor + 1) * sizeof (double));
        lst->next   = (int*)    calloc (1, (capacity_ctor + 1) * sizeof (int));
        lst->prev   = (int*)    calloc (1, (capacity_ctor + 1) * sizeof (int));
    }

    else
    {
        lst->List_info.error_codes |= ERR_CAP;

        return ERR_CAP;
    }

    lst->buffer[0] = 0;
    lst->next[0] = 0;
    lst->prev[0] = 0;

    lst->buffer[1] = 10;
    lst->next[1] = 2;
    lst->prev[1] = 0;

    lst->buffer[2] = 13;
    lst->next[2] = 0;
    lst->prev[2] = 1;

    //verificate_list (lst);

    return 0;
}

//-----------------------------------------------------------------------------

void list_dtor (List *lst)
{
    //verificate_list (lst);

    free (lst->buffer);
    free (lst->next);
    free (lst->prev);

    fclose (lst->List_info.dbg_file);
}

//-----------------------------------------------------------------------------

int list_resize (List *lst, int opt_resize)
{
    if(opt_resize == lst_increase)
    {
        if(lst->capacity == 0)
        {
            lst->capacity = 2;
        }

        lst->capacity *= 2;
    }

    else if(opt_resize == lst_decrease)
    {
        lst->capacity /= 2;
    }

    else
    {
        lst->List_info.error_codes |= ERR_RESIZE;
    }

    lst->buffer = (double*) recalloc (lst->buffer, lst->capacity, lst->size);
    lst->next   = (int*)    recalloc (lst->buffer, lst->capacity, lst->size);
    lst->prev   = (int*)    recalloc (lst->buffer, lst->capacity, lst->size);
}

//-----------------------------------------------------------------------------

void list_push (List *lst, double elem, int pos)
{
    //verificate_stack (lst);

    if(lst->size + 1 > lst->capacity)
    {
        list_resize (lst, lst_increase);
    }

    lst->buffer[lst->size] = elem;

    int nt_pos = lst->next[pos - 1];
    lst->next[pos - 1] = lst->size;
    lst->next[lst->size] = nt_pos;

    lst->prev[lst->size] = lst->prev[pos];
    lst->prev[pos] = lst->size;

    debug_list (lst);

    lst->size++;
}

//-----------------------------------------------------------------------------

void debug_list (List *lst)
{
    printf ("___________________________________________________________\n\n");

    for (int i = 0; i < lst->size; i++)
    {
        printf ("%lg ", lst->buffer[i]);
    }

    printf ("\n");

    for (int i = 0; i < lst->size; i++)
    {
        printf ("%d ", lst->next[i]);
    }

    printf ("\n");

    for (int i = 0; i < lst->size; i++)
    {
        printf ("%d ", lst->prev[i]);
    }

    printf ("\n___________________________________________________________\n\n");
}

//-----------------------------------------------------------------------------

void *recalloc (void *buffer, int capacity, int size)
{
    char *pointer = (char*) realloc ((char*) buffer, capacity * sizeof (double));

    if(capacity > size)
    {
        memset (pointer + size * sizeof (double), '\0', (capacity - size) * sizeof (double));
    }

    return (void*) pointer;
}

//-----------------------------------------------------------------------------


