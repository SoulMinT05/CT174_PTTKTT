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
    int i;
    for(i=0; i<n; i++)
        printf("%d %d %f\n", i+1, a[i].key, a[i].value);
}
void selectionSort(recordtype a[], int n){
    for(int i=0; i<n-1; i++){
        int min_idx = i;
        int min = a[i].key;
        
        for(int j=i+1; j<n; j++){
            if(a[j].key < min){
                min_idx = j;
                min = a[j].key;
            }
        }
        if(min_idx !=i ){
            swap(&a[min_idx], &a[i]);
        }
    }
}
int main(){
    recordtype a[20];
    freopen("data.txt","r",stdin);
    int n = 0;
    while(2 == scanf("%d%f", &a[n].key, &a[n].value))
        n++;
    printf("Thuat toan sap xep chon\n");
    printf("Truoc khi sap xep\n");
    print(a,n);
    selectionSort(a,n);
    printf("Sau khi sap xep\n");
    print(a,n);
}