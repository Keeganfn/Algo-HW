#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
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

//Used the psuedocode from HW documentas well as the psuedocode from the visualization given in module 2 as well as the psuedocode from this wikipedia page https://en.wikipedia.org/wiki/Stooge_sort
void stooge_sort(vector<int>& data_arr,int start, int number_of_datapoints){

	//swaps numbers if condition holds true
	if(data_arr[number_of_datapoints] < data_arr[start]){
		swap(data_arr[number_of_datapoints],data_arr[start]);	
	}	
	//starts recursive calls if it is above 3 
	if((number_of_datapoints - start + 1) > 2){
		int	placeholder = (number_of_datapoints - start + 1)/3;	
		stooge_sort(data_arr, start, number_of_datapoints-placeholder);
		stooge_sort(data_arr, start+placeholder, number_of_datapoints );
		stooge_sort(data_arr, start, number_of_datapoints-placeholder);
	}
}

//reads data.txt and outputs the sorted result in descending order to insert.out
int main(int argc, char **argv){
	ifstream datafile;
	datafile.open("data.txt");
	ofstream outputfile;
	outputfile.open("stooge.out");

	vector<int> data_arr;
	string lineinput;
	int number_of_datapoints = 0;
	//grabs each individual line and converts it into a vector for processing by insert_sort which is then outputted to file
	if(datafile.is_open()){
		while(getline(datafile, lineinput)){
			get_line_data(data_arr, lineinput, number_of_datapoints);
			stooge_sort(data_arr,0,number_of_datapoints-1);
			for(auto i: data_arr){
				outputfile << i << " ";
			}
			outputfile << "\n";
			data_arr.clear();
		}	
	
	}
	else{	
		cout << "couldnt open file data.txt" << endl;	
	}

	datafile.close();
	outputfile.close();
	return 0;
}
