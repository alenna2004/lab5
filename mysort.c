#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abonent.h"
#include "mysort.h"


void swap(Abonent *a, Abonent *b){
	Abonent cur = new_abonent(a->name, a->number, a->time);
	*a = *b;
	*b = cur; 
}


int comparator(const Abonent *a, const Abonent *b, const char *field, const char *dest){
	if (strcmp(field,"name") == 0){
		if (strcmp(dest,"down")==0){
			return abonent_cmp_name_down(a,b);
		}
		else{
			return abonent_cmp_name_up(a,b);
		}
	}
	 if (strcmp(field, "number")==0){
		if (strcmp(dest,"down")==0){
			return abonent_cmp_number_down(a,b);
		}
		else{
			return abonent_cmp_number_up(a,b);
		}
	}
	if(strcmp(field,"time")==0){
		if (strcmp(dest,"down")==0){
			return abonent_cmp_time_down(a,b);
		}
		else{
			return abonent_cmp_time_up(a,b);
		}
	}
}

void gnome_sort(Abonent **arr, int len, const char *field, const char *dest){
	int i = 1;
	int j = 2;
	while(i<len){
		if (comparator(*arr+i, *arr+i-1, field, dest) >0){
			i = j;
			j+=1;
		}
		else{
			swap(*arr+i, *arr+i-1);
			i = i-1;
			if(i==0){
				i=j;
				j+=1;
			}
		}
	}
}


int count_max_pow(int len){
	int i = 0;
	while(len>1){
		len /=2;
		i+=1;
	}
	return i;
}


void shell_sort(Abonent **arr, int len, const char *field, const char *dest){
	int d = len/2;
	while(d>0){
		for(int i = d; i<len; i++){
			for (int j = i; j - d >=0; j -= d){
				if(comparator(*arr+j-d, *arr+j, field, dest) > 0){
            		swap(*arr+j-d, *arr+j);
            	}
            }
		}
		d/=2;
	}
}