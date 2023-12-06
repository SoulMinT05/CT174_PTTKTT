//51
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
void bubbleSort(recordtype a[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=n-1; j>i; j--){
            if(a[j].key < a[j-1].key)
                swap(&a[j], &a[j-1]);
        }
    }
}
int main(){
    recordtype a[20];
    int n=0;
    freopen("data.txt","r",stdin);
    while(2 == scanf("%d%f", &a[n].key, &a[n].value))
        n++;
    printf("Thuat toan sap xep noi bot\n");
    printf("Truoc sap xep\n");
    print(a, n);
    bubbleSort(a, n);
    printf("Sau sap xep\n");
    print(a, n);
}