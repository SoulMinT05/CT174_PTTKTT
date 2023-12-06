//59
#include <stdio.h>
typedef struct {
    int key;
    float value;
}recordtype;
void swap(recordtype *a, recordtype *b){
    recordtype temp = *a;
    *a=*b;
    *b=temp;
}
void print(recordtype a[], int n){
    for(int i=0; i<n; i++)
        printf("%d %d %f\n", i+1, a[i].key, a[i].value);
}
void intertionSort(recordtype a[], int n){
    for(int i=0; i<n; i++){
        int j=i;
        while(j>0 && a[j].key < a[j-1].key){
            swap(&a[j],&a[j-1]);
            j--;
        }
    }
}
int main(){
    recordtype a[20];
    int n=0;
    freopen("data.txt","r",stdin);
    while(2 == scanf("%d%f", &a[n].key, &a[n].value))
        n++;
    printf("Thuat toan sap xep xen\n");
    printf("Truoc sap xep\n");
    print(a, n);
    intertionSort(a, n);
    printf("Sau sap xep\n");
    print(a, n);
}