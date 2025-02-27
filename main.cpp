#include <iostream>
#include <string>

char checkerBoard[8][8];
int ownershipBoard[8][8];

const char EMPTY_SPACE{'*'};
const char P1_NORM_PIECE{'O'};
const char P2_NORM_PIECE{'0'};

const int P1_NORM_PIECE_ID{1};
const int P2_NORM_PIECE_ID{2};
const int EMPTY_SPACE_ID{0};
// Worry about the King pieces later
// const int P1_KING_PIECE_ID{100};
// const int P2_KING_PIECE_ID{200};

void displayCheckerBoard(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            std::cout << checkerBoard[i][j];
        }
        std::cout << '\n';
    }
}

void setupOwnershipBoard(){
    for(int ROW = 0; ROW < 8; ROW++){
        int start = (ROW % 2 == 0 ? 1: 0);
        for(int COLUMN = 0; COLUMN < 8; COLUMN++){
            if(ROW<=2){
                ownershipBoard[ROW][COLUMN] = (COLUMN % 2 == start ? P2_NORM_PIECE_ID: EMPTY_SPACE_ID);
            }
            else if(ROW<=4){
                ownershipBoard[ROW][COLUMN] = EMPTY_SPACE_ID;
            }else{
                ownershipBoard[ROW][COLUMN] = (COLUMN % 2 == start ? P1_NORM_PIECE_ID: EMPTY_SPACE_ID);
            }
        }
    }
}

void setupCheckerBoard(){
    for(int ROW = 0; ROW < 8; ROW++){
        for(int COLUMN = 0; COLUMN < 8; COLUMN++){
            switch(ownershipBoard[ROW][COLUMN]){
                case(P1_NORM_PIECE_ID):
                    checkerBoard[ROW][COLUMN] = P1_NORM_PIECE;
                    break;
                case(P2_NORM_PIECE_ID):
                    checkerBoard[ROW][COLUMN] = P2_NORM_PIECE;
                    break;
                default:
                    checkerBoard[ROW][COLUMN] = EMPTY_SPACE;
                    break;
            }
        }
    }
}

bool checkValidityOfChosenPiece(std::string &position, int playerTurnID){
    if(position.length() != 2){
        return false;
    }
    int ROW = position[0] - '0';
    int COLUMN = position[1] - '0';

    if(!(0 <= ROW && ROW <= 7) || !(0 <= COLUMN && COLUMN <= 7)){
        return false;
    }

    if(playerTurnID == 1){
        if(ownershipBoard[ROW][COLUMN] == P1_NORM_PIECE_ID){
            return true;
        }
        return false;
    }else{
        if(ownershipBoard[ROW][COLUMN] == P2_NORM_PIECE_ID){
            return true;
        }
        return false;
    }
}
int main(){
    setupOwnershipBoard();
    setupCheckerBoard();
    displayCheckerBoard();
    int playerTurn = 1;
    while(true){
        std::string poistionOfPiece;
        std::cout << "Input the posititon of the piece you would like to move: ";
        std::cin >> poistionOfPiece;
        
        while(!checkValidityOfChosenPiece(poistionOfPiece, playerTurn)){
            std::cout << "Not valid. Input the posititon of the piece you would like to move: ";
            std::cin >> poistionOfPiece;
        }

        playerTurn = (playerTurn == 1 ? 2: 1);
    }
}