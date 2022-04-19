#include <stdio.h>

typedef struct my_mm {
    int id;
    int p[10];
} my_mm_t;
int g_mem[10];
my_mm_t mms;

int *my_calloc(int n, int size) {
    int index = -1;
    for (int i = 0; index < 0 && i < 10; i++) {
        int j = 0;
        for (int m = 0; !j && m < size; m++) {
          if (g_mem[i + m] != 0 || i + m >= 10) j = 1;
    }
    if (!j) index = i;
    }
    if (index >= 0) {
      for (int i = 0; i < size; i++) g_mem[index + i] = mms.id + 1;
      mms.p[mms.id] = n;
      mms.id++;
    }
      for (int i = 0; i < 10; i++) g_mem[i] ? printf("%i", mms.p[g_mem[i] - 1]) : printf("0");
    printf("\n");
    return index >= 0 ? &mms.p[mms.id - 1] : NULL;
}

void my_free(int *p) {
    int index = -1;
    for (int i = 0; index < 0 && i < 10; i++) {
        if (&mms.p[i] == p) index = i;
    }
    for (int i = 0; index >= 0 && i < 10; i++) {
        if (g_mem[i] == index + 1) g_mem[i] = 0;
    }
    for (int i = 0; i < 10; i++) g_mem[i] ? printf("%i", mms.p[g_mem[i] - 1]) : printf("0");
    printf("\n");
}

int main() {
    int *np1 = my_calloc(1, 1);
    int *np2 = my_calloc(1, 2);
    int *np3 = my_calloc(1, 3);
    int *np4 = my_calloc(1, 4);
    my_free(np1);
    my_free(np4);
    int *np5 = my_calloc(1, 3);
    return 0;
}
