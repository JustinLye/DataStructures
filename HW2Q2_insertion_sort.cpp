#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

//sort a given array using insertion sort implementation
void insertion_sort(int* A, int length);
void print_step(int* A, int length, int key, int j, int i, bool in_loop = true);
void print_array(int* A, int length);
void print_step1(int* A, int key,int length, int j,int i);
void print_step2(int* A, int key, int length, int j, int i);
const char* page_break = "\n--------------------------------\n";
std::ofstream out_file;

int main(int argc, char* argv[]) {
	int A[] = { 5,3,8,2,10,7 };
	int length = sizeof(A) / sizeof(A[0]);
	out_file.open("output.txt");
	out_file << "CS 4343 - HW2 - Q2\n\nUnsorted array:\n";
	print_array(A,length);
	out_file << "\n\n";
	insertion_sort(A, length);
	out_file << page_break << '\n';
	out_file << "sorted array:\n";
	print_array(A, length);
	out_file.close();
	return 0;
}

void print_step1(int* A, int key,int length, int j, int i) {
	out_file << page_break;
	print_array(A, length);
	out_file << "\nj = " << j << '\n' << "key = " << key << '\n' << "i = " << i << '\n';
	out_file << '\n';
	if (A[i] < key) {
		out_file << "A[" << i << "] < " << key << " so A[" << i + 1 << "] = " << key << '\n';
	}
}

void print_step2(int* A, int key, int length, int j, int i) {
	if (i > -1) {
		out_file << "A[" << i << "] < " << key << " so " << "A[" << i + 1 << "] = " << key << '\n';
	} else {
		out_file << "i <= -1 so " << "A[" << i + 1 << "] = " << key << '\n';
	}
}

void insertion_sort(int* A, int length) {
	//initialize key to zero
	int key = 0;
	int i = 0;
	//loop through entire lenght of array
	for (int j = 1; j < length; j++) {
		//set key to the leading index
		key = A[j];
		//set i to the leading index - 1
		i = j - 1;
		//for each index ahead of j, push back all values greater than key
		print_step1(A, key, length, j, i);
		while (i > -1 && A[i] > key) {
			print_step(A, length, key, j, i);
			A[i + 1] = A[i];
			out_file << "updated array:\n";
			print_array(A, length);
			out_file << '\n';
			out_file << "i = i - 1 = " << i << " - 1 = " << i - 1 << '\n';
			i = i - 1;
		}
		if (i != j - 1) {
			print_step2(A, key, length, j, i);
		}
		//insert the key element in the correct slot, which is either the beginning of the array or at the index where key is greater than the index directly ahead of it
		A[i + 1] = key;
		
		out_file << "updated array:\n";
		print_array(A, length);
		out_file << '\n';
		
	}
}

void print_step(int* A, int length, int key, int j, int i, bool in_loop) {
	out_file << "A[" << i << "] > " << key << " so A[" << i + 1 << "] = A[" << i << "]\n";
	out_file << "A[" << i + 1 << "] = " << A[i] << '\n';
}

void print_array(int* A, int length) {
	out_file << "A=[";
	for (int i = 0; i < length - 1; i++) {
		out_file << A[i] << ",";
	}
	out_file << A[length - 1] << "] ";
}
