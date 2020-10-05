#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <time.h>

using namespace std;

//generates random numbers using time and rand to populate arrays of size starting_num
void generate_random(vector<int>& data_arr, int& starting_num){
	//seeding
	srand(time(NULL));
	int ran_num;
	for(int i = 0; i < starting_num; i++){
		ran_num = rand()%10001;	
		data_arr.push_back(ran_num);		
	}
}

//creates a work array identical to data_arr
void copy_array(vector<int>& final_arr, int begin, int end, vector<int>& temp_arr){
	temp_arr = final_arr;	
}


//is called to compare subtrees and rearrange them 
void merge(vector<int>& final_arr, int begin, int middle, int end, vector<int>& temp_arr){
	int i = begin;
	int j = middle;

	for(int k = begin; k < end; k++){
		if(i < middle && (j >= end || final_arr[i] >= final_arr[j])){
			temp_arr[k] = final_arr[i];	
			i++;
		}	
		else{
			temp_arr[k] = final_arr[j];
			j++;	
		}		
	}
}
//splits arrays into subarrays then merges them back together using recursion
void split(vector<int>& temp_arr, int begin, int end, vector<int>& final_arr){
		
		if(end - begin <= 1){
			return;	
		}
		
		int middle = (begin + end) / 2;
		//splits arrays into smaller and smaller sub arrays recursively
		split(final_arr, begin, middle, temp_arr);
		split(final_arr, middle, end, temp_arr);
		//after splitting they begin to merge back together recursively	
		merge(temp_arr, begin, middle, end, final_arr);

}

//Used the psuedocode from the book  as well as the psuedocode from wikepedia https://en.wikipedia.org/wiki/Merge_sort but modified for descending and vectors 
void merge_sort(vector<int>& data_arr, vector<int>& temp_arr, int number_of_datapoints){
	copy_array(data_arr, 0, number_of_datapoints, temp_arr);	
	split(temp_arr, 0, number_of_datapoints, data_arr);

}


//learned how to use chrono library for timing using this article https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
int main(int argc, char **argv){
	//creating all needed vars and arrays
	vector<int> data_arr;
	vector<int> temp_arr;
	int number_of_datapoints = 0;
	int starting_num = 100000;
	cout << "Timing for merge sort over different values of n" << endl;
	for(int i = 0; i < 7; i++){
		generate_random(data_arr, starting_num);
		auto start_time = chrono::high_resolution_clock::now();
		merge_sort(data_arr, temp_arr, data_arr.size());
		auto finish_time = chrono::high_resolution_clock::now();
		auto time_elapsed = chrono::duration_cast<chrono::milliseconds>(finish_time - start_time);
		cout << "n = " << starting_num << " time elapsed in milliseconds = " << time_elapsed.count() << endl;	
		data_arr.clear();
		starting_num += 100000;
	}	

	return 0;
}
