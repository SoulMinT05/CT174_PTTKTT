#include <stdio.h>
#include <mm_malloc.h>
#include <string.h>

typedef struct {
    char tenTien[25];
    int MG, PA;
}Tien;

Tien *readfromfile(int *n) {
    FILE *f;
    f = fopen("atm.txt", "r");
    Tien *dslt;
    dslt = (Tien*)malloc(sizeof(Tien));
    int i=0;
    while(!feof(f)) {
        fscanf(f, "%d", &dslt[i].MG);
        fgets(dslt[i].tenTien, 25, f);
        dslt[i].tenTien[strlen(dslt[i].tenTien) - 1] = '\0';
        dslt[i].PA = 0;
        i++;
        dslt = (Tien*)realloc(dslt, sizeof(Tien)*(i+1));
    }
    *n=i;
    fclose(f);
    return dslt;
}
void swap(Tien *x, Tien *y) {
    Tien temp;
    temp = *x; 
    *x = *y;
    *y = temp;
}

void bubbleSort(Tien *dslt, int n){
    int i, j;
    for(i=0; i<n-1; i++) {
        for(j=n-1; j>i; j--) {
            if(dslt[j].MG < dslt[j-1].MG) 
                swap(&dslt[j], &dslt[j-1]);
        }
    }
}

void inDS(Tien *dslt, int n, int tiencanrut) {
    int i;
    int tongtientra=0;
    printf("|---|-------------------------|---------|---------|----------|\n");
    printf("|%-3s|%-25s|%-9s|%-9s|%-10s|\n", "STT", "     Loai tien", "Menh gia", "So to", "Thanh tien");
    printf("|---|-------------------------|---------|---------|----------|\n");
    for(i=0; i<n; i++) {
       if(dslt[i].PA > 0) { //tờ tiền nào được dùng mới in
            printf("|%-3d", i+1);
            printf("|%-25s", dslt[i].tenTien);
            printf("|%-9d", dslt[i].MG);
            printf("|%-9d", dslt[i].PA);
            printf("|%-10d|\n", dslt[i].MG * dslt[i].PA);
            tongtientra += dslt[i].MG * dslt[i].PA;
       }
    }
    printf("|---|-------------------------|---------|---------|----------|\n");
    printf("So tien can rut = %d\n", tiencanrut);
    printf("So tien da tra = %d\n", tongtientra);
    printf("So tien con du = %d\n", tiencanrut -tongtientra);
}
void Greedy(Tien *dslt, int n, int tiencanrut) {
    int i=0;
    while(i<n && tiencanrut > 0) {
        dslt[i].PA = tiencanrut / dslt[i].MG;
        tiencanrut = tiencanrut - dslt[i].PA * dslt[i].MG;
        i++;
    }
}

int main() {
    int n, tiencanrut;
    printf("Nhap so tien can rut: ");
    scanf("%d",&tiencanrut);
    Tien *dslt;
    dslt = readfromfile(&n);
    bubbleSort(dslt, n);
    Greedy(dslt, n, tiencanrut);
    inDS(dslt, n, tiencanrut);
    return 0;
}