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
    for(int i=0; i<n-1; i++)
        for(int j=n-1; j>i; j--)
            if(dsdv[j].DG > dsdv[j-1].DG)
                swap(&dsdv[j], &dsdv[j-1]);
}
DoVat *readFromFile(int *n, float *W){
    FILE *f;
    f=fopen("caibalo2.txt", "r");
    fscanf(f, "%f", W);
    DoVat *dsdv;
    dsdv = (DoVat*)malloc(sizeof(DoVat));
    int i=0;
    while(!feof(f)){
        fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].tenDV);
        dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
        dsdv[i].PA =0;
        i++;
        dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
    }
    *n=i;
    fclose(f);
    return dsdv;
}
void InDV(DoVat *dsdv, int n, float W){
    int i;
    float tongTL=0.0, tongGT=0.0;
    printf("Phuong an CBL2 dung nhanh can\n");
    printf("Trong luong = %-9.2f\n", W);
    printf("|---|------------------|---------|---------|---------|---------|---------|\n");
    printf("|STT|   Ten do vat     |Tr luogn |Gia tri  |Don gia  |So luong |Phuong an|\n");
    printf("|---|------------------|---------|---------|---------|---------|---------|\n");
    for(i=0; i<n; i++){
        printf("|%2d |%-18s|%-9.2f|%-9.2f|%-9.2f|%-9d|%-9d|\n", i+1, dsdv[i].tenDV, dsdv[i].TL,
            dsdv[i].GT, dsdv[i].DG, dsdv[i].SL, dsdv[i].PA);
        tongTL += dsdv[i].PA * dsdv[i].TL;
        tongGT += dsdv[i].PA * dsdv[i].GT;
    }
    printf("Phuong an X: (");
    for(i=0; i<n-1; i++)
        printf("%d, ", dsdv[i].PA);
    printf("%d)\n", dsdv[n-1].PA);
    printf("Tong trong luong = %-9.2f\n", tongTL);
    printf("Tong gia tri = %-9.2f\n", tongGT);
}
void taoNutGoc(float W, float *V, float *TGT, float *GLNTT, float *CT, float DG_Max){
    *V = W;
    *TGT = 0;
    *GLNTT =0;
    *CT = *V * DG_Max;
}
void capNhatGLNTT(float TGT, float *GLNTT, int x[], int n, DoVat *dsdv){
    if(*GLNTT < TGT){
        *GLNTT = TGT;
        for(int i=0; i<n; i++){
            dsdv[i].PA = x[i];
        }
    }
}
int min(int a, int b){
    return a<b?a:b;
}
void nhanhCan(int i, int n, int x[], float *TGT, float *GLNTT, float *CT, float *V, DoVat *dsdv){
    int j;
    int vk = min(*V / dsdv[i].TL, dsdv[i].SL);
    for(j=vk; j>=0; j--){
        *TGT += j*dsdv[i].GT;
        *V -= j*dsdv[i].TL;
        *CT = *TGT + *V * dsdv[i+1].DG;
        if(*CT > *GLNTT){   
            x[i] = j;
            if((i==n-1) || (*V==0)){
                capNhatGLNTT(*TGT, GLNTT, x, n, dsdv);
            }else {
                nhanhCan(i+1, n, x, TGT, GLNTT, CT, V, dsdv);
            }
        }
        x[i]=0;
        *TGT -= j*dsdv[i].GT;
        *V += j*dsdv[i].TL;
    }
}
int main(){
    DoVat *dsdv;
    int n;
    float W, V, TGT, CT, GLNTT;
    dsdv = readFromFile(&n, &W);
    // InDV(dsdv, n, W);
    int x[n];
    bubbleSort(dsdv, n);
    taoNutGoc(W, &V, &TGT, &GLNTT, &CT, dsdv[0].DG);
    nhanhCan(0, n, x, &TGT, &GLNTT, &CT, &V,dsdv);
    InDV(dsdv, n, W);
    free(dsdv);
    
}