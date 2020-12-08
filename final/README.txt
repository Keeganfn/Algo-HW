Portfolio Assignment - Keegan Nave 

Sudoku:

To run the game on flip servers:
    - g++ -std=c++11 sudoku.cpp -o sudoku
    - ./sudoku (uses hardcoded puzzle that is easier) 
    - ./sudoku random (uses randomly generated puzzle that is harder)


Controls/Rules:
    - Enter ROW COLUMN NUMBER to add a number (ex: 1 1 1) you can also replace numbers this way if they were not apart of the original puzzle.
        -There is limited error checking for this so dont try too hard to break it :)
        -You will be prompted again if you give a number out of range (unless you enter a 0 anywhere in your answer which will check your answer)

    - Enter 0 to check your current answer, you can run this even if you have not filled every square to check your progress

    - Enter -1 to reset the board to its original state

    - Enter -2 to auto solve the board if possible and end the game, this usually will take only a couple seconds but it could take up to 2 minutes to solve
        - Only takes into account the original board, none of the user answers
        - Will also let you know if the board is valid but unsolvable

    - Running the program with ./sudoku random will generate a random board of 10 numbers, this usually takes longer for the solver to solve than the 
      hard coded board that is run with ./sudoku
        -This will create a valid board garunteed but it is not garunteed to be solvable which is normal for sudoku 
         (Most of the time it is solvable though)


    -Instructions appear at the bottom of the board and any prompts from actions appear above the board.

    -After filling all the squares you will need to verify your solution with 0 in order to win. You can also check your solutions along the way.


Runtime:

    -My verification algorithm has a O(n^3) runtime since we have 2 nested for loops and within the for loops I am inserting values into an 
     unordered list which has a worst case runtime of n. The average case for the insertinon of an unordered list is constant so the average
     case runtime is closer to O(n^2).

    -My generating algorithm has an unknown runtime since it uses random values and could theoretically take forever. 

    -My solving algorithm is also hard to tell its runtime but I believe it is something terrible like 2^(n^2) which is not polynomial time since it
     uses both recursion and a nested for loop.



Thanks!

