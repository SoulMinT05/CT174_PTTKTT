//04
#include <stdio.h>
typedef struct {
    int dau, cuoi;
    float do_dai;
}canh;
void readFromFile(canh a[], int *n){
    int i,j,t;
    float temp;
    FILE *f;
    f=fopen("tsp.txt","r");
    fscanf(f,"%d",n);
    int k=0;
    for(i=0; i<*n; i++){
        for(j=i; j<*n; j++){
            if(i==j){
                for(t=0; t<=j; t++)
                    fscanf(f, "%f", &temp);
            }else {
                fscanf(f, "%f", &a[k].do_dai);
                a[k].dau = i;
                a[k].cuoi=j;
                k++;
            }
                
        }
    }
    fclose(f);
}
void inDScanh(canh a[], int n, int la_PA){
    int i;
    float tong=0.0;
    for(i=0; i<n; i++){
        printf("%3d %c%c = %5.2f\n", i+1, a[i].dau+97,a[i].cuoi+97,a[i].do_dai);
        if(la_PA)
            tong += a[i].do_dai;
    }
    if(la_PA)
        printf("Tong do dai = %5.2f\n", tong);
}
void swap(canh *a, canh *b){
    canh temp = *a;
    *a=*b;
    *b=temp;
}
void bubbleSort(canh a[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=n-1; j>i; j--){
            if(a[j].do_dai < a[j-1].do_dai)
                swap(&a[j],&a[j-1]);
        }
    }
}
int dinhCap3(canh a[], int k, canh moi){
    int i, dem;
    i=0;
    dem=1;
    while(i<k && dem<3){
        if(moi.dau == a[i].dau || moi.dau == a[i].cuoi)
            dem++;
        i++;
    }
    return dem==3;
    i=0;
    dem=1;
    while(i<k && dem<3){
        if(moi.cuoi == a[i].dau || moi.cuoi == a[i].cuoi)
            dem++;
        i++;
    }
    return dem==3;
}
void init_forest(int parent[], int n){
    for(int i=0; i<n; i++)
        parent[i] = i;
}
int find_root(int parent[], int u){
    while(u!=parent[u])
        u=parent[u];
    return u;
}
int chuTrinh(int r_dau, int r_cuoi){
    return r_dau==r_cuoi;
}
void update_forest(int parent[], int r1, int r2){
    parent[r2]=r1;
}
void Greedy(canh a[], int n, canh PA[]){
    int i,j;
    int parent[n];
    init_forest(parent, n);
    j=0;
    int r_dau, r_cuoi;
    for(i=0; i<n*(n-1)/2 && j<n-1; i++){
        r_dau = find_root(parent, a[i].dau);
        r_cuoi = find_root(parent, a[i].cuoi);
        if(!dinhCap3(PA, j, a[i]) && !chuTrinh(r_dau, r_cuoi)){
            PA[j]= a[i];
            j++;
            update_forest(parent, r_dau, r_cuoi);
        }
    }
    for(; i<n*(n-1)/2; i++){
        r_dau = find_root(parent, a[i].dau);
        r_cuoi = find_root(parent, a[i].cuoi);
        if(!dinhCap3(PA, n-1, a[i]) && chuTrinh(r_dau, r_cuoi)){
            PA[n-1]= a[i];
            break;
        }
    }
}

int main(){
    canh a[30];
    int n;
    readFromFile(a, &n);
    printf("Phuong an TSP dung tham an\n");
    printf("Danh sach cac canh cua dt\n");
    inDScanh(a, n*(n-1)/2, 0);

    bubbleSort(a, n*(n-1)/2);
    printf("Danh sach cac canh cua dt da sap xep\n");
    inDScanh(a, n*(n-1)/2, 0);

    canh PA[n];
    Greedy(a, n, PA);
    printf("Phuong an\n");
    inDScanh(PA, n, 1);
}