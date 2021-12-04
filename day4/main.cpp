#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

struct Cell {
    int num;
    bool occupied;
};

struct Board {
    std::vector<std::vector<Cell> > board;
};

struct Game {
    std::vector<int> nums;
    std::vector<Board> boards;
};

Game parseGame();
int getWinningSum(Game& game);
int getLosingSum(Game& game);

int main() {
    Game game = parseGame();

    std::cout << game.nums.size() << std::endl;
    std::cout << game.boards.size() << std::endl;
    std::cout << "winner: " << getWinningSum(game) << std::endl;
    std::cout << "loser: " << getLosingSum(game) << std::endl;
}


void markBoard(Board& board, int num) {
    for(int i=0; i<board.board.size(); ++i) {
        for(int j=0; j<board.board.size(); ++j) {
            if(board.board[i][j].num == num) {
                board.board[i][j].occupied = true;
            }
        }
    }
}

int sumUnoccupiedBoard(Board& board) {
    int sum = 0;
    for(int i=0; i<board.board.size(); ++i) {
        for(int j=0; j<board.board.size(); ++j) {
           if(board.board[i][j].occupied) {
               continue;
           }
           sum += board.board[i][j].num;
        }
    }
    return sum;
}

bool boardFinished(Board& board) {
    bool complete = true;
    for(int row=0; row<board.board.size(); ++row) {
        for(int col=0; col<board.board.size(); ++col) {
            complete &= board.board[row][col].occupied;
        }
        if(complete) {
            return true;
        }
        complete = true;
    }

    complete = true;
    for(int col=0; col<board.board.size(); ++col) {
        for(int row=0; row<board.board.size(); ++row) {
            complete &= board.board[row][col].occupied;
        }
        if(complete) {
            return true;
        }
        complete = true;
    }

    complete = true;
    for(int row=0, col = 0; row < board.board.size(); ++row, ++col) {
        complete &= board.board[row][col].occupied;
    }
    if(complete) {
        return true;
    }
    complete = true;

    for(int row=0, col=board.board.size(); row < board.board.size(); ++row, --col) {
        complete &= board.board[row][col].occupied;
    }
    return complete;
}

void printBoard(Board& board) {
    for(int i=0; i<board.board.size(); ++i) {
        for(int j=0; j<board.board.size(); ++j) {
            char c = 'u';
            if(board.board[i][j].occupied) {
                c = 'o';
            }
            std::cout << " " << board.board[i][j].num << c << " ";
        }
        std::cout << std::endl;
    }
}

int getLosingSum(Game& game) {
    int index=0;
    for(;index < game.nums.size();) {
        int num = game.nums[index++];
        std::vector<int> toRemove;
        for(int i=0; i<game.boards.size(); ++i) {
            markBoard(game.boards[i], num);
            bool isBoardFinished = boardFinished(game.boards[i]);
            if(isBoardFinished) {
                if(game.boards.size() == 1) {
                    return sumUnoccupiedBoard(game.boards[i]) * num;
                }
                toRemove.push_back(i);
            }
        }
        for(int i=toRemove.size()-1; i>=0; --i) {
            game.boards.erase(game.boards.begin() + toRemove[i]);
        }
    }
    return -1;
}

int getWinningSum(Game& game) {
    int index = 0;
    for(;;) {
        int num = game.nums[index++];
        for(int i=0; i<game.boards.size(); ++i) {
            markBoard(game.boards[i], num);
            if(boardFinished(game.boards[i])) {
                printBoard(game.boards[i]);
                return sumUnoccupiedBoard(game.boards[i]) * num;
            }
        }
    }
}

std::vector<int> parseNums(std::string line) {
    for(int i=0; i<line.size(); ++i) {
        if(line[i] == ',') {
            line[i] = ' ';
        }
    }
    std::stringstream ss(line);
    int num;
    std::vector<int> nums;
    while(ss >> num) {
        nums.push_back(num);
    }
    return nums;
}

std::vector<Cell> parseBoardLine(std::string line) {
    std::stringstream ss(line);

    std::vector<Cell> cells;
    std::string num;
    for(int i=0; i<5; ++i) {
       ss >> num;
       int numInt = std::stoi(num);
       Cell cell;
       cell.occupied = false;
       cell.num = numInt;
       cells.push_back(cell);
    }
    return cells;
}

Game parseGame() {
    std::ifstream input("input.txt");
    Game game;

    Board* board = NULL;
    std::string line;
    int count = 0;
    for(;;) {
       std::getline(input, line);
       if(input.fail()) {
           break;
       } else if(line == "") {
           if(board) {
               game.boards.push_back(*board);
               delete board;
           }
           board = new Board;
           continue;
       }

       if(count++ == 0) {
          game.nums = parseNums(line);
           continue;
       }
       board->board.push_back(parseBoardLine(line));
    }

    return game;
}
