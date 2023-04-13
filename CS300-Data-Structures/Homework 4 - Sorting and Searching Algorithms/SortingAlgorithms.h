#ifndef _SORTINGALGORITHMS_H
#define _SORTINGALGORITHMS_H

#include <vector>

using namespace std;

template <class Comparable>
void insertionSort(vector <Comparable>& vector) {
	int j;

	for (int p = 1;  p < vector.size(); p++) {
		Comparable tmp = vector[p];
                            
		for (j = p; j > 0 &&  tmp < vector[j-1]; j--) {
			vector[j] = vector[j-1];
		}
		vector[j] = tmp;
	}
}

template <class Comparable>
void percDown(vector<Comparable>& vector, int i, int n) {
    int child;
    Comparable tmp;

    for (tmp = vector[i]; 2*i+1 < n; i = child) {
        child = 2*i+1;
        if (child != n-1 && vector[child] < vector[child+1]) {
            child++;
		}

        if (vector[child] > tmp) {
            vector[i] = vector[child];
		}
        else {
            break;
		}
    }

    vector[i] = tmp;
}

template <class Comparable>
void heapsort(vector<Comparable>& vector) {
	for (int i = vector.size()/2; i >=0; i--) {
		percDown(vector, i, vector.size());
	}

	for (int j = vector.size() -1; j >0; j--) {
		swap(vector[0], vector[j]);
		percDown(vector, 0, j);
	}
}

template <class Comparable>
const Comparable& median3(vector<Comparable>& vector, int left, int right)
{
    int center = (left + right) / 2;
    if (vector[center] < vector[left]) {
		swap(vector[left], vector[center]);
	}

    if (vector[right] < vector[left]) {
		swap(vector[left], vector[right]);
	}

    if (vector[right] < vector[center]) {
		swap(vector[center], vector[right]);
	}

    // Place pivot at position right - 1
    swap(vector[center], vector[right - 1]);
    return vector[right - 1];
}

template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right ) {
    for (int p = left + 1; p <= right; p++) {
        Comparable tmp = a[p];
        int j;

        for (j = p; j > left && tmp < a[j - 1]; j--) {
			a[j] = a[j - 1];
		}
        a[j] = tmp;
    }
}

template <class Comparable>
void quicksort(vector<Comparable>& vector, int left, int right)
{
    if (left + 10 <= right) {
		Comparable pivot = median3(vector, left, right);
		// Begin partitioning
		int i = left, j = right - 1;
		for ( ; ; )
		{
			while (vector[++i] < pivot);

			while (pivot < vector[--j]);

			if (i < j) {
				swap(vector[i], vector[j]);
			}
			else {
				break;
			}
		}
		swap(vector[i], vector[right - 1]);	  // Restore pivot
		quicksort(vector, left, i - 1);    // Sort small elements
		quicksort(vector, i + 1, right);   // Sort large elements
	}

	else {  // Do an insertion sort on the subarray
		insertionSort(vector, left, right);
	}
}

template <class Comparable>
void quicksort(vector<Comparable>& vector) {
	quicksort(vector, 0, vector.size()-1);
}

//template <class Comparable>
//void merge( vector<Comparable>& a, vector<Comparable> & tmpArray, int leftPos, int rightPos, int rightEnd )
//{
//    int leftEnd = rightPos - 1;
//    int tmpPos = leftPos;
//    int numElements = rightEnd - leftPos + 1;
//    // Main loop
//    while ( leftPos <= leftEnd && rightPos <= rightEnd )
//            if ( a[ leftPos ] <= a[ rightPos ] )
//                tmpArray[ tmpPos++ ] = a[ leftPos++ ];
//            else
//                tmpArray[ tmpPos++ ] = a[ rightPos++ ];
//
//    while ( leftPos <= leftEnd )    // Copy rest of first half
//        tmpArray[ tmpPos++ ] = a[ leftPos++ ];
//
//    while ( rightPos <= rightEnd )  // Copy rest of right half
//        tmpArray[ tmpPos++ ] = a[ rightPos++ ];
//
//    // Copy tmpArray back
//    for ( int i = 0; i < numElements; i++, rightEnd-- )
//        a[ rightEnd ] = tmpArray[ rightEnd ];
//}
//
//template <class Comparable>
//void mergeSort( vector<Comparable> & a, vector<Comparable> & tmpArray, int left, int right )
//{
//    if ( left < right )
//    {
//        int center = ( left + right ) / 2;
//        mergeSort( a, tmpArray, left, center );
//        mergeSort( a, tmpArray, center + 1, right );
//        merge( a, tmpArray, left, center + 1, right );
//    }
//}
//
//template <class Comparable>
//void mergeSort( vector<Comparable> & a )
//{
//    vector<Comparable> tmpArray( a.size( ) );
//
//    mergeSort( a, tmpArray, 0, a.size( ) - 1 );
//}

template <class Comparable>
void merge(vector<Comparable> &list, int start, int mid, int end)
{
    int start2 = mid + 1;
 
    // If the direct merge is already sorted
    if (list[mid] <= list[start2]) {
        return;
    }
 
    // Two pointers to maintain start
    // of both arrays to merge
    while (start <= mid && start2 <= end) {
 
        // If element 1 is in right place
        if (list[start] <= list[start2]) {
            start++;
        }
        else {
			Comparable value = list[start2];
            int index = start2;
 
            // Shift all the elements between element 1
            // element 2, right by 1.
            while (index != start) {
                list[index] = list[index - 1];
                index--;
            }
            list[start] = value;
 
            // Update all the pointers
            start++;
            mid++;
            start2++;
        }
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
template <class Comparable>
void mergeSort(vector<Comparable> &list, int l, int r)
{
    if (l < r) {
 
        // Same as (l + r) / 2, but avoids overflow
        // for large l and r
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(list, l, m);
        mergeSort(list, m + 1, r);
 
        merge(list, l, m, r);
    }
}

#endif