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

//reads data.txt and outputs the sorted result in descending order to insert.out
int main(int argc, char **argv){
	ifstream datafile;
	datafile.open("data.txt");
	ofstream outputfile;
	outputfile.open("insert.out");

	vector<int> data_arr;
	string lineinput;
	int number_of_datapoints = 0;
	//grabs each individual line and converts it into a vector for processing by insert_sort which is then outputted to file
	if(datafile.is_open()){
		while(getline(datafile, lineinput)){
			get_line_data(data_arr, lineinput, number_of_datapoints);
			insert_sort(data_arr, number_of_datapoints);
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
