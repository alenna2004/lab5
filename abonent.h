#ifndef ABONENT_H
#define ABONENT_H

typedef struct{
	char *name;
	char *number;
	int time;
} Abonent;

Abonent new_abonent(char *name, char *number, int time);
//void print_abonent(const Abonent *a);
int abonent_cmp_name_up(const Abonent *a1, const Abonent *a2);
int abonent_cmp_number_up(const Abonent *a1, const Abonent *a2);
int abonent_cmp_time_up(const Abonent *a1, const Abonent *a2);
int abonent_cmp_name_down(const Abonent *a1, const Abonent *a2);
int abonent_cmp_number_down(const Abonent *a1, const Abonent *a2);
int abonent_cmp_time_down(const Abonent *a1, const Abonent *a2);
//void abonent_array_print(const char *msg, const Abonent *arr, int len);

#endif
