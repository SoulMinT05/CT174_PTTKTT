//27
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int PA;
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
            if(dsdv[j].DG > dsdv[j-1].DG)
                swap(&dsdv[j], &dsdv[j-1]);
        }
    }
}
DoVat *readFromFile(int *n, float *W){
    FILE *f;
    f=fopen("caibalo1.txt","r");
    fscanf(f, "%f", W);
    DoVat *dsdv;
    dsdv = (DoVat*)malloc(sizeof(DoVat));
    int i=0;
    while(!feof(f)){
        fscanf(f, "%f%f%[^\n]",&dsdv[i].TL, &dsdv[i].GT, &dsdv[i].tenDV);
        dsdv[i].DG = dsdv[i].GT /dsdv[i].TL;
        dsdv[i].PA=0;
        i++;
        dsdv =(DoVat*)realloc(dsdv,sizeof(DoVat)*(i+1));
    }
    *n=i;
    fclose(f);
    return dsdv;
}
void inDSDV(DoVat *dsdv, int n, float W){
    int i;
    float tongTL=0.0, tongGT=0.0;
    printf("Phuong an CBl1 dung nhanh can\n");
    printf("Trong luong = %-9.2f\n", W);
    printf("|---|------------------|---------|---------|---------|---------|\n");
    printf("|STT|   Ten do vat     |Tr luong |Gia tri  |Don gia  |Phuong an|\n");
    printf("|---|------------------|---------|---------|---------|---------|\n");
    for(i=0; i<n; i++){
        printf("|%2d |%-18s|%-9.2f|%-9.2f|%-9.2f|%-9d|\n",i+1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG,
            dsdv[i].PA);
        tongTL += dsdv[i].PA *dsdv[i].TL;
        tongGT += dsdv[i].PA * dsdv[i].GT;
    }
    printf("Phuong an X (");
    for(i=0; i<n-1; i++)
        printf("%d, ", dsdv[i].PA);
    printf("%d)\n", dsdv[n-1].PA);
    printf("Tong trong luong = %-9.2f\n", tongTL);
    printf("Tong gia tri = %-9.2f\n", tongGT);
}
void taoNutGoc(float W, float *V, float *TGT, float *CT, float *GLNTT, float DG_Max){
    *V=W;
    *TGT=0;
    *GLNTT=0;
    *CT = *V * DG_Max;
}
void capNhatPA(float TGT, float *GLNTT, int n, int x[], DoVat *dsdv){
    if(*GLNTT < TGT){
        *GLNTT = TGT;
        for(int i=0; i<n; i++) 
            dsdv[i].PA=x[i];
    }
}
void nhanhCan(int i, int n, int x[], float *TGT, float *CT, float *GLNTT, float *V, DoVat *dsdv){
    int j;
    int vk = *V/dsdv[i].TL;
    for(j=vk; j>=0; j--){
        *TGT += j*dsdv[i].GT;
        *V -= j*dsdv[i].TL;
        *CT = *TGT + *V * dsdv[i+1].DG;
        if(*CT > *GLNTT){
            x[i]=j;
            if((i==n-1) || (*V==0))
                capNhatPA(*TGT, GLNTT, n, x, dsdv);
            else    
                nhanhCan(i+1, n, x, TGT, CT, GLNTT, V , dsdv);
        }
        x[i]=0;
        *TGT -= j*dsdv[i].GT;
        *V += j*dsdv[i].TL;
    }
}
int main(){
    DoVat *dsdv;
    int n;
    float W,V,TGT,GLNTT,CT;
    dsdv=readFromFile(&n,&W);
    int x[n];
    bubbleSort(dsdv, n);
    taoNutGoc(W, &V, &TGT, &CT, &GLNTT, dsdv[0].DG);
    nhanhCan(0, n, x, &TGT, &CT, &GLNTT, &V, dsdv);
    inDSDV(dsdv, n, W);
}