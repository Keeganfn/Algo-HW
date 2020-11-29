#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//recursively finds the number of step combinations for a given number, has atrocious run time anything over 50 takes forever
int step_finder(int number_of_steps){
    //base case for when our step number is below 3 we return (this will either be 1 or 2)
    if(number_of_steps < 3){
        return number_of_steps; 
    }

    //sums the unique ways to climb steps
    int unique_ways = 0;

    //goes through recurvively taking 1 or 2 steps at each level and returning the results which are eventually added together
    unique_ways += step_finder(number_of_steps - 1);
    unique_ways += step_finder(number_of_steps - 2);

    //returns our answer
    return unique_ways;
}



//takes an integer as command line input, 
int main(int argc, char **argv){
 
    int number = 5;

    //takes command line input for number of steps if one is not provided it defaults to 5
    if(argc > 1){
        number = stoi(argv[1]);
    }

    //finds recursive solution
    int result = step_finder(number); 
    cout << "Unique ways to climb " << number << " steps: " << result << endl;

}
