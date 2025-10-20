
typedef int Elemtype;

void directInsertionSort(Elemtype A[], int n)
{
    int i, j;
    for (i = 2; i < n; ++i) 
        if (A[i] < A[i-1]) {
            A[0] = A[i];
            for (j = i - 1; A[0] < A[j]; --j)
                A[j+1] = A[j]; 
            A[j+1] = A[0];
        }
}

void binaryInsertionSort(Elemtype A[], int n)
{
    int i, j, low, mid, high;
    for (i = 2; i < n; ++i) {
        low = 1;
        high = i - 1;
        A[0] = A[i];
        while (low <= high) {
            mid = (low + high) / 2;
            if (A[mid] > A[0])
                high = mid - 1;
            else low = mid + 1;
        }
        for (j = i - 1; j >= high + 1; --j)
            A[j+1] = A[j];
        A[high+1] = A[0];
    }
}

void shellSort(Elemtype A[], int n)
{
    int dk, j, i;

    for (dk = n / 2; dk >= 1; dk /= 2) 
        for (i = dk + 1; i <= n; ++i) 
            if (A[i] < A[i-dk]) {
                A[0] = A[i];
                for (j = i - dk; j > 0 && A[0] < A[j]; j -= dk) 
                    A[j+dk] = A[j];
                A[j+dk] = 0;
            }
}

void bubbleSort(Elemtype A[], int n)
{
    for (int i = 0; i < n - 1; ++i) {
        bool flag = false;
        for (int j = n - 1; j > i; --j) {
            if (A[j-1] > A[j]) {
                int temp = A[j];
                A[j] = A[j-1];
                A[j-1] = temp;
                flag = true;
            }
        }
        if (!flag)  return;
    }
}

int partition(Elemtype A[], int low, int high) {
    Elemtype pivot = A[low];
    while (low < high) {
        while (low < high && A[high] >= pivot) --high;
        A[low] = A[high];
        while (low < high && A[low <= pivot]) ++low;
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

void quickSort(Elemtype A[], int low, int high)
{
    if (low < high) {
        int pivotpos = partition(A, low, high);
        quickSort(A, low, pivotpos - 1);
        quickSort(A, pivotpos + 1, high);
    }
}
