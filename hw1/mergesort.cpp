#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>


using namespace std;

//takes line data from file and delimets them and turns them into integers so they can be stored in a vector
void get_line_data(vector<int>& data_arr, string& lineinput, int& number_of_datapoints){
	int count = 0;
	int datapoint;

	//coverts to integer and delimets based on spaces
	for(stringstream geek(lineinput); geek >> datapoint;){
		if(count == 0){
			number_of_datapoints = datapoint;
			count++;
		}
		else{
			data_arr.push_back(datapoint);	
		}	
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
void merge_sort(vector<int>& data_arr, vector<int>& sorted_arr, int number_of_datapoints){

	copy_array(data_arr, 0, number_of_datapoints, sorted_arr);	
	split(sorted_arr, 0, number_of_datapoints, data_arr);

}


//reads data.txt and outputs the sorted result in descending order to insert.out
int main(int argc, char **argv){
	ifstream datafile;
	datafile.open("data.txt");
	ofstream outputfile;
	outputfile.open("merge.out");

	vector<int> data_arr;
	vector<int> sorted_arr;
	string lineinput;
	int number_of_datapoints = 0;

	//grabs each individual line and converts it into a vector for processing by insert_sort which is then outputted to file
	if(datafile.is_open()){
		while(getline(datafile, lineinput)){
			get_line_data(data_arr, lineinput, number_of_datapoints);
			merge_sort(data_arr, sorted_arr, number_of_datapoints);
			for(auto i: data_arr){
				outputfile << i << " ";
			}
			outputfile << "\n";
			data_arr.clear();
			sorted_arr.clear();
		}	
	
	}
	else{	
		cout << "couldnt open file data.txt" << endl;	
	}

	datafile.close();
	outputfile.close();
	return 0;
}
