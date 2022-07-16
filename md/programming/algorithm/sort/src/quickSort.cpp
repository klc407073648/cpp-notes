Paritition1(int A[], int low, int high) {
   int pivot = A[low];
   while (low < high) {
     while (low < high && A[high] >= pivot) {
       --high;
     }
     A[low] = A[high];
     while (low < high && A[low] <= pivot) {
       ++low;
     }
     A[high] = A[low];
   }
   A[low] = pivot;
   return low;
 }

 void QuickSort(int A[], int low, int high) //快排母函数
 {
   if (low < high) {
     int pivot = Paritition1(A, low, high);
     QuickSort(A, low, pivot - 1);
     QuickSort(A, pivot + 1, high);
   }
 }