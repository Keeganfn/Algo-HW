#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <time.h>
#include <stdlib.h>

using namespace std;


//draws board
void draw_board(vector<vector<string>> &board){ 
    cout << "              " << "SUDOKU" << endl;
    //displays numbers at the top
    cout << "  ";  
    for(int i = 1; i <= 9; i++){
        cout << "  " << i;  
        if(i % 3 == 0){
        cout << " ";  
        }
    }
    cout << endl;

    //draws game board with values from board vector
    for(int i = 1; i <= 9; i++){
        for(int j = 1; j <= 9; j++){
            if(j == 1){
                cout << i << " |";  
            }
            cout << " " << board[i-1][j-1] << " "; 
            if(j % 3 == 0){
                cout << "|"; 
            }
        }
        cout << endl; 
        if(i % 3 == 0 && i != 9){
            cout << "  |-----------------------------|" << endl;
        }
    }
}

//checks answer
int check_answer(vector<vector<string>> &board){
    bool incomplete = false;
    //Refrenced the docs for refresher on unordered sets http://www.cplusplus.com/reference/unordered_set/unordered_set/
    vector<unordered_set<string>> row(9);
    vector<unordered_set<string>> column(9);
    vector<unordered_set<string>> box(9);

    //goes through each row, column and box in the sudoku board and adds them to the respective unorded set
    //If the item already exists in an unordered set we know that the answer is incorrect and we return false
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] != "*"){
                //adding respective value to the respective unorded set array for row, columm and box
                auto unique_check_row = row[i].insert(board[i][j]);    
                auto unique_check_column = column[j].insert(board[i][j]);    
                //gets box numberk
                int box_id = (i/3)*3 + j/3;
                auto unique_check_box = box[box_id].insert(board[i][j]);    

                //if already present solution is incorrect
                if(unique_check_row.second == 0 || unique_check_column.second == 0 || unique_check_box.second == 0){
                    return 0;
                }
            }
            else{
                incomplete = true; 
            }


        }
    }
    //if the solution contains empty spaces but so far the answers are correct we return this message instead
    if(incomplete == true){
        return 2;
    }
    else{
        return 1;
    }


}

//generates a random sudoku board
vector<vector<string>> random_board(int given_numbers){

    vector<vector<string>> board(9, vector<string> (9, "*"));
    int num_given = 0; 

    //generates a given number of numbers on the board
    while(num_given < given_numbers){

        //generates random rows columns and numbers
        int random_row = rand() % 8; 
        int random_column = rand() % 8; 
        int random_number = rand() % 9 + 1; 

        int possible = 0;
        //if empty space we try to insert our random number and check to see if the board still works, if it does we increment the count and move on
        //otherwise we remove the number from the board and try again
        if(board[random_row][random_column] == "*"){
            board[random_row][random_column] = to_string(random_number); 
            possible = check_answer(board);
            if(possible == 2){
                num_given++; 
            }
            else{
                board[random_row][random_column] = "*"; 
            }
        }
    }
    return board;

}

//solves board if possible, if it isnt then it returns false
//took inspiration from this video that I saw a while back https://www.youtube.com/watch?v=G_UYXzGuqvM but I modified it for my use case a pretty large amount as well as ported it to c++ and as such it is pretty unrecognizable from the video.
bool solve_board(vector<vector<string>> &board){
    
    //double for loop that goes through every row and column of the board
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            //if we reach a space that is not filled execute whats inside
            if(board[i][j] == "*"){
                //we try every possible number from 1-9 and check to see if it works
                for(int k = 1; k < 10; k++){
                    
                    board[i][j] = to_string(k);
                    int answer = check_answer(board);
                    //changes back in case it doesnt work
                    board[i][j] = "*";

                    //if it does work but still has spots remaining we set the board index to the value and
                    //recursively call the solve_board function. The process repeats until the check_answer function returns a true for complete
                    //solvability, if we do not recieve that and instead reach a dead end we "backtrack" and reset value by value until a new 
                    //value that works is found and we go through the process again.
                    if(answer == 2){
                        board[i][j] = to_string(k);
                        bool solved = solve_board(board); 
                        if(!solved){
                            //reset value if we reach a dead end
                            board[i][j] = "*";
                        }
                        else{
                            return true;
                        }
                    }
                    //if it is completely solved we return true
                    if(answer == 1){
                        board[i][j] = to_string(k);
                        return true; 
                    }
                } 
                return false;
            }
        }
    }

}


