#include <stdio.h>

static int count;

int* findAddress(int num, int* n){
    count = 0;
    while(*n != num){
        n++;
        count++;
        if(count>10)return 0;
    }
    return n;
}


int main()
{
    int n[] = {6,4,7,12,0,11,8,1,5,3};
    int* p;
    int num1 = 11;
    p = findAddress(num1, n);
    printf("No.1-----------------\n");
    printf("&n[%d] -> %p, n[%d] = %d; p -> %p, *p = %d\n", count, &n[count], count, n[count], p, *p);
    printf("No.2-----------------\n");
    int* ap[10];
    int i = 0, b = 0;
    while(i < 10){
        if(findAddress(b, n)){
            ap[i] = findAddress(b, n);
            printf("&n[%d] -> %p, n[%d] = %d; ap[%d] -> %p, *ap[%d] = %d\n", count, &n[count], count, n[count], i, ap[i], i, *ap[i]);
            i++;
            b++;
        }    
        else b++;  
    }    
}
