#include "../include/list.h"

//-----------------------------------------------------------------------------

int main ()
{
    List lst1;

    list_ctor (&lst1, 15);

    debug_list (&lst1);

    list_push (&lst1, 300, 2);
    list_push (&lst1, 301, 3);
    list_push (&lst1, 302, 4);
    list_push (&lst1, 303, 5);

    list_dtor (&lst1);

    return 0;
}

//-----------------------------------------------------------------------------

