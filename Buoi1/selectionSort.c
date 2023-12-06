//54
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
void selectionSort(recordtype a[], int n){
    for(int i=0; i<n-1; i++){
        int min = a[i].key;
        int min_idx = i;
        for(int j=i+1; j<n; j++){
            if(a[j].key < min){
                min = a[j].key;
                min_idx = j;
            }
        }
        if(min_idx != i) swap(&a[i], &a[min_idx]);
    }
}
int main(){
    recordtype a[20];
    int n=0;
    freopen("data.txt","r",stdin);
    while(2 == scanf("%d%f",&a[n].key, &a[n].value))
        n++;
    printf("Thuat toan sap xep chon\n");
    printf("Truoc sap xep\n");
    print(a, n);
    selectionSort(a, n);
    printf("Sau sap xep\n");
    print(a, n);
}