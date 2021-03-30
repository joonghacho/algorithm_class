#include <chrono>
#include <iostream>
#include <random>

using namespace std;
using namespace std::chrono;
using std::chrono::system_clock;

bool check_sorted(int* arr, int n) {
    for (size_t i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

void print_arr(int* arr, int n) {
    for (size_t i = 0; i < n; i++) {
        if (i) cout << ", ";
        cout << arr[i];
    }
    cout << endl;
}

int* gen_data(int n, int seed = 0) {
    int* arr = new int[n];
    mt19937 rs(seed);
    uniform_int_distribution<int> dist(0, INT32_MAX);

    for (size_t i = 0; i < n; i++) {
        arr[i] = dist(rs);
    }
    return arr;
}

void swap(int* arr, int x, int y) {
	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
	return; 
}

// copy this template and implement your algorihtm
int* insertionSort(int* arr, int n) {
    int* sorted = new int[n];
    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    // implement your algorithm
    for (size_t j = 1; j <= n; j++) {
		int temp = INT32_MAX;
		int index = -1;
	    while (j>0) {
	    	if (sorted[j] < sorted[j-1]) {
	    		swap(sorted, j-1, j);
	    		j--;
			} else {
	    		break;
			}
		}
	}
    return sorted;
}

void merge(int* sorted, int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;
	
	int L[n1], M[n2];
	
	for (int i = 0; i < n1; i++) {
		L[i] = sorted[p + i];
	}
	for (int j = 0; j < n2; j++) {
		M[j] = sorted[q + 1 + j];
	}
	
	int i, j, k;
	i = 0;
	j = 0;
	k = p;
	
	while (i < n1 && j < n2) {
		if (L[i] <= M[j]) {
			sorted[k] = L[i];
			i++;
		} else {
			sorted[k] = M[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		sorted[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		sorted[k] = M[j];
		j++;
		k++;
	}
}

void mergeSortRecursive(int* sorted, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		
		mergeSortRecursive(sorted, l, m);
		mergeSortRecursive(sorted, m + 1, r);
		
		merge(sorted, l, m, r);
	}
}

int* mergeSort(int* arr, int n) {
    int* sorted = new int[n];
    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    // implement your algorithm
    mergeSortRecursive(sorted, 0, n-1);

    return sorted;
}

int partitionRandomPivot(int* sorted, int low, int high) {
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<int> distribution(low, high);
	int randomInt = distribution(generator);
	int pivot = sorted[randomInt];
	int i = (low - 1);
	
	for (int j = low; j <= high; j++) {
		printf("i : %d j : %d low : %d high : %d\n ", i,j,low,high);
		if (j == randomInt){
			continue;
		}
		if (sorted[j] <= pivot) {
			i++;
			if (i == randomInt){
				randomInt++;
			}
			swap(sorted, i, j);
		}
	}
	swap(sorted, i + 1, randomInt);
	return (i + 1);
}

int* quickSortRandomPivotRecursive(int* sorted, int low, int high) {
	if (low < high) {
		int pivotPoint = partitionRandomPivot(sorted, low, high);
		quickSortRandomPivotRecursive(sorted, low, pivotPoint - 1);
		quickSortRandomPivotRecursive(sorted, pivotPoint + 1, high);
	}
}

int* quickSortRandomPivot(int* arr, int n) {
    int* sorted = new int[n];
    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    // implement your algorithm
    quickSortRandomPivotRecursive(sorted, 0, n-1);

    return sorted;
}

int partitionLastPivot(int* sorted, int low, int high) {
	int pivot = sorted[high];
	int i = (low - 1);
	
	for (int j = low; j < high; j++) {
		if (sorted[j] <= pivot) {
			i++;
			swap(sorted, i, j);
		}
	}
	swap(sorted, i + 1, high);
	return (i + 1);
}

int* quickSortLastPivotRecursive(int* sorted, int low, int high) {
	if (low < high) {
		int pivotPoint = partitionLastPivot(sorted, low, high);
		quickSortLastPivotRecursive(sorted, low, pivotPoint - 1);
		quickSortLastPivotRecursive(sorted, pivotPoint + 1, high);
	}
}

int* quickSortLastPivot(int* arr, int n) {
    int* sorted = new int[n];
    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    // implement your algorithm
    quickSortLastPivotRecursive(sorted, 0, n-1);

    return sorted;
}

int main(void) {
    system_clock::time_point begin;
    double duration;
    bool is_sorted;
    int* arr;
    int n;

    // example of gen_data
    arr = gen_data(10);
    cout << "Example: ";
    print_arr(arr, 10);
    delete[] arr;

    n = 10;
    begin = system_clock::now();
    arr = gen_data(n);
    duration = duration_cast<milliseconds>(system_clock::now() - begin).count() / 1000.0;
    cout << "Time for gen data: " << duration << "s" << endl;

    begin = system_clock::now();
    int* sorted = insertionSort(arr, n);
    duration = duration_cast<milliseconds>(system_clock::now() - begin).count() / 1000.0;
    cout << "Time for insertion sort: " << duration << "s" << endl;

    is_sorted = check_sorted(sorted, n);
    cout << "Sorted(1: true, 0:false): " << check_sorted(sorted, n) << endl;
    if (!is_sorted) {
        cout << "Try the implementation again" << endl;
    }
    delete[] sorted;
    
    begin = system_clock::now();
    sorted = mergeSort(arr, n);
    duration = duration_cast<milliseconds>(system_clock::now() - begin).count() / 1000.0;
    cout << "Time for merge sort: " << duration << "s" << endl;

    is_sorted = check_sorted(sorted, n);
    cout << "Sorted(1: true, 0:false): " << check_sorted(sorted, n) << endl;
    if (!is_sorted) {
        cout << "Try the implementation again" << endl;
    }
    delete[] sorted;
    
    begin = system_clock::now();
    sorted = quickSortRandomPivot(arr, n);
    duration = duration_cast<milliseconds>(system_clock::now() - begin).count() / 1000.0;
    cout << "Time for randomized pivot quick sort: " << duration << "s" << endl;

    is_sorted = check_sorted(sorted, n);
    
    for(int i=0;i<n;i++) printf("%d ", sorted[i]);
    printf("\n");
    
    
    cout << "Sorted(1: true, 0:false): " << check_sorted(sorted, n) << endl;
    if (!is_sorted) {
        cout << "Try the implementation again" << endl;
    }
    delete[] sorted;
    
    begin = system_clock::now();
    sorted = quickSortLastPivot(arr, n);
    duration = duration_cast<milliseconds>(system_clock::now() - begin).count() / 1000.0;
    cout << "Time for last element pivot quick sort: " << duration << "s" << endl;

    is_sorted = check_sorted(sorted, n);
    cout << "Sorted(1: true, 0:false): " << check_sorted(sorted, n) << endl;
    if (!is_sorted) {
        cout << "Try the implementation again" << endl;
    }
    delete[] sorted;
    

    delete[] arr;
    return 0;
}
