#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <unordered_map>
#include <queue>


using namespace std;

//wrestler struct to keep necessary info for bfs
struct wrestler{
    int role = -1;
    bool visited = false;
    list<string> rivals;
};

//refreshed my usage of queues in c++ with this webpage https://www.geeksforgeeks.org/queue-cpp-stl/
bool bfs_rivals(unordered_map<string, wrestler>& graph){
    //initialized queue of strings 
    queue<string> wrestler_queue;
    auto start = graph.begin(); 
    bool complete = false; 
    //makes sure that if graph is disjointed that every vertex is explored
    while(complete == false){
        for(auto i = graph.begin(); i != graph.end(); i++){
            if(i->second.visited == false){
                start = i; 
                break;
            } 
            else{
                complete = true;    
            } 
        }

        //initializing starting vertex
        wrestler_queue.push(start->first);
        start->second.role = 0;
         
        while(!wrestler_queue.empty()){
            //gets pointer to first wrestler name in queue and finds the corresponding wrestler struct with adjacency list
            string name = wrestler_queue.front();
            wrestler_queue.pop(); 
            wrestler *current_wrestler = &graph.at(name);  

            //for every adjacent vertex in the adjacency list of the first wrestler
            for(auto i = current_wrestler->rivals.begin(); i != current_wrestler->rivals.end(); i++){

                //we get a pointer to the rival_wrestler information from list
                wrestler* rival_wrestler = &graph.at(*i);

                //if we havent visited this vertex yet 
                if(rival_wrestler->visited == false)
                    //if a rival adjacent wrestler has the same role as our current wrestler we know it is not possible
                    //for everyone to have a rival and return false
                    if(rival_wrestler->role == current_wrestler->role && rival_wrestler->role != -1){
                        return false; 
                    }

                    //otherwise if the wrestler role has not been assigned we set it to the oppposite role of the current wrestler
                    else if(rival_wrestler->role == -1){
                        if(current_wrestler->role == 0){
                            rival_wrestler->role = 1;
                        } 
                        else{
                            rival_wrestler->role = 0; 
                        }
                        //adds the rival wrestler to the queue
                        wrestler_queue.push(*i);
                    }
                    else{}
            }
            //mark current wrestler as visited
            current_wrestler->visited = true;  
        }
    } 
    //the sequence is possible return true
    return true;
}



//Creates unordered map to better store wrestler data for easy lookup and creates an adjacency Matrix, sends the map to bfs and returns the result.
//More complicated than it needs to be probably
int main(int argc, char **argv){
    
	ifstream datafile;
	datafile.open(argv[1]);

	string lineinput;
    int num_wrestlers;
    int num_pairs;

    //refreshed my memory on using unordered_maps and lists in c++ using these webpages: https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/
    //https://www.geeksforgeeks.org/list-cpp-stl/
    unordered_map<string, wrestler> wrestler_graph;
    wrestler wrestler_template;

    //using an unordered_map for easy fast lookup on strings
	if(datafile.is_open()){
		getline(datafile, lineinput);
		num_wrestlers = stoi(lineinput);
        
        //adds wrestlers to unordered_map aka adjacency list
        for(int i = 0; i < num_wrestlers; i++){
            getline(datafile, lineinput); 
            stringstream gg(lineinput);
            gg >> lineinput;
            //wrestler_graph.insert(pair<string, wrestler>(lineinput,wrestler_template));
            wrestler_graph[lineinput] = wrestler_template; 
        }

        getline(datafile, lineinput);
		num_pairs = stoi(lineinput);

        //fills out adjacency list of each wrestler 
        for(int i = 0; i < num_pairs; i++){
            string wrestler1;
            string wrestler2;

            getline(datafile, lineinput); 
			stringstream ss(lineinput);
            ss >> wrestler1;
            ss >> wrestler2;
            
            //adds both wrestlers to each others adjacency list
            auto place = wrestler_graph.find(wrestler1);
            place->second.rivals.push_back(wrestler2);

            place = wrestler_graph.find(wrestler2);
            place->second.rivals.push_back(wrestler1);
        }

        bool possible = bfs_rivals(wrestler_graph);

        //if a sequence is possible we go through each role value and print out the combination of roles that works
        if(possible == true){
            cout << "Possible" << endl;
            cout << "Babyfaces: ";
            for(auto i = wrestler_graph.begin(); i != wrestler_graph.end(); i++){
                if(i->second.role == 0){
                    cout << i->first << " "; 
                }
            }
            cout << endl;
            cout << "Heels: ";
            for(auto i = wrestler_graph.begin(); i != wrestler_graph.end(); i++){
                if(i->second.role == 1){
                    cout << i->first << " "; 
                }
            }
        
        }
        //otherwise return impossible
        else{
            cout << "Impossible"; 
        }
        cout << endl; 
	
	}
	else{	
		cout << "couldnt open file data.txt" << endl;	
	}

	datafile.close();
	return 0;
}
