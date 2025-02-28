#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

char checkerBoard[8][8];
int ownershipBoard[8][8];

const char EMPTY_SPACE{'*'};
const char P1_NORM_PIECE{'O'};
const char P2_NORM_PIECE{'0'};
const char P1_KING_PIECE{'K'};
const char P2_KING_PIECE{'R'};

const int P1_NORM_PIECE_ID{1};
const int P2_NORM_PIECE_ID{2};
const int EMPTY_SPACE_ID{0};
const int P1_KING_PIECE_ID{100};
const int P2_KING_PIECE_ID{200};

void displayCheckerBoard(){
    std::cout << "  ";
    for(int i = 0; i < 8; i++){
        std::cout << i << " ";
    }
    std::cout << '\n';

    for(int i = 0; i < 8; i++){
        std::cout << i << " ";
        for(int j = 0; j < 8; j++){
            std::cout << checkerBoard[i][j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
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
                case(P1_KING_PIECE_ID):
                    checkerBoard[ROW][COLUMN] = P1_KING_PIECE;
                    break;
                case(P2_KING_PIECE_ID):
                    checkerBoard[ROW][COLUMN] = P2_KING_PIECE;
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
        if(ownershipBoard[ROW][COLUMN] == P1_NORM_PIECE_ID ||ownershipBoard[ROW][COLUMN] == P1_KING_PIECE_ID){
            return true;
        }
        return false;
    }else{
        if(ownershipBoard[ROW][COLUMN] == P2_NORM_PIECE_ID ||ownershipBoard[ROW][COLUMN]==P2_KING_PIECE_ID ){
            return true;
        }
        return false;
    }
}

void generatePossibleMoves(std::vector<int>& arr, std::string& position){
    int ROW = position[0] - '0';
    int COL = position[1] - '0';

    if(ownershipBoard[ROW][COL] == P1_NORM_PIECE_ID){
        if(COL-1 >= 0){
            if(ownershipBoard[ROW-1][COL-1]== EMPTY_SPACE_ID){//Program sometimes accesses negative row elements but dosent fail (yet)
                arr.push_back((ROW-1)*10 + COL-1);
            }
            else if(ROW-2 >=0 && COL-2 >= 0){
                if((ownershipBoard[ROW-1][COL-1]==P2_NORM_PIECE_ID||ownershipBoard[ROW-1][COL-1]==P2_KING_PIECE_ID)
                    && ownershipBoard[ROW-2][COL-2] == EMPTY_SPACE_ID){
                    arr.push_back((ROW-2)*10 + COL-2);
                }
            }
        }

        if(COL+1 <= 7){
            if(ownershipBoard[ROW-1][COL+1]== EMPTY_SPACE_ID){
                arr.push_back((ROW-1)*10 + (COL+1));
            }
            else if(ROW-2 >=0 && COL+2 <= 7){
                if((ownershipBoard[ROW-1][COL+1]==P2_NORM_PIECE_ID||ownershipBoard[ROW-1][COL+1]==P2_KING_PIECE_ID)
                    && ownershipBoard[ROW-2][COL+2] == EMPTY_SPACE_ID){
                    arr.push_back((ROW-2)*10 + COL+2);
                }
            }
        }
    }
    else if(ownershipBoard[ROW][COL] ==P1_KING_PIECE_ID){
        if(COL-1 >= 0){
            if(ownershipBoard[ROW-1][COL-1]== EMPTY_SPACE_ID){//Program sometimes accesses negative row elements but dosent fail (yet)
                arr.push_back((ROW-1)*10 + COL-1);
            }
            else if(ROW-2 >=0 && COL-2 >= 0){
                if((ownershipBoard[ROW-1][COL-1]==P2_NORM_PIECE_ID||ownershipBoard[ROW-1][COL-1]==P2_KING_PIECE_ID)
                    && ownershipBoard[ROW-2][COL-2] == EMPTY_SPACE_ID){
                    arr.push_back((ROW-2)*10 + COL-2);
                }
            }
            
            if(ownershipBoard[ROW+1][COL-1]==EMPTY_SPACE_ID){
                arr.push_back((ROW+1)*10 + COL-1);
            }else if(ROW+2 <= 7 && COL-2>=0){
                if((ownershipBoard[ROW+1][COL-1]==P2_NORM_PIECE_ID||ownershipBoard[ROW+1][COL-1]==P2_KING_PIECE_ID)
                    &&ownershipBoard[ROW+2][COL-2] == EMPTY_SPACE_ID){
                        arr.push_back((ROW+2)*10 + COL-2);
                }
            }
        }

        if(COL+1 <= 7){
            if(ownershipBoard[ROW-1][COL+1]== EMPTY_SPACE_ID){
                arr.push_back((ROW-1)*10 + (COL+1));
            }
            else if(ROW-2 >=0 && COL+2 <= 7){
                if((ownershipBoard[ROW-1][COL+1]==P2_NORM_PIECE_ID||ownershipBoard[ROW-1][COL+1]==P2_KING_PIECE_ID)
                    && ownershipBoard[ROW-2][COL+2] == EMPTY_SPACE_ID){
                    arr.push_back((ROW-2)*10 + COL+2);
                }
            }

            if(ownershipBoard[ROW+1][COL+1]==EMPTY_SPACE_ID){
                arr.push_back((ROW+1)*10 + COL+1);
            }else if(ROW+2 <= 7 && COL+2<=7){
                if((ownershipBoard[ROW+1][COL+1]==P2_NORM_PIECE_ID||ownershipBoard[ROW+1][COL+1]==P2_KING_PIECE_ID)
                    &&ownershipBoard[ROW+2][COL+2] == EMPTY_SPACE_ID){
                        arr.push_back((ROW+2)*10 + COL+2);
                }
            }
        }
    }
    else if(ownershipBoard[ROW][COL] == P2_NORM_PIECE_ID){//Source of future errors?
        if(COL-1 >= 0){
            if(ownershipBoard[ROW+1][COL-1]== EMPTY_SPACE_ID){
                arr.push_back((ROW+1)*10 + COL-1);
            }
            else if(ROW+2 <= 7 && COL-2 >= 0){
                if((ownershipBoard[ROW+1][COL-1]==P1_NORM_PIECE_ID||ownershipBoard[ROW+1][COL-1]==P1_KING_PIECE_ID)
                    && ownershipBoard[ROW+2][COL-2] == EMPTY_SPACE_ID){
                    arr.push_back((ROW+2)*10 + COL-2);
                }
            }
        }

        if(COL+1 <= 7){
            if(ownershipBoard[ROW+1][COL+1]== EMPTY_SPACE_ID){
                arr.push_back((ROW+1)*10 + COL+1);
            }
            else if(ROW+2 <= 7 && COL+2 <= 7){
                if((ownershipBoard[ROW+1][COL+1]==P1_NORM_PIECE_ID||ownershipBoard[ROW+1][COL+1]==P1_KING_PIECE_ID)
                    && ownershipBoard[ROW+2][COL+2] == EMPTY_SPACE_ID){
                    arr.push_back((ROW+2)*10 + COL+2);
                }
            }
        }
    }
    else{
        if(COL-1 >= 0){
            if(ownershipBoard[ROW-1][COL-1]== EMPTY_SPACE_ID){//Program sometimes accesses negative row elements but dosent fail (yet)
                arr.push_back((ROW-1)*10 + COL-1);
            }
            else if(ROW-2 >=0 && COL-2 >= 0){
                if((ownershipBoard[ROW-1][COL-1]==P1_NORM_PIECE_ID||ownershipBoard[ROW-1][COL-1]==P1_KING_PIECE_ID)
                    && ownershipBoard[ROW-2][COL-2] == EMPTY_SPACE_ID){
                    arr.push_back((ROW-2)*10 + COL-2);
                }
            }
            
            if(ownershipBoard[ROW+1][COL-1]==EMPTY_SPACE_ID){
                arr.push_back((ROW+1)*10 + COL-1);
            }else if(ROW+2 <= 7 && COL-2>=0){
                if((ownershipBoard[ROW+1][COL-1]==P1_NORM_PIECE_ID||ownershipBoard[ROW+1][COL-1]==P1_KING_PIECE_ID)
                    &&ownershipBoard[ROW+2][COL-2] == EMPTY_SPACE_ID){
                        arr.push_back((ROW+2)*10 + COL-2);
                }
            }
        }

        if(COL+1 <= 7){
            if(ownershipBoard[ROW-1][COL+1]== EMPTY_SPACE_ID){
                arr.push_back((ROW-1)*10 + (COL+1));
            }
            else if(ROW-2 >=0 && COL+2 <= 7){
                if((ownershipBoard[ROW-1][COL+1]==P1_NORM_PIECE_ID||ownershipBoard[ROW-1][COL+1]==P1_KING_PIECE_ID)
                    && ownershipBoard[ROW-2][COL+2] == EMPTY_SPACE_ID){
                    arr.push_back((ROW-2)*10 + COL+2);
                }
            }

            if(ownershipBoard[ROW+1][COL+1]==EMPTY_SPACE_ID){
                arr.push_back((ROW+1)*10 + COL+1);
            }else if(ROW+2 <= 7 && COL+2<=7){
                if((ownershipBoard[ROW+1][COL+1]==P1_NORM_PIECE_ID||ownershipBoard[ROW+1][COL+1]==P1_KING_PIECE_ID)
                    &&ownershipBoard[ROW+2][COL+2] == EMPTY_SPACE_ID){
                        arr.push_back((ROW+2)*10 + COL+2);
                }
            }
        }
    }   
}

void displayPossibleMoves(std::vector<int>& arr){
    for(int i = 0; i < arr.size(); i++){
        std::cout << std::setfill('0') << std::setw(2) << arr[i] << " ";
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
    }
    return false;
}

void updateOwnershipBoard(std::string& positionOfPiece, std::string& positionToMoveTo, int playerTurn){
    int PIECE_ROW = positionOfPiece[0] - '0';
    int PIECE_COL = positionOfPiece[1] - '0';

    int MOVE_ROW = positionToMoveTo[0] - '0';
    int MOVE_COL = positionToMoveTo[1] - '0';

    int currentPiece = ownershipBoard[PIECE_ROW][PIECE_COL];
    ownershipBoard[PIECE_ROW][PIECE_COL] = EMPTY_SPACE_ID;
    ownershipBoard[MOVE_ROW][MOVE_COL] = currentPiece;

    if(abs(MOVE_ROW-PIECE_ROW) == 2){
        ownershipBoard[std::min(PIECE_ROW, MOVE_ROW) + 1][std::max(PIECE_COL, MOVE_COL) - 1] = EMPTY_SPACE_ID;
        // TODO: Work on the updating of the board to be displayed to be more effiecient later
        // checkerBoard[std::min(PIECE_ROW, MOVE_ROW) - 1][std::max(PIECE_COL, MOVE_COL) - 1] = EMPTY_SPACE;
    }
   
    if(playerTurn == 1 && MOVE_ROW == 0){
        ownershipBoard[MOVE_ROW][MOVE_COL] = P1_KING_PIECE_ID;
    }else if(playerTurn == 2 && MOVE_ROW == 7){
        ownershipBoard[MOVE_ROW][MOVE_COL] = P2_KING_PIECE_ID;
    }
}

//for debugging
void displayOwnershipBoard(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            std::cout << ownershipBoard[i][j];
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
int main(){
    setupOwnershipBoard();
    ownershipBoard[5][0] = P1_KING_PIECE_ID;
    setupCheckerBoard();
    int playerTurn = 1;
    while(true){
        std::cout << "Player " << playerTurn << "'s Turn\n\n";
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
                updateOwnershipBoard(positionOfPiece, choice, playerTurn);
                //displayOwnershipBoard();
                setupCheckerBoard();
                for(int i = 0; i < 100; i++){
                    std::cout << "-";
                }std::cout << '\n';
                hasAvailableMoves = true;
                
            }else{
                std::cout << "Piece chosen can't move anywhere! ";
                positionOfPiece = "CHANGED TO BREAK LOOP";
            }
        }
        playerTurn = (playerTurn == 1 ? 2: 1);
    }
}