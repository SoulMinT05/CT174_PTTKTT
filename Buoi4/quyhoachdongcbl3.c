//18
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
    int PA, TL, GT;
    char tenDV[25];
}DoVat;
DoVat *readFromFile(int *n, int *W){
    FILE *f;
    f=fopen("caibalo1.txt", "r");
    fscanf(f, "%d", W);
    DoVat *dsdv;
    dsdv=(DoVat*)malloc(sizeof(DoVat));
    int i=0;
    while(!feof(f)){
        fscanf(f, "%d%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].tenDV);
        dsdv[i].PA = 0;
        i++;
        dsdv= (DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
    }
    *n=i; 
    fclose(f);
    return dsdv;
}
void inDSDV(DoVat *dsdv, int n, int W){
    int i;
    int tongTL=0.0, tongGT=0.0;
    printf("Phuong an CBL3 dung QHD\n");
    printf("Trong luong = %-9d\n", W);
    printf("|---|------------------|---------|---------|---------|\n");
    printf("|STT|   Ten do vat     |Tr luong |Gia tri  |Phuong an|\n");
    printf("|---|------------------|---------|---------|---------|\n");
    for(i=0; i<n; i++){
        printf("|%2d |%-18s|%-9d|%-9d|%-9d|\n",i+1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].PA);
        tongTL += dsdv[i].PA * dsdv[i].TL;
        tongGT += dsdv[i].PA * dsdv[i].GT;
    }
    printf("Tong trong luong = %-9d\n", tongTL);
    printf("Tong gia tri = %-9d\n", tongGT);
}
typedef int bang[100][100];
int min(int a, int b){
    return a<b?a:b;
}
void taoBang(int n, int W, bang F, bang X, DoVat *dsdv){
    int xk, yk, k;
    int XMax, FMax, V;
    for(V=0; V<=W; V++){
        X[0][V] = V/dsdv[0].TL;
        F[0][V] = X[0][V] * dsdv[0].GT;
    }
    for(k=1; k<n; k++){
        for(V=0; V<=W; V++){
            XMax = 0;
            FMax = F[k-1][V];
            yk = min(1, V/dsdv[k].TL); // quen hoai
            for(xk=1; xk<=yk; xk++){
                if(F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT > FMax){
                    FMax = F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT;
                    XMax = xk;
                }
            }
            X[k][V] = XMax;
            F[k][V] = FMax;
        }
    }
}
void inBang(int n, int W, bang F, bang X){
    int k, V;
    for(k=0; k<n;k++){
        for(V=0; V<=W; V++){
            printf("|%2d%4d",F[k][V], X[k][V]);
        }
        printf("\n");
    }
}
void traBang(int n, int W, bang X, DoVat *dsdv){
    int V, k;
    V=W;
    for(k=n-1; k>=0; k--){
        dsdv[k].PA = X[k][V];
        V = V - X[k][V] * dsdv[k].TL;
    }
}
int main(){
    DoVat *dsdv;
    int n, W;
    bang F, X;
    dsdv=readFromFile(&n, &W);
    taoBang(n, W, F, X, dsdv);
    inBang(n, W, F, X);
    printf("\n");
    traBang(n, W, X, dsdv);
    inDSDV(dsdv, n, W);
}