#include<stdio.h>

typedef struct my_mm
{
    int nm[10];
    int* nm_p[10];
    int count;
}my_mm_t;

my_mm_t mms;
int g_mem[10];

void mms_detect()
{
    for(int i=0;i<10;i++)
    {
        if(g_mem[i]!=0) mms.nm[i]=1;
        else mms.nm[i]=0;
        printf("%d",mms.nm[i]);
    }    
}

int* my_calloc(int n,int size)
{
    mms.count++;
    int np=0;
    for(int i=0;i<10;i++)
    {
        if(g_mem[i]==0) np++;
        else np=0;
        if(np>=n*size)
        {
            for(int j=i-np+1;j<i+1;j++)
            {
                g_mem[j] = mms.count;
            }            
            mms_detect();
            printf("\n");
            return &g_mem[i];
        }
    }
    mms_detect();
    printf("<-Out of space\n");
    return NULL;
}

int* findAddress(int* n,int num){
    int count = 0;
    while(*n!=num)
    {
        n++;
        count++;
        if(count > 10) return 0;
    }
    return n;
}

void my_free(int* p)
{                
    int count = 0;
    while(findAddress(g_mem,*p)&&count<10)
    {
        int *n = findAddress(g_mem,*p);
        *n = 0;
        count++;
    }
    mms_detect();
    printf("\n");
}
    
int main()
{
    int* p1 = my_calloc(1,1);
    int* p2 = my_calloc(1,2);
    int* p3 = my_calloc(1,3);
    int* p4 = my_calloc(1,4);    
    my_free(p1);
    my_free(p4);
    int* p5 = my_calloc(1,5);
    int* p6 = my_calloc(1,1);
}
