#include <iostream>

using namespace std;

void qsort(int *array, int size) {
	if (size <= 1)return;
	int head = 0, tail = size - 1;
	int mid = array[size / 2];
	while (head <= tail) {
		while (array[head] < mid)head++;
		while (array[tail] > mid)tail--;
		if (head <= tail) {
			int temp = array[head];
			array[head] = array[tail];
			array[tail] = temp;
			head++;
			tail--;
		}
	}
	qsort(array,tail+1);
	qsort(array+head,size-head);
}

int main() {
	int arr[9] = {65, 70, 75, 80, 85, 60, 55, 50, 45};
	qsort(arr, 9);
	for (int i = 0; i < 9; ++i)
		cout << arr[i] << " ";
	return 0;
}
