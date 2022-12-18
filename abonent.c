#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abonent.h"


Abonent new_abonent(char *name, char *number, int time){
	Abonent a = {name, number, time};
	return a;
}


int abonent_cmp_name_up(const Abonent *a1, const Abonent *a2){
	return strcmp(a1->name, a2->name);
}


int abonent_cmp_number_up(const Abonent *a1, const Abonent *a2){
	return strcmp(a1->number, a2->number);
}


int abonent_cmp_time_up(const Abonent *a1, const Abonent *a2){
	int d = a1->time - a2->time;
	if (d>0){
		return 1;
	}
	if (d<0){
		return -1;
	}
	else{
		return 0;
	}
}

int abonent_cmp_name_down(const Abonent *a1, const Abonent *a2){
	return strcmp(a2->name, a1->name);
}


int abonent_cmp_number_down(const Abonent *a1, const Abonent *a2){
	return strcmp(a2->number, a1->number);
}


int abonent_cmp_time_down(const Abonent *a1, const Abonent *a2){
	int d = a2->time - a1->time;
	if (d>0){
		return 1;
	}
	if (d<0){
		return -1;
	}
	else{
		return 0;
	}
}