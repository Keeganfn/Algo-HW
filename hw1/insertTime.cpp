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
//Used the psuedocode from book  as well as the psuedocode from wikepedia https://en.wikipedia.org/wiki/Insertion_sort but modified for descending 
void insert_sort(vector<int>& data_arr, int number_of_datapoints){
	int i = 1;
	int j;
	int temp;
	//compares elements and switches them / backtracks as needed
	while(i < data_arr.size()){
		j = i;
		while(j > 0 && data_arr[j-1] < data_arr[j]){
			temp = data_arr[j];	
			data_arr[j] = data_arr[j-1];			
			data_arr[j-1] = temp;	
			j--;
		}
		i++;
	}

}

//learned how to use chrono library for timing using this article https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
int main(int argc, char **argv){
	vector<int> data_arr;
	int number_of_datapoints = 0;
	int starting_num = 5000;
	cout << "Timing for insert sort over different values of n" << endl;
	for(int i = 0; i < 7; i++){
		generate_random(data_arr, starting_num);
		auto start_time = chrono::high_resolution_clock::now();
		insert_sort(data_arr, number_of_datapoints);
		auto finish_time = chrono::high_resolution_clock::now();
		auto time_elapsed = chrono::duration_cast<chrono::milliseconds>(finish_time - start_time);
		cout << "n = " << starting_num << " time elapsed in milliseconds = " << time_elapsed.count() << endl;	
		data_arr.clear();
		//seven increments of 5000
		starting_num += 5000;
	}	

	return 0;
}
