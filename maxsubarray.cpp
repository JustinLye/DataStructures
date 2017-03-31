//CS 4343 - HW4 - Q1 - Justin Lye
#include<iostream>
#include<cmath>

namespace ds {
	//tuple class used to return values from subarray functions.
	//template allows floating point data do be analyzed (int, int, float)
	template<typename T1, typename T2, typename T3>
	class tuple {
	public:
		tuple(const tuple& t) :
			_first(t._first),
			_second(t._second),
			_third(t._third) {}
		tuple(tuple&& t) :
			_first(std::move(t._first)),
			_second(std::move(t._second)),
			_third(std::move(t._third)) {}
		tuple(const T1& First, const T2& Second, const T3& Third) :
			_first(First),
			_second(Second),
			_third(Third) {}
		inline void operator()(T1& load_first, T2& load_second, T3& load_third) {
			load_first = _first;
			load_second = _second;
			load_third = _third;
		}
		inline friend std::ostream& operator<<(std::ostream& s, const tuple& t) {
			t.print(s);
		}
	private:
		tuple() {}
		T1 _first;
		T2 _second;
		T3 _third;
		void print(std::ostream& s) const {
			s << "(" << _first << ", " << _second << ", " << _third << ")";
		}
	};
}


//max sub array method taken from Introduction to Algorithms (CLRS) 3rd ed. page 71
template<typename T1, typename T2>
ds::tuple<T1,T1,T2> find_max_crossing_subarray(T2* A, T1 low, T1 mid, T1 high) {
	T2 left_sum = std::numeric_limits<T2>::lowest(); //initialize -inf
	T2 right_sum = left_sum; //initialize -if
	T1 max_left = 0; //initialize max-left index
	T1 max_right = 0; //initialize max-right index
	T2 sum = 0; //initalize running sum
	
	for (T1 i = mid; i >= low; i--) { //loop through left half of array
		sum = sum + A[i]; //running summation on left half of array
		if (sum > left_sum) { //if adding A[i] increases running sum then store summation and array index for left half
			left_sum = sum;
			max_left = i;
		}
	}
	sum = 0; //reset running sum
	for (T1 i = mid + 1; i <= high; i++) { //loop through right half of array
		sum = sum + A[i]; //running summation on right half of array
		if (sum > right_sum) { //if adding A[i] increases running sum then store summation and array index for right half
			right_sum = sum;
			max_right = i;
		}
	}
	return ds::tuple<T1,T1,T2>(max_left, max_right, left_sum + right_sum); //return summation and index result as tuple
}

//max sub array method taken from Introduction to Algorithms (CLRS) 3rd ed. page 72
template<typename T1, typename T2>
ds::tuple<T1, T1, T2> find_max_subarray(T2* A, T1 low, T1 high) {
	if (high == low) { //base case return if array length is 1
		return ds::tuple<T1,T1,T2>(low, high, A[low]);
	}
	T1 left_low = 0; T1 left_high = 0; T2 left_sum = 0; //initialize left half values
	T1 right_low = 0; T1 right_high = 0; T2 right_sum = 0; //initalize right half values
	T1 cross_low = 0; T1 cross_high = 0; T2 cross_sum = 0; //initalize cross array values

	T1 mid = std::floor<T1>((low + high)/2); //calculate mid-point
	ds::tuple<T1,T1,T2> left_tuple = find_max_subarray<T1,T2>(A, low, mid); //recurse down the left half of the array
	ds::tuple<T1,T1,T2> right_tuple = find_max_subarray<T1,T2>(A, mid + 1, high); //recurse down the right half of the array
	ds::tuple<T1,T1,T2> cross_tuple = find_max_crossing_subarray<T1,T2>(A, low, mid, high); //recurse across the array from the inside out

	left_tuple(left_low, left_high, left_sum); //tuple::operator() --> loads values i.e. arg1 = left_tuple.first, arg2 = left_tuple.second, and arg3 = left_tuple.third
	right_tuple(right_low, right_high, right_sum); //load right half results
	cross_tuple(cross_low, cross_high, cross_sum); //load cross-section results

	/*
		recursively evalute the cross-section totals, such that the section of the
		array with the maximum sub-total will be pulled to the top of the call
		stack and returned as the final result.
	*/
	if (left_sum >= right_sum && right_sum >= cross_sum) {
		return ds::tuple<T1,T1,T2>(left_low, left_high, left_sum);
	} else if (right_sum >= left_sum && right_sum >= cross_sum) {
		return ds::tuple<T1,T1,T2>(right_low, right_high, right_sum);
	} else {
		return ds::tuple<T1,T1,T2>(cross_low, cross_high, cross_sum);
	}

}

int test_array[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
int TEST_ARRAY_LOW = 0;
int TEST_ARRAY_HIGH = 15;

int main(int argc, char* argv[]) {
	ds::tuple<int,int,int> t = find_max_subarray<int,int>(test_array, TEST_ARRAY_LOW, TEST_ARRAY_HIGH);
	std::cout << t << '\n';
	
}
