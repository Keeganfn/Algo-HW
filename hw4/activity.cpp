#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>


using namespace std;

//struct to hold all the data on an activity for easy lookup and sorting
struct activity{
	int name;
	int start;
	int finish;
};


//from assignment 1
//Used the psuedocode from book as well as the psuedocode from wikepedia https://en.wikipedia.org/wiki/Insertion_sort but modified for vectors 
//also modified for use with my struct and sorts in descending order the start times
 void insert_sort(vector<activity> &data_arr){
	int i = 1;
	int j;
	activity temp;
	//compares elements and switches them / backtracks as needed
	while(i < data_arr.size()){
		j = i;
		while(j > 0 && data_arr[j-1].start < data_arr[j].start){
			temp = data_arr[j];	
			data_arr[j] = data_arr[j-1];			
			data_arr[j-1] = temp;	
			j--;
		}
		i++;
	}

}

//This greedy algorithm is modified from the book to choose the last activity to start instead of the first activity to finish 
//Expects a sorted list of activities start times in descending order 
vector<activity> last_to_start_algo(vector<activity> &activities){
	int size = activities.size();
	vector<activity> solution;
	//add the last activity to start and add it to our array
	solution.push_back(activities[0]);
	int index = 0;

	for(int i = 1; i < size; i++){
		//if the start time is greater than the finish time of the next activity to finish then we add that to our solution and change the index
		if(activities[index].start >= activities[i].finish){
			solution.insert(solution.begin(),activities[i]);	
			index = i;
		}		
	}
	return solution;

}
//reads act.txt and inserts the information into a vector of activity structs where it is then sorted and sent through a greedy algo to get our result
int main(int argc, char **argv){
	ifstream datafile;
	datafile.open("act.txt");

	int num_activities;
	int set_num = 1;
	string lineinput;
	vector<activity> activity_arr;
	vector<activity> optimal_solution;
	//grabs the data from file and converts it to an array for sorting and greedy algo
	if(datafile.is_open()){
		while(getline(datafile, lineinput)){
			num_activities = stoi(lineinput);
			
			activity placeholder;
			int temp;
			int count;
			//puts activity information into a struct then a vector for easy access
			for(int i = 0; i < num_activities; i++){
				count = 0;
				getline(datafile, lineinput);
				for(stringstream ss(lineinput); ss >> temp;){
					if(count == 0){
						placeholder.name = temp;	
						count++;
					}	
					else if (count == 1) {
						placeholder.start = temp;
						count++;
					}
					else if (count == 2){
						placeholder.finish = temp;	
						count++;
					}	
				}
				activity_arr.push_back(placeholder);
			}
			//sorts the activity_arr by descending order according to start times
			insert_sort(activity_arr);
			//begins greedy algo	
			optimal_solution = last_to_start_algo(activity_arr);
		
			//outputs the solution to the terminal
			cout << "Set " << set_num << endl;
			cout << "Number of activities selected = " << optimal_solution.size() << endl;
			cout << "Activities: ";
			for(auto i: optimal_solution){
				cout << i.name << " ";	
			}
			cout << endl;

			//clears the arrays for next set
			set_num++;
			activity_arr.clear();
			optimal_solution.clear();
		}	
	
	}
	else{	
		cout << "couldnt open file data.txt" << endl;	
	}

	datafile.close();
	return 0;
}
