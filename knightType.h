/*
CS 302 Assignment 2

Name: Keith Beauvais, 5005338658, CS 302 Assignment 2
*/


#include <iostream>
#include <vector>
#include <iomanip>

class knightType{


    public:
        struct position{
            position(int r = 0, int c = 0, int o = 0){
                row = r;
                col = c;
                onwardMoves = o;
            }
    int row;
    int col;
    int onwardMoves;
    };

    knightType(int = 8);
    bool knightTour(int , int);
    void outputTour () const;

    private:

    bool knightTour(int , int , int);
    std::vector <position> getAvailableMoves(int , int);
    bool fullBoard ();
    std::vector <std::vector<int> > board;
    int functionsCalled;
};

/* 
knightType(int dim) - constructor that allocates a dim ×dim vector to the board
object and sets each element to 0, sets functionsCalled to 0.

return value - n/a
*/
knightType::knightType(int dim){
    board.resize(dim);
    int zero = 0;
    functionsCalled = zero;

    for(int i = 0; i<board.size(); i++){
        board[i].resize(dim);
    }

    for(int i = 0; i < board.size(); i++){

        for (int j = 0; j < board[i].size(); j++){
            board[i][j] = zero;
            
        }
    }

}

/* 
vector<knightType::position> knightType::getAvailableMoves(int r, int c) - function that returns a list of possible moves a knight can make from coordinate [r, c] along with the onward
moves that the knight can make if the new potential location is chosen.

return value - returns a vector of possible moves a knight can make from coordinate [r, c] 
*/
std::vector<knightType::position> knightType::getAvailableMoves(int r, int c){
    
    std::vector<position> knightMoves;
    int tempRow=0;
    int tempCol=0;
    int tempOnward = 0;

    int onwardRowTemp = 0;
    int onwardColTemp = 0;

    // Navigator to avoid using 8 if statements
    int xCoord[8] = {  1 , -1 ,  2 ,  2 ,  1 , -1 , -2 , -2 };
    int yCoord[8] = {  2 ,  2 , -1 ,  1 , -2 , -2 , -1 ,  1 };

    // Outer loop is to make sure the coordinates being passed in are in bounds before moving onto the onward moves.
    for(int i = 0; i < 8; i++){
        tempRow=xCoord[i]+r;    // temp row index
        tempCol=yCoord[i]+c;    // temp column index
        if(tempRow>=0 && tempCol>=0){ //make sure the new indexs are above 0 
            if(tempRow<board.size()&& tempCol<board.size()){ //make sure the new indexs are less than the board size
                if(board[tempRow][tempCol]==0){ // make sure that the new index hasnt been vistied before.
                    // inner loop checks the onward moves 
                    for(int j = 0; j<8; j++){
                        onwardRowTemp=xCoord[j]+tempRow;    // temp onward row index
                        onwardColTemp=yCoord[j]+tempCol;     // temp onward column index
                            if(onwardRowTemp>=0 && onwardColTemp>=0){ //make sure the new indexs are above 0 
                                if(onwardRowTemp<board.size()&& onwardColTemp<board.size()){ //make sure the new indexs are less than the board size
                                    if(board[onwardRowTemp][onwardColTemp] == 0){ // make sure that the new index hasnt been vistied before.
                                        tempOnward++; // increment the amount of onward moves there are.
                                    }
                                }
                            }
                    }
                    // exits inner loop and pushes back into the vector with new coordinates to be returned
                    knightMoves.push_back(position(tempRow,tempCol,tempOnward));
                    tempOnward = 0; // resets the onward moves counter
                }
            }
        }
    }
    return knightMoves;
}

/* 
bool fullBoard() - returns true if the knight tour is complete (every cell in board
contains an integer larger than 0), and false otherwise

return value - returns true or false bases on parameters listed above
*/
bool knightType::fullBoard(){
    for(int i = 0; i < board.size(); i++){

        for (int j = 0; j < board[i].size(); j++){

            if(board[i][j] == 0 ){

                return false;
            }
            
        }

    }
    return true;
}

/* 
void outputTour() const - outputs the board and the amount of functions called

return value - n/a
*/
void knightType::outputTour() const{

    knightType test;

    int testNum = 0;
    char outlineRow = 'A';
    char outlineCol = 'A';

    for(int i = 0; i< board.size()+1; i++){
        for (int j = 0; j <board.size()+1; j++){
            if(j == 0 && i > 0){
                std::cout << outlineCol <<" ";
                outlineCol++;
            }
            if(i == 0 && j >0){
                std::cout <<std::setw(3)<< outlineRow <<" ";

                outlineRow++;
            }
            if(i ==0 && j == 0){
                std::cout <<"  ";
            }
            if(i>0 && j>0){
                std::cout <<std::setw(3)<< board[i-1][j-1]<<" ";
            }
        }
        std::cout<<std::endl;

    }
    std::cout<<"Functions Called: " <<functionsCalled<<std::endl;

}

/* 
bool knightType::knightTour(int r, int c) - function that makes the first initial call to the recursive function r is the row and c is column. 

return value - returns true or false bases on parameters listed above
*/
bool knightType::knightTour(int r, int c){

    return knightTour(r,c,1);

}

/* 
bool knightType::knightTour(int r, int c) - his recursive function simulates the knight movement, the steps are:
    - Set the board[r][c] with tourIndex
    - Increments functions called
    - Check if the board is full if so, return true
    - Get all the available moves from location [r, c] and stores in a temp vector
    - Picks the available move with the minimal onward moves
    - Make a recursive call to this function, pass in the new r and c values using the chosen available
      move from the above step
      
return value - returns true or false bases on parameters listed above
*/
bool knightType::knightTour(int r, int c, int tourIndex){

    std::vector<position> tempVec;

    int minOnward;
    int index = 0;
    int minIndex = 0;
    int newRow= 0;
    int newCol= 0;
    bool flag = false;

    board[r][c] = tourIndex;

    functionsCalled++;

    if(fullBoard()==true){
        return true;
    }
    
    tempVec = getAvailableMoves(r,c);

    minOnward = tempVec[0].onwardMoves;

    for(int i =0; i<tempVec.size(); i++){
        tempVec[i];
        if (tempVec[i].onwardMoves < minOnward) {
            minOnward = tempVec[i].onwardMoves;
            minIndex = index;
        }
        index++;
    }

   
    newRow = tempVec[minIndex].row;
    newCol = tempVec[minIndex].col;

    flag = knightTour(newRow, newCol, tourIndex+1);

    if(flag){
        return true;
    }

    return false;
}
