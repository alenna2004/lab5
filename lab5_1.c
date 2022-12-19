#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "abonent.h"
#include "mysort.h"


char *prettify_number(char *number){
	int i = 0;
	int k = 0;
	char *new_num = (char*)malloc(12*sizeof(char));
	while(number[i] != '\0'){
		if (number[i] !=' ' && number[i] != '+'){
			new_num[k] = *(number + i);
			k++;
		}
		i++;
	}
	new_num[11] = '\0';
	return new_num;
}


char *get_line(FILE *f){
	int n, len = 0;
	int L = 80;
	char buf[L+1];
	char *ptr = (char*)malloc(1);
	*ptr = '\0';
	do{
		n = fscanf(f,"%80[^\n]", buf);
		if (n<0){
			free(ptr);
			ptr = NULL;
			continue;
		}
		if (n==0){
			fscanf(f,"%*c");
		}
		else{
			len += strlen(buf);
			ptr = (char*)realloc(ptr, len+1);
			strcat(ptr,buf);
		}
	}
	while(n>0);
	return ptr;
}


Abonent *read_file(char *filename, int *arr_len){
	int N = 4;
	int num_abonents = 0;
	int memal = N;
	FILE *f;
	f = fopen(filename, "r");
	char *line = get_line(f);
	Abonent *arr = (Abonent *)malloc(N*sizeof(Abonent));
	while (line){
		char *name = strtok(line,",");
		char *number = prettify_number(strtok(NULL, ","));
		int time = atoi(strtok(strtok(NULL, ","), " "));
		Abonent a = new_abonent(name, number, time);
		num_abonents+=1;
		if (num_abonents>memal){
			memal += N;
			arr = (Abonent*)realloc(arr, memal*sizeof(Abonent));
		}
		arr[num_abonents-1] = a;
		line = get_line(f);
	}
	arr = (Abonent*)realloc(arr, num_abonents*sizeof(Abonent));
	fclose(f);
	*arr_len = num_abonents;
	return arr;
} 


int (*comparator(const char *field, const char *dest))(const Abonent *, const Abonent *){
	if (strcmp(field,"name") == 0){
		if (strcmp(dest,"down")==0){
			return &abonent_cmp_name_down;
		}
		else{
			return &abonent_cmp_name_up;
		}
	}
	 if (strcmp(field, "number")==0){
		if (strcmp(dest,"down")==0){
			return &abonent_cmp_number_down;
		}
		else{
			return &abonent_cmp_number_up;
		}
	}
	if(strcmp(field,"time")==0){
		if (strcmp(dest,"down")==0){
			return &abonent_cmp_time_down;
		}
		else{
			return &abonent_cmp_time_up;
		}
	}
}



int main(int argc, char **argv){
	 if(argc == 1) {
        printf("You must parse some options to run this programm\n");
        printf("You can parse algoritm name with flag a\n");
        printf("You can parse field for sorting with flag f\n");
        printf("You can parse destination of sorting with flag d\n");
        printf("You must parse name of input file with flag i and name of output file with flag o\n");
        return 1;
    }
    char *opts = "a:f:d:"; 
    char *alg = "qsort";
    char *field = "name";
    char *dest = "up";
    char *input_name = NULL;
    char *output_name = NULL; 
    int opt; 
    while(optind < argc){
    	if ((opt = getopt(argc, argv, opts)) != -1){
	        switch(opt) {
	            case 'a':{ 
	                alg = optarg;
	                if(strcmp(alg,"qsort") != 0 && strcmp(alg,"gnome") != 0 && strcmp(alg,"shell") != 0){
	                	printf("The algoritm name can be only qsort, gnome or shell\n");
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
	        }
	    }
	    else{
	    	input_name = argv[optind];
	    	optind+=1;
	    	output_name = argv[optind];
	    	optind+=1;
	    }
    }
    if (input_name == NULL || output_name == NULL){
    	printf("There must be names of input and output files\n");
    	return 1;
    }
    int len;
	Abonent *array = read_file(input_name, &len);
	int (*fp)(const Abonent *, const Abonent *);
	fp = comparator(field, dest);	
	if (strcmp(alg,"qsort") == 0){
		qsort(array, len, sizeof(Abonent), (int (*)(const void *, const void *)) fp);
	}
	else if (strcmp(alg,"gnome") == 0){
		gnome_sort(array, len, sizeof(Abonent), (int (*)(const void *, const void *)) fp);
	}
	else{
		shell_sort(array, len, sizeof(Abonent), (int (*)(const void *, const void *)) fp);
	}
    FILE *fd;
    fd = fopen(output_name, "w");
	for (int i=0; i<len; i++){
		fprintf(fd, "%s, %s, %d\n", array[i].name, array[i].number, array[i].time);
		free(array[i].name);
		free(array[i].number);
	}
	fclose(fd);
	free(array);
	return 0;
}