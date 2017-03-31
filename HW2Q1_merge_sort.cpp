//CS 4343 - HW2 - Q1
#include<iostream>
#include<cmath>
#include<limits>
#include<string>
#include<sstream>
/*FUNCTION DECLARATIONS*/
//function used to print elements of an array
void print_array(int* A, int s, int e, const char* msg = nullptr, bool a_break = true);
//recursive merge sort
void merge_sort(int* A, int p, int r);
//merge
void merge(int* A, int p, int q, int r);
/* GLOBALS */
//constant added to the end of left and right arrays in merge function
const int g_infinity = std::numeric_limits<int>::max();
int main(int argc, char* argv[]) {
	//create array
	int A[] = { 2,4,5,7,1,2,3,6 };
	//print the original array
	print_array(A, 0, 7, "original array");
	//sort the array
	merge_sort(A, 0, 7);
	//print the sorted array
	print_array(A, 0, 7, "after sort");
}
void merge_sort(int* A, int p, int r) {
	//check if the starting index is less than the ending index
	if (p < r) {
		//calculate mid point between start and end indices. store value in q.
		int q = (r + p) / 2;
		/*recursive call to merge_sort using the midpoint as a new ending index*/
		merge_sort(A, p, q);
		/*recursive call to merge_sort using the midpoint + 1 as the new starting index.*/
		merge_sort(A, q + 1, r);
		/*at this point the array is sorted correctly on either side of the midpoint q.
		  call to merge combines the indices on either side of q in the correct, sorted, order.
		*/
		merge(A, p, q, r);
	}
}
void merge(int* A, int p, int q, int r) {
	//calculate the siz of the left array
	int n1 = q - p + 1;
	//calculate the size of the right array
	int n2 = r - q;
	//allocate memory for the left array plus one additional element
	int* L = new int[n1 + 1];
	//allocate memory for the right array plus one additional element
	int* R = new int[n2 + 1];
	//assign infinity to the end of the left and right array
	L[n1] = g_infinity;
	R[n2] = g_infinity;

	//copy values from the start index to n1 into the left array
	for (int i = 0; i < n1; i++)
		L[i] = A[p + i];
	//copy values from the midpoint to n2 into the right array
	for (int i = 0; i < n2; i++)
		R[i] = A[q + i + 1];
	//create variable to increment through left index
	int i = 0;
	//create variable to increment through right index
	int j = 0;

	//loop from the start to end indices
	for (int k = p; k <= r; k++) {
		/*if the value on the left side is less,
		  assign that value then increment the left array,
		  otherwise assign the right array value and increment the right array
		*/
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i++;
		} else {
			A[k] = R[j];
			j++;
		}
	}
	//release memory allocated for the left and right arrays
	delete[] L;
	delete[] R;
}
void print_array(int* A, int s, int e, const char* msg) {
	//check if an additional message was passed to the function then print heading
	if (msg)
		std::cout << "\n\tprint_array(" << s << ", " << e << "): " << msg << "\n\n\t";
	else
		std::cout << "\n\tprint_array(" << s << ", " << e << ")\n\n\t";
	//loop throught the array printing each element separated by commas
	for (int i = s; i <= e - 1; i++)
		std::cout << A[i] << ", ";
	std::cout << A[e] << "\n\n";
}