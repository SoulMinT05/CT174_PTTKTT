//24
#include <stdio.h>
#include <limits.h>
#define size 30

typedef struct {
    int dau, cuoi, da_dung;
    float do_dai;
}canh;
void readFromFile(canh a[][size], int *n){
    int i,j;
    FILE *f;
    f=fopen("tsp.txt","r");
    fscanf(f, "%d", n);
    for(i=0; i<*n; i++){
        for(j=0; j<*n; j++){
            fscanf(f,"%f",&a[i][j].do_dai);
            a[i][j].dau = i;
            a[i][j].cuoi = j;
            a[i][j].da_dung=0;
        }
    }
    fclose(f);
}
void inMT(canh a[][size], int n){
    printf("Ma tran\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("  %c%c = %5.2f",a[i][j].dau+97, a[i][j].cuoi+97,a[i][j].do_dai);
        }
        printf("\n");
    }
}
void inPA(canh a[], int n){
    int i;
    float tong=0.0;
    printf("Phuong an\n");
    for(i=0; i<n; i++){
        tong += a[i].do_dai;
        printf("Canh %c%c = %5.2f\n", a[i].dau+97, a[i].cuoi+97,a[i].do_dai);
    }
    printf("Chu trinh: ");
    for(i=0; i<n; i++){
        printf("%c", a[i].dau+97);
        printf("-> ");
    }
    printf("%c\n", a[0].dau+97);
    printf("Tong do dai = %5.2f\n", tong);
}
float canhNN(canh a[][size], int n){
    float Cmin = INT_MAX;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i!=j && !a[i][j].da_dung && a[i][j].do_dai < Cmin)
                Cmin = a[i][j].do_dai;
        }
    }
    return Cmin;
}
float canDuoi(canh a[][size], int n, int i, float TGT){
    return TGT + (n-i)*canhNN(a, n);
}
void capNhatPA(canh a[][size], canh x[], canh PA[], int n, float TGT, float *GNNTT){
    int i;
    x[n-1] = a[x[n-2].cuoi][x[0].dau];
    TGT += x[n-1].do_dai;
    if(*GNNTT > TGT){
        *GNNTT = TGT;
        for(i=0; i<n; i++)
            PA[i] = x[i]; 
    }
}
int chuTrinh(canh x[], int k, int ketiep){
    int i=0, coCT=0;
    while(i<k && !coCT)
        if(x[i].dau == ketiep) coCT=1;
        else i++;
    return coCT;
}
void reset(canh a[][size], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            a[i][j].da_dung=0;
        }
    }
}
void nhanhCan(int i, int n, int dau, canh a[][size], canh x[], canh PA[], float *TGT, float *CD, float *GNNTT){
    int j;
    for(j=0; j<n; j++){
        if(dau !=j && !a[i][j].da_dung && !chuTrinh(x, i, j)){
            *TGT += a[i][j].do_dai;
            *CD = canDuoi(a, n, i+1, *TGT);
            if(*CD < *GNNTT){
                x[i] = a[dau][j];
                a[dau][j].da_dung=1;
                a[j][dau].da_dung=1;
                if(i==n-2)
                    capNhatPA(a, x, PA, n, *TGT, GNNTT);
                else   
                    nhanhCan(i+1, n, j, a, x, PA, TGT, CD, GNNTT);
            }
        }
         *TGT -= a[i][j].do_dai;
        a[dau][j].da_dung=0;
        a[j][dau].da_dung=0;
    }
}
int main(){
    canh a[size][size];
    int n;
    readFromFile(a, &n);
    canh x[n], PA[n];
    char tpxp, yn;
    while(1){
        fflush(stdin);
        inMT(a, n);
        float TGT=0.0, CD=0.0, GNNTT=INT_MAX;
        printf("Xuat phat tu tp nao: \n");
        printf("Chon 1 trong cac tp tu a den %c: ", n-1+97);
        scanf("%c",&tpxp);
        nhanhCan(0, n, tpxp-97, a, x, PA, &TGT, &CD, &GNNTT);
        inPA(PA, n);
        fflush(stdin);
        printf("Tiep tuc Y/N:  ");
        scanf("%c", &yn);
        if(yn=='N' || yn=='n') break;
        reset(a, n);
    }
}