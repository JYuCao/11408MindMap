
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
                Elemtype temp = A[j];
                A[j] = A[j-1];
                A[j-1] = temp;
                flag = true;
            }
        }
        if (!flag)  return;
    }
}

static int QS_partition(Elemtype A[], int low, int high) {
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
        int pivotpos = QS_partition(A, low, high);
        quickSort(A, low, pivotpos - 1);
        quickSort(A, pivotpos + 1, high);
    }
}

void simpleSelectSort(Elemtype A[], int n)
{
    for (int i = 0; i < n; ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j)
            if (A[j] < A[min])
                min = j;
        if (min != i) {
            Elemtype temp = A[min];
            A[min] = A[i];
            A[i] = temp;
        }
    }
}

static void HS_buildMaxHeap(Elemtype A[], int len)
{
    for (int i = len / 2; i > 0; --i) {
        HS_headAdjust(A, i, len);
    }
}

static void HS_headAdjust(Elemtype A[], int k, int len)
{
    A[0] = A[k];
    for (int i = 2 * k; i <= len; i *= 2) {
        if (i < len && A[i] < A[i+1])
            ++i;
        if (A[0] > A[i])
            break;
        else {
            A[k] = A[i];
            k = i;
        }
    }
    A[k] = A[0];
}

void heapSort(Elemtype A[], int len)
{
    HS_buildMaxHeap(A, len);
    for (int i = len; i > 1; --i) {
        Elemtype temp = A[i];
        A[i] = A[1];
        A[1] = temp;
        HS_headAdjust(A, 1, i-1);
    }
}


void BMS_merge(Elemtype A[], int low, int mid, int high, Elemtype B[])
{
    int i, j, k;
    for (k = low; k <= high; ++k)
        B[k] = A[k];
    for (i = low, j = mid + 1, k = i; i <= mid && j <= high; ++k) 
        if (B[i] <= B[j])
            A[k] = B[i++];
        else   
            A[k] = B[j++];
    while (i <= mid)  A[k++] = B[i++];
    while (j <= high) A[k++] = B[j++];
}

void binaryMergeSort1(Elemtype A[], int low, int high, Elemtype B[]) {
    if (low < high) {
        int mid = (low + high) / 2;
        binaryMergeSort1(A, low, mid, B);
        binaryMergeSort1(A, mid+1, high, B);
        BMS_merge(A, low, mid, high, B);
    }
}

void binaryMergeSort(Elemtype A[], int n) {
    Elemtype *B = new Elemtype[n+1];
    binaryMergeSort1(A, 0, n, B);
    delete B;
}

void countingSort(Elemtype A[], int n)
{   // 假设A中都是非负整数
    Elemtype * B = new Elemtype[n];
    Elemtype * count = new Elemtype[n];

    for (int i = 0; i < n; ++i) 
        ++count[A[i]];
    
    for (int i = 1; i < n; ++i)
        count[i] += count[i-1];

    for (int i = 0; i < n; ++i) {
        B[count[A[i]]-1] = count[i];
        --count[A[i]];
    }
        

    for (int i = 0; i < n; ++i) {
        A[i] = B[i];
    }
    delete B;
    delete count;
}
