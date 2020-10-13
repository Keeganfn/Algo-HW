#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <time.h>

using namespace std;

//genereates random numbers and fills the vector depending on startin_num
void generate_random(vector<int>& data_arr, int& starting_num){
	srand(time(NULL));
	int ran_num;
	for(int i = 0; i < starting_num; i++){
		ran_num = rand()%10001;	
		data_arr.push_back(ran_num);		
	}
}
//Used the psuedocode from HW documentas well as the psuedocode from the visualization given in module 2 as well as the psuedocode from this wikipedia page https://en.wikipedia.org/wiki/Stooge_sort
void stooge_sort(vector<int>& data_arr,int start, int number_of_datapoints){
	int placeholder;
	int temp;
	//swaps numbers if condition holds true
	if(data_arr[number_of_datapoints] < data_arr[start]){	
		temp = data_arr[number_of_datapoints];
		data_arr[number_of_datapoints] = data_arr[start];
		data_arr[start] = temp;
		//swap(data_arr[number_of_datapoints],data_arr[start]);	
	}	
	//starts recursive calls if it is above 3 
	if((number_of_datapoints - start + 1) > 2){
		placeholder = (number_of_datapoints - start + 1)/3;	
		stooge_sort(data_arr, start, number_of_datapoints-placeholder);
		stooge_sort(data_arr, start+placeholder, number_of_datapoints );
		stooge_sort(data_arr, start, number_of_datapoints-placeholder);
	}
}


//learned how to use chrono library for timing using this article https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
int main(int argc, char **argv){
	vector<int> data_arr;
	int number_of_datapoints = 0;
	int starting_num = 100;
	cout << "Timing for stooge sort over different values of n" << endl;
	for(int i = 0; i < 7; i++){
		generate_random(data_arr, starting_num);
	
		auto start_time = chrono::high_resolution_clock::now();
		stooge_sort(data_arr,0,data_arr.size()-1);
		auto finish_time = chrono::high_resolution_clock::now();
		auto time_elapsed = chrono::duration_cast<chrono::milliseconds>(finish_time - start_time);
		cout << "n = " << starting_num << " time elapsed in milliseconds = " << time_elapsed.count() << endl;	
		data_arr.clear();
		//seven increments of 5000
		starting_num += 100;
	}	

	return 0;
}
