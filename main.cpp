#include <iostream>
#include <string>
#include <vector>

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

// bool checkValidityOfMove(std::string& piecePosition, std::string& newPosition, int playerTurnID){
//     if(newPosition.length() != 2){
//         return false;
//     }
    
//     int piecePos = piecePosition[0] - '0';
//     int pieceCol = piecePosition[1] - '0';

//     int newPosRow = newPosition[0] - '0';
//     int newPosCol = newPosition[1] - '0';

//     // Unnecessary check?
//     // if(!(0 <= newPosRow && newPosRow <= 7) || !(0 <= newPosCol && newPosCol <= 7)){
//     //     return false;
//     // }

//     if(playerTurnID == 1){
//         if()
//     }
//     else{

//     }
// }
void generatePossibleMoves(std::vector<int>& arr, std::string& position){
    int ROW = position[0] - '0';
    int COL = position[1] - '0';

    if(ownershipBoard[ROW][COL] == P1_NORM_PIECE_ID){
        if(COL-1 >= 0){
            if(ownershipBoard[ROW-1][COL-1]== EMPTY_SPACE_ID){
                arr.push_back((ROW-1)*10 + COL-1);
            }
            else if(ROW-2 >=0 && COL-2 >= 0){
                if(ownershipBoard[ROW-1][COL-1]==P2_NORM_PIECE_ID && ownershipBoard[ROW-2][COL-2] == EMPTY_SPACE_ID){
                    arr.push_back((ROW-2)*10 + COL-2);
                }
            }
        }

        if(COL+1 <= 7){
            if(ownershipBoard[ROW-1][COL+1]== EMPTY_SPACE_ID){
                arr.push_back((ROW-1)*10 + (COL+1));
            }
            else if(ROW-2 >=0 && COL+2 <= 7){
                if(ownershipBoard[ROW-1][COL+1]==P2_NORM_PIECE_ID && ownershipBoard[ROW-2][COL+2] == EMPTY_SPACE_ID){
                    arr.push_back((ROW-2)*10 + COL+2);
                }
            }
        }
    }
    else if(ownershipBoard[ROW][COL] == P2_NORM_PIECE_ID){
        //CHANGE LATER
    }
    else{
        //EXPAND FOR KINGS AND RINGS LATER
    }
}
void displayPossibleMoves(std::vector<int>& arr){
    for(int i = 0; i < arr.size(); i++){
        std::cout << arr[i] << " ";
    }
}

bool checkValidityOfMove(std::vector<int>& arr, std::string& choice){
    if(choice.length() != 2){
        return false;
    }
    int ROW = choice[0] -'0';
    int COL = choice[1] - '0';

    for(int i = 0; i < arr.size(); i++){
        if(ROW==0){
            if(arr[i] < 10 && COL == arr[i]){
                return true;
            }
        }else if(ROW== arr[i]/10 && COL == arr[i]%10 ){
            return true;
        }
        // std::cout << (arr[i]-(arr[i]%10))%10 << '\n';
        // std::cout << arr[i]%10 << '\n';
    }
    return false;
}
int main(){
    setupOwnershipBoard();
    setupCheckerBoard();
    int playerTurn = 1;
    while(true){
        displayCheckerBoard();
        std::string positionOfPiece;
        std::cout << "Input the posititon of the piece you would like to move: ";
        std::cin >> positionOfPiece;
        bool hasAvailableMoves{false};
        
        while(!hasAvailableMoves){
            while(!checkValidityOfChosenPiece(positionOfPiece, playerTurn)){
                std::cout << "Not valid. Input the posititon of the piece you would like to move: ";
                std::cin >> positionOfPiece;
            }
            
            std::vector<int> availableMoves;
        
            generatePossibleMoves(availableMoves, positionOfPiece);

            if(availableMoves.size() > 0){
                displayPossibleMoves(availableMoves);
                std::cout << "\nChoose the move you would like to make: ";
                std::string choice; std::cin >> choice;
                while(!checkValidityOfMove(availableMoves, choice)){
                    std::cout << "Not an available move! Please input an available move: ";
                    std::cin >> choice;
                }

                
                hasAvailableMoves = true;
                positionOfPiece = "BAD_FIX";
            }else{
                std::cout << "Piece chosen can't move anywhere! ";
            }
        }

       

        playerTurn = (playerTurn == 1 ? 2: 1);
    }
}