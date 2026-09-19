// merge sort
// merge procedure

#include <iostream>
using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int l[n1], r[n2];

    for (int i = 0; i < n1; i++) {
        l[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        r[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (l[i] < r[j]) {
            arr[k++] = l[i++];
        }
        else {
            arr[k++] = r[j++];
        }
    }

    while (i < n1) {
        arr[k++] = l[i++];
    }

    while (j < n2) {
        arr[k++] = r[j++];
    }
}
void mergeSort(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {

    int arr[] = {5, 2, 4, 6, 1, 3};
    int size = sizeof(arr) / sizeof(arr[0]);    

    mergeSort(arr, 0, size - 1);

    for (int value : arr) {
        cout << value << ' ';
    }
    cout << '\n';

    return 0;
}