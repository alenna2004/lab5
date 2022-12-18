#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "abonent.h"
#include "mysort.h"


Abonent gen_abonent(){
	int name_len = (rand() % 512) + 1;
	char *name = (char*)malloc((name_len+1)*sizeof(char));
	char *number = (char*)malloc(12*sizeof(char));
	int time  = rand()+1;
	char *alphabet = "abcdefghijklmnopqrstuvwxyz- абвгдежзиклмнопрстуфхцчшщъыьэюя";
	char *digits = "0123456789";
	int alph_len = strlen(alphabet);
	for (int i = 0; i<name_len;  i++){
		int index = rand() % alph_len;
		name[i] = alphabet[index];
	}
	name[name_len] = '\0';
	for (int i = 0; i <11; i++){
		int index = rand() % 10;
		number[i] = digits[index];
	}
	number[11] = '\0';
	return new_abonent(name, number, time);
}


Abonent *gen_arr(int num_el){
	Abonent *arr = (Abonent *)malloc(num_el*sizeof(Abonent));
	for (int i=0; i<num_el; i++){
		arr[i] = gen_abonent();
	}
	return arr;
}


int main(int argc, char **argv){
	 if(argc == 1) {
        printf("You must parse some options to run this programm\n");
        printf("You can parse algoritm name with flag a\n");
        printf("You can parse field for sorting with flag f\n");
        printf("You can parse destination of sorting with flag d\n");
        printf("You must parse num of elements in each array with flag e and nun of arrays with flag m\n");
        return 1;
    }
    char *opts = "a:f:d:e:m:"; 
    char *alg = "qsort";
    char *field = "name";
    char *dest = "up";
    int num_el = 0;
    int num_ar = 0; 
    int opt; 
    while((opt = getopt(argc, argv, opts)) != -1) { 
        switch(opt) {
            case 'a':{ 
                alg = optarg;
                if(strcmp(alg,"qsort") != 0 && strcmp(alg,"gnome") != 0 && strcmp(alg,"shell") != 0){
                	printf("The algoritm name canbe only qsort, gnome or shell\n");
                	return 1;
                }
                break;
            }
            case 'f':{
                 field = optarg;
                 if(strcmp(field,"name") != 0 && strcmp(field,"number") != 0 && strcmp(field,"time") != 0){
                 	printf("The field can be only name, number or time\n");
                 	return 1;
                 }
                 break;
             }
            case 'd':{
                 dest = optarg;
                 if(strcmp(dest,"up") != 0 && strcmp(dest,"down") != 0){
                 	printf("The destination can be only up or down\n");
                 	return 1;
                 }
                 break;
            }
            case 'e':{
            	num_el = atoi(optarg);
            	break;
            }
        	case 'm':{
        		num_ar = atoi(optarg);
        	}
        }
    }
    if (num_el == 0 || num_ar == 0){
    	printf("There must be number of element in each array and number of arrays\n");
    	return 1;
    }
	Abonent **array = malloc(num_ar*sizeof(Abonent *));
	for (int i = 0;  i<num_ar; i++){
		array[i] = gen_arr(num_el);
	}
	double total_time = 0;
	if (strcmp(alg,"qsort") == 0){
		if(strcmp(field,"name") == 0){
			if(strcmp(dest,"up") == 0){
				for(int i = 0; i<num_ar; i++){
					clock_t start = clock();
					qsort(array[i], num_el, sizeof(Abonent), (int (*)(const void *, const void *)) abonent_cmp_name_up);
					clock_t end = clock();
					double sort_time = (double)(end-start)/CLOCKS_PER_SEC;
					total_time += sort_time;
				}
			}
			else{
				for(int i = 0; i<num_ar; i++){
					clock_t start = clock();
					qsort(array[i], num_el, sizeof(Abonent), (int (*)(const void *, const void *)) abonent_cmp_name_down);
					clock_t end = clock();
					double sort_time = (double)(end-start)/CLOCKS_PER_SEC;
					total_time += sort_time;
				}
			}
		}
		else if(strcmp(field,"number") == 0){
			if(strcmp(dest,"up") == 0){
				for(int i = 0; i<num_ar; i++){
					clock_t start = clock();
					qsort(array[i], num_el, sizeof(Abonent), (int (*)(const void *, const void *)) abonent_cmp_number_up);
					clock_t end = clock();
					double sort_time = (double)(end-start)/CLOCKS_PER_SEC;
					total_time += sort_time;
				}
			}
			else{
				for(int i = 0; i<num_ar; i++){
					clock_t start = clock();
					qsort(array[i], num_el, sizeof(Abonent), (int (*)(const void *, const void *)) abonent_cmp_number_down);
					clock_t end = clock();
					double sort_time = (double)(end-start)/CLOCKS_PER_SEC;
					total_time += sort_time;
				}
			}
		}
		else{
			if(strcmp(dest,"up") == 0){
				for(int i = 0; i<num_ar; i++){
					clock_t start = clock();
					qsort(array[i], num_el, sizeof(Abonent), (int (*)(const void *, const void *)) abonent_cmp_time_up);
					clock_t end = clock();
					double sort_time = (double)(end-start)/CLOCKS_PER_SEC;
					total_time += sort_time;
				}
			}
			else{
				for(int i = 0; i<num_ar; i++){
					clock_t start = clock();
					qsort(array[i], num_el, sizeof(Abonent), (int (*)(const void *, const void *)) abonent_cmp_time_down);
					clock_t end = clock();
					double sort_time = (double)(end-start)/CLOCKS_PER_SEC;
					total_time += sort_time;
				}
			}
		}
	}
	else if (strcmp(alg,"gnome") == 0){
		for(int i = 0; i<num_ar; i++){
				clock_t start = clock();
				gnome_sort(array+i, num_el, field, dest);
				clock_t end = clock();
				double sort_time = (double)(end-start)/CLOCKS_PER_SEC;
				total_time += sort_time;
		}
	}
	else{
		for(int i = 0; i<num_ar; i++){
			clock_t start = clock();
			gnome_sort(array+i, num_el, field, dest);
			clock_t end = clock();
			double sort_time = (double)(end-start)/CLOCKS_PER_SEC;
			total_time += sort_time;
		}
	}
    printf("%lf\n", total_time/(double)num_ar);
    for (int j = 0; j<num_ar; j++){
		for (int i=0; i<num_el; i++){
			free(array[j][i].name);
			free(array[j][i].number);
		}
		free(array[j]);
	}
	free(array);
	return 0;
}