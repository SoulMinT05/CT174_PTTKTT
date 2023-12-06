//27
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
        printf("%d %d %f\n",i+1, a[i].key, a[i].value);
}
void pushDown(recordtype a[], int first, int last){
    int r = first;
    while(r <= (last-1)/2){
        if(last == (2*r)+1){
            if(a[r].key > a[last].key)
                swap(&a[r], &a[last]);
            r = last;
        }else if(a[r].key > a[2*r+1].key && a[2*r+1].key <= a[2*r+2].key){
            swap(&a[r], &a[2*r+1]);
            r = 2*r+1;
        }else if(a[r].key > a[2*r+2].key){
            swap(&a[r], &a[2*r+2]);
            r = 2*r+2;
        }else r = last;
    }
}
void heapSort(recordtype a[], int n){
    for(int i=(n-2)/2; i>=0; i--)
        pushDown(a, i, n-1);
    for(int i=n-1; i>=2; i--){
        swap(&a[0], &a[i]);
        pushDown(a, 0, i-1);
    }
    swap(&a[0], &a[1]);
}
int main(){
    freopen("data.txt","r",stdin);
    recordtype a[20];
    int n=0;
    while(2 == scanf("%d%f",&a[n].key, &a[n].value))
        n++;
    printf("Thuat toan Heap sort giam dan\n");
    printf("Truoc khi sap xep\n");
    print(a, n);
    heapSort(a, n);
    printf("Sau khi sap xep\n");
    print(a, n);
}