bool get_input(vector<vector<string>> &board, vector<vector<string>> &board_master){
    string input;
    int temp_num;
    int row;
    int column;
    int number;
    //printing instructions
    cout << "\n\n\nEnter 0 to check your current answer progress (Results displayed above board)" << endl;
    cout << "Enter -1 to reset the board" << endl;
    cout << "Enter -2 to solve the board (this will end the game and not take into account any inputs you have made)" << endl;
    cout << "Enter ROW COLUMN NUMBER to add a number (ex: 1 1 1) You can also replace numbers this way" << endl;
    cout << "Please enter your next action:  " << endl;
    getline(cin, input); 

    int count = 0;
    //checks inputs and calls the correct function or outputs an error message
    for(stringstream ss(input); ss >> temp_num;){
        //calls check answer function
        if(temp_num == 0){
            cout << "\n\n\nCHECKING ANSWER:"<< endl; 
            int correct = check_answer(board);
            if(correct == 0){
                cout << "\n\n\nINCORRECT SOLUTION " << endl;; 
            }
            else if(correct == 1){
                cout << "\n\n\nCORRECT SOLUTION! YOU WIN!" << endl; 
            }
            else{
                cout << "\n\n\nCORRECT SOLUTION SO FAR, BUT YOU STILL HAVE BLANK SPACES TO FILL!" << endl; 
                correct = 0;
            }

            return correct;
        }
        //calls reset board function
        if(temp_num == -1){
            cout << "\n\n\nRESETTING BOARD:\n"<< endl; 
            board = board_master;
            return false;
        } 
        //calls solve board function
         if(temp_num == -2){
            cout << "\n\n\nSOLVING BOARD: (MAY TAKE A LITTLE) \n"<< endl; 
            bool test = solve_board(board_master);
            if(test == false){
                cout << "\n\n\nUNSOLVABLE BOARD SORRY \n" << endl; 
            }
            draw_board(board_master);
            return true;
        }
        //error catching
        if(temp_num < 1 || temp_num > 9){
            cout << "\n\n\nINCORRECT NUMBER USED: Your number choices need to be within 1-9 for all fields unless you are deleting or checking\n" << endl; 
            return false;
        }
        if(count == 0){
            row = temp_num; 
        } 
        else if(count == 1){
            column = temp_num; 
        }
        else if(count == 2){
            number = temp_num; 
        }
        count++;
    }
    //more error checking
    if(count != 3){
        cout << "\n\n\nINCORRECT NUMBER OF ARGUMENTS: Please enter your choice in format: ROW COLUMN NUMBER ex: 1 1 1 \n" << endl;
        return false; 
    }

    //inserts the user number into the board if it is allowed
    if(board_master[row-1][column-1] == "*"){
        board[row-1][column-1] = to_string(number);
        return false; 
    }
    else{
        cout << "\n\n\nCANT REPLACE: Cant replace this number since it is one of the given numbers for this board.\n"<< endl; 
        return false;
    }
}



int main(int argc, char **argv){
    srand(time(NULL));

    //predefined puzzle and solution
    vector<vector<string>> sudoku1{
    {"*","*","*","2","6","*","7","*","1"},
    {"6","8","*","*","7","*","*","9","*"},
    {"1","9","*","*","*","4","5","*","*"},
    {"8","2","*","1","*","*","*","4","*"},
    {"*","*","4","6","*","2","9","*","*"},
    {"*","5","*","*","*","3","*","2","8"},
    {"*","*","9","3","*","*","*","7","4"},
    {"*","4","*","*","5","*","*","3","6"},
    {"7","*","3","*","1","8","*","*","*"}
    };
/*
    vector<vector<string>> solution1{
    {"4","3","5","2","6","9","7","8","1"},
    {"6","8","2","5","7","1","4","9","3"},
    {"1","9","7","8","3","4","5","6","2"},
    {"8","2","6","1","9","5","3","4","7"},
    {"3","7","4","6","8","2","9","1","5"},
    {"9","5","1","7","4","3","6","2","8"},
    {"5","1","9","3","2","6","8","7","4"},
    {"2","4","8","9","5","7","1","3","6"},
    {"7","6","3","4","1","8","2","5","9"}
    };
*/

    //uses random generated board if random is passed as a command line argument
    if(argc >= 2){
        if(string(argv[1]) == "random"){
            sudoku1 = random_board(10);
        }
    }

    vector<vector<string>> board_master(9, vector<string> (9, "*"));
    board_master = sudoku1;

    //runs game
    bool input_result = false;
    while(!input_result){
        draw_board(sudoku1);
        input_result = get_input(sudoku1, board_master); 
    }
    cout << "\n\n\nGAME OVER\n " << endl;

}
