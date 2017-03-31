//CS 4343 - HW5 - Q1 - Justin Lye

#include<iostream>
#include<stdexcept>
#include<limits>
#include<string>

namespace ds {
	//Simple array class
	template<typename T>
	class Array {
	public:
		//constructor: allocates space from array of init_length
		Array(int init_length) : _length(init_length), _array(nullptr) { _array = new T[_length]; }
		//constructor: accepts initialization list
		Array(std::initializer_list<T> l) : _length(l.size()) {
			_array = new T[_length];
			int count = 0;
			for (auto i = l.begin(); i != l.end(); ++i) {
				_array[count] = *i;
				count++;
			}
		}
		//destructor: release memory
		~Array() { delete[] _array; }
		//getter: returns length of array
		inline int length() const { return _length; }
		//getter: return maximum value found in array in O(n) time
		inline T Max() const {
			T result = _array[0];
			for (int i = 1; i < _length; i++) {
				if(result < _array[i])
					result = _array[i];
			}
			return result;
		}

		//resets array to array_length. All existing elements are lost
		inline void resize(int array_length) {
			if (_array != nullptr) {
				delete[] _array;
			}
			_array = new T[array_length];
			_length = array_length;
		}
		//fill array with some constant value. All existing elements are replaced
		inline void fill(const T& val) { for (int i = 0; i < _length; i++) { _array[i] = val; } }
		//operator: random access operator
		inline T& operator[](int idx) { if (idx >= 0 && idx < _length) { return _array[idx]; } else { std::string msg = std::string("Index out of bounds ") + std::to_string(idx); throw std::runtime_error(msg.c_str()); }}
		//operator: standard output operator
		friend inline std::ostream& operator<<(std::ostream& s, const Array& a) {
			a.print(s);
			return s;
		}
	protected:
		//member: stores current length of array
		int _length;
		//base pointer to array
		int* _array;
		//method to print array to given output s
		void print(std::ostream& s) const {
			std::cout << "[";
			for (int i = 0; i < _length - 1; i++) {
				std::cout << _array[i] << ',';
			}
			std::cout << _array[_length-1] << "]";
		}
	private:
		int_array() {}
		int_array(const Array& a) {}
		int_array(Array&& a) {}
	};
}

//declaration of COUNTING-SORT implementation
template<typename T>
void CountingSort(ds::Array<T>& A, ds::Array<T>&B, T k = std::numeric_limits<T>::min());

int main(int argc, char* argv[]) {
	ds::Array<int> A = { 6,0,2,0,1,3,4,6,1,3,2 }; //default array to sort

	if (argc > 1) { //command line arguments are assumed to be an array to sort
		A.resize(argc-1);
		for (int i = 0; i < (argc - 1); i++) {
			A[i] = std::atoi(argv[i+1]);
		}
	}
	//allocate storge for sorted array
	ds::Array<int> B(A.length());
	//print unsorted array
	std::cout << "Array before sort:\n\n" << A << "\n\n";
	//sort array
	CountingSort<int>(A,B);
	//print sorted array
	std::cout << "Array after sort:\n\n" << B << "\n\n";
	return 0;
}

//COUNTING-SORT implementation
template<typename T>
void CountingSort(ds::Array<T>& A, ds::Array<T>&B, T k) {
	//if k argument is not passed then find maximum
	if (k <= std::numeric_limits<T>::min()) {
		k = A.Max();
	}
	//allocate storage for sorted array and fill with zeros
	B.resize(A.length());
	B.fill(0);
	//allocate storage for working array and fill with zeros
	ds::Array<T> C(k+1);
	C.fill(0);
	//subtract one from count to handle zero based array indexing
	C[0] = -1; 
	
	//count occurances of each element in array A
	for (int i = 0; i < A.length(); i++) {		
		C[A[i]] = C[A[i]]+1;
	}
	//accumulate totals
	for (int i = 1; i < C.length(); i++) {
		C[i] = C[i - 1] + C[i];
	}
	//fill sorted array per accumulated totals in working array
	for (int i = A.length() - 1; i >= 0; i--) {
		B[C[A[i]]] = A[i];
		C[A[i]] = C[A[i]] - 1;
	}
}
