#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
    int PA, SL;
    float TL, GT, DG;
    char tenDV[25];
}DoVat;
void swap(DoVat *a, DoVat *b){
    DoVat temp = *a;
    *a=*b;
    *b=temp;
}
void bubbleSort(DoVat *dsdv, int n){
    for(int i=0; i<n-1; i++){
        for(int j=n-1; j>i; j--){
            if(dsdv[j].DG > dsdv[j-1].DG){
                swap(&dsdv[j], &dsdv[j-1]);
            }
        }
    }
}
DoVat *readFromFile(int *n, float *W){
    FILE *f;
    f=fopen("caibalo2.txt","r");
    fscanf(f,"%f",W);
    DoVat *dsdv;
    dsdv=(DoVat*)malloc(sizeof(DoVat));
    int i=0;
    while(!feof(f)){
        fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].tenDV);
        dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
        dsdv[i].PA=0;
        i++;
        dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
    }
    *n=i;
    fclose(f);
    return dsdv;
}
void inDSDV(DoVat *dsdv, int n, float W){
    int i;
    float tongTL=0.0, tongGT=0.0;
    printf("Thuat toan CBL2 dung tham an\n");
    printf("Trong luong cua ba lo = %-9.2f\n",W);
    printf("|---|------------------|---------|---------|---------|---------|---------|\n");
    printf("|STT|   Ten do vat     |Tr luong |Gia tri  |So luong |Don gia  |Phuong an|\n");
    printf("|---|------------------|---------|---------|---------|---------|---------|\n");
    for(i=0; i<n; i++){
        printf("|%2d |%-18s|%-9.2f|%-9.2f|%-9d|%-9.2f|%-9d|\n",i+1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT
            ,dsdv[i].SL, dsdv[i].DG, dsdv[i].PA);
        tongTL += dsdv[i].PA * dsdv[i].TL;
        tongGT += dsdv[i].PA * dsdv[i].GT;
    }
    printf("Phuong an X: (");
    for(i=0; i<n-1; i++){
        printf("%d, ",dsdv[i].PA);
    }
    printf("%d)\n", dsdv[n-1].PA);
    printf("Tong trong luong = %-9.2f\n", tongTL);
    printf("Tong gia tri = %-9.2f\n", tongGT);
}
void Greedy(DoVat *dsdv, int n, float W){
    int i;
    for(i=0; i<n; i++){
        dsdv[i].PA= W/dsdv[i].TL;
        if(dsdv[i].PA > dsdv[i].SL) dsdv[i].PA = dsdv[i].SL;
        W = W-dsdv[i].PA * dsdv[i].TL;
    }
}
int main(){
    int n;
    float W;
    DoVat *dsdv;
    dsdv=readFromFile(&n,&W);
    bubbleSort(dsdv,n);
    Greedy(dsdv,n,W);
    inDSDV(dsdv,n,W);
}