#include <stdio.h>

void print(int a[], int n);
void divide(int a[], int left, int right);
void merge(int a[], int left, int mid, int right);

void print(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}

int main()
{
    int n, i;
    printf("\nEnter number of elements:\n");
    scanf("%d", &n);

    int a[n], b[n];
    printf("\nEnter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    divide(a, 0, n - 1);
    print(a, n);
}

// Dividing step
void divide(int a[], int left,  int right) 
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        divide(a, left, mid);
        divide(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

// Overall 'N' ietrations
void merge(int a[], int left, int mid, int right)
{
    int i, j, k, l, head = 0, tail = 0, size;
    int queue[right - left];
    i = left;
    k = i;
    j = mid + 1;

    // Push first element into the queue from first sorted halve.
    queue[tail] = a[i];
    i++;
    tail++;

    // Push the elements into the queue from first sorted array, compare elements of queue and second sorted array and merge them back into the original array.
    while (i <= mid && j <= right) {
        
        queue[tail] = a[i];
        tail++;
        i++;
        if (a[j] <= queue[head]) {
            a[k] = a[j];
            j++;
            k++;
        } else {
            a[k] = queue[head];
            head++;
            k++;
        }
    }

    // If first sorted array is completed, compare elements from queue and second sorted array and menrge them into original array.
    while (head < tail && j <= right) {
        
        if (a[j] <= queue[head]) {
            a[k] = a[j];
            k++;
            j++;
        } else {
            a[k] = queue[head];
            k++;
            head++;
        }
    }

    // If second sorted array is completed, push first sorted array into queue and queue elements into original array.
    while (i <= mid) {
        
        queue[tail] = a[i];
        tail++;
        i++;

        a[k] = queue[head];
        k++;
        head++;
    }

    // Push all elements from second sorted array into queue and push queue elements into original array.
    while (j <= right) {
        
        queue[tail] = a[j];
        tail++;
        j++;

        a[k] = queue[head];
        k++;
        head++;
    }
    
    // Push all queue elements back into original array.
    while (head < tail) {
        
        a[k] = queue[head];
        k++;
        head++;
    }
}