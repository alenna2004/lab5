#include "abonent.h"
#ifndef MYSORT
#define MYSORT

void gnome_sort(void *ar, int len, int size, int (*compar)(const void *, const void*));
void shell_sort(void *ar, int len, int size, int (*compar)(const void *, const void*));

#endif
