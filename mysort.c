#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abonent.h"
#include "mysort.h"


void swap(void *a, void *b, int size){
	char *ca = (char*)a;
	char *cb = (char*)b;
	do{
		char tmp = *ca;
		*ca = *cb;
		*cb = tmp;
		ca+=1;
		cb+=1;
		size -=1;
	}
	while(size>0);
}



void gnome_sort(void *ar, int len, int size, int (*compar)(const void *, const void*)){
	char *arr = (char *)ar;
	int i = size;
	int j = 2*size;
	while(i<(len*size)){
		if ((*compar)((void *)arr+i, (void *)arr+i-size) >0){
			i = j;
			j+=size;
		}
		else{
			swap(arr+i, arr+i-size, size);
			i = i-size;
			if(i==0){
				i=j;
				j+=size;
			}
		}
	}
}


void shell_sort(void *ar, int len, int size, int (*compar)(const void *, const void*)){
	char *arr = (char *)ar;
	int cur_len = (len*size);
	int d = len/2;
	while(d>0){
		for(int i = d*size; i<cur_len; i+=size){
			for (int j = i; j - (d*size) >=0; j -= (d*size)){
				if((*compar)((void *)arr+j-d*size, (void *)arr+j) > 0){
            		swap(arr+j-d*size, arr+j, size);
            	}
            }
		}
		d/=2;
	}
}