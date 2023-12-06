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
		printf("%d  %d  %f\n", i+1, a[i].key, a[i].value);
}
int findPivot(recordtype a[], int bot, int top){
	int k =bot+1;
	int firstKey = a[bot].key;
	while(k<=top && a[k].key == firstKey){
		k++;
	}
	if(k>top) return -1;
	if(a[k].key > firstKey) return bot;
	return k;
}
int partition(recordtype a[], int bot, int top, int pivot){
	int L = bot;
	int R = top;
	while(L<=R){
		while(a[L].key <= pivot) L++;
		while(a[R].key > pivot) R--;
		if(L<R) swap(&a[L], &a[R]);
	}
	return L;
}
void quickSort(recordtype a[], int bot, int top){
	int pivot;
	int pivot_idx = findPivot(a, bot, top);
	if(pivot_idx != -1){
		pivot = a[pivot_idx].key;
		int k = partition(a, bot, top, pivot);
		quickSort(a, bot, k-1);
		quickSort(a, 0, k-1);
	}
}
int main() {
	recordtype a[100];
	int n = 0;
	freopen("data.txt", "r", stdin);
	while(2 == scanf("%d%f", &a[n].key, &a[n].value))
		n++;
	
	printf("Thuat toan Quick sort bien the\n");
	printf("Truoc khi sap xep\n");
	print(a, n);

	quickSort(a, 0, n-1);
	printf("\nSau khi sap xep\n");
	print(a, n);
}