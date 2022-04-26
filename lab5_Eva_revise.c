#include<stdio.h>
#include<stdlib.h>

//第一題 
int* get_int_array(int n) {
	return (int*)calloc(n, sizeof(int));
}

void set_value(int* p, int v) {
	*p = v;
}

void print_array(int* p, int n) {
	int i;
	for (i = 0 ; i < n-1 ; i++) {
		printf("%d, ", *p+i);
	}
	printf("%d", *p+i);
}

//第二題
typedef struct array_list {
	int nn;
	int (*get_ptr)(int);
	void (*set_ptr)(int*, int);
	void (*print_ptr)(int*, int);
} array_list_t;

//第三題
char* ptr;
char* func(char a[], char b[]) {
	int len_a = 0;
	int len_b = 0;
	while(a[len_a++]);
	while(b[len_b++]);
	ptr = (char*)calloc(len_a+len_b-1, sizeof(char));
	for (int i = 0 ; i < len_a-1 ; i++) {
		ptr[i] = a[i];
	}
	for (int i = 0 ; i < len_b-1 ; i++) {
		ptr[len_a-1+i] = b[i];
	}
	ptr[len_a+len_b-1] = '\0';
	return ptr;
}

char* add_str_func(char a[], char b[], char* (*func_ptr)(char*, char*)) {
	return func_ptr(a, b);
}

int main() {
	int n = 10;
	
	printf("No.1----------\n[");
	int* ip = get_int_array(n);
	for (int i = 0 ; i < n ; i++) {
		set_value(ip+i, i+1);
	}
	print_array(ip, n);
	printf("]\n");
	free(ip);
	
	printf("No.2----------\n");
	array_list_t array;
	array.nn = 10;
	array.get_ptr = get_int_array;
	array.set_ptr = set_value;
	array.print_ptr = print_array;
	int* ipp = array.get_ptr(array.nn);
	for (int i = 0 ; i < array.nn ; i++) {
		array.set_ptr(ipp+i, i+1);
	}
	printf("[");
	array.print_ptr(ipp, array.nn);
	printf("]\n");
	free(ipp);
	
	printf("No.3----------\n");
	char a[] = "IU!IU!";
	char b[] = "@CGU";
	printf("add_str_func = %s\n", add_str_func(a, b, func));
	
	return 0;
}
