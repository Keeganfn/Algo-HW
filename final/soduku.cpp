#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <set>

using namespace std;



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

bool check_answer(vector<vector<string>> &board){
    bool incomplete = false;
    //Refrenced the docs for refresher on unordered sets http://www.cplusplus.com/reference/unordered_set/unordered_set/
    vector<unordered_set<string>> row(9);
    vector<unordered_set<string>> column(9);
    vector<unordered_set<string>> box(9);

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] != "*"){
                auto unique_check_row = row[i].insert(board[i][j]);    
                auto unique_check_column = column[j].insert(board[i][j]);    
                int box_id = (i/3)*3 + j/3;
               // cout << "ID" << box_id << endl;
                auto unique_check_box = box[box_id].insert(board[i][j]);    
               // cout << "Box: " << box_id << " Location: " << i << j << " value: " << board[i][j] << endl;

                if(unique_check_row.second == 0 || unique_check_column.second == 0 || unique_check_box.second == 0){
                 //   cout << "ROW: " << unique_check_row.second << endl;
                   // cout << "COLUMN: " << unique_check_column.second << endl;
                    //cout << "BOX: " << unique_check_box.second << endl;
                    cout << "INCORRECT SOLUTION\n" << endl;
                    return false;
                }
            }
            else{
                incomplete = true; 
            }


        }
    }

    if(incomplete == true){
        cout << "So far your solution is correct but you still have squares that need to be filled!\n" << endl;
        return false;
    }
    else{
        cout << "CORRECT SOLUTION\n" << endl; 
        cout << "YOU WIN! \n" << endl; 
        return true;
    }


}


bool get_input(vector<vector<string>> &board, vector<vector<string>> &board_master, vector<vector<string>> &board_solution){
    string input;
    int temp_num;
    int row;
    int column;
    int number;
    cout << "\n\n\nEnter 0 to check your current answer progress (Results displayed above board)" << endl;
    cout << "Enter -1 to reset the board" << endl;
    cout << "Enter -2 to solve the board" << endl;
    cout << "Enter ROW COLUMN NUMBER to add a number (ex: 1 1 1) You can also replace numbers this way" << endl;
    cout << "Please enter your next action:  " << endl;
    getline(cin, input); 

    int count = 0;
    for(stringstream ss(input); ss >> temp_num;){
        if(temp_num == 0){
            cout << "\n\n\nCHECKING ANSWER:"<< endl; 
            bool correct = check_answer(board);

            return correct;
        }
        if(temp_num == -1){
            cout << "\n\n\nRESETTING BOARD:\n"<< endl; 
            board = board_master;
            return false;
        } 
         if(temp_num == -2){
            cout << "\n\n\nSOLVING BOARD: (CHECK SOLUTION TO VERIFY BY ENTERING 0)\n"<< endl; 
            board = board_solution;
            return false;
        }
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
    if(count != 3){
        cout << "\n\n\nINCORRECT NUMBER OF ARGUMENTS: Please enter your choice in format: ROW COLUMN NUMBER ex: 1 1 1 \n" << endl;
        return false; 
    }

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
    vector<vector<string>> board(9, vector<string> (9, "*"));

/*    for(auto i: board){
        for(auto j: i){
            cout << j; 
        }
        cout << endl;
    }
*/
//    board[4][6] = "7";
//    board[2][5] = "7";
//    board[6][8] = "7";
//    board[3][0] = "7";
//    board[0][1] = "7";
//    board[1][2] = "7";
//      board[0][3] = "2";
//      board[0][4] = "6";
//      board[0][6] = "7";
//      board[0][6] = "1";
vector<vector<string>> soduku1{
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

    board = soduku1;
   // check_answer(board);

    vector<vector<string>> board_master(9, vector<string> (9, "*"));
    board_master = board;

    bool input_result;
    while(input_result == false){
        draw_board(board);
        input_result = get_input(board, board_master, solution1); 
    
    }




    



}
