#include <iostream>
#include <limits>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
using namespace std;

int counter=0;
const int SIZE = 3;
char board[SIZE][SIZE] = {
    {'_', '_', '_'},
    {'_', '_', '_'},
    {'_', '_', '_'}
};

bool isMovesLeft() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

int evaluate() {
    // Rows
    for (int row = 0; row < SIZE; row++)
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2]) {
            if (board[row][0] == 'X') return +10;
            if (board[row][0] == 'O') return -10;
        }

    // Columns
    for (int col = 0; col < SIZE; col++)
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col]) {
            if (board[0][col] == 'X') return +10;
            if (board[0][col] == 'O') return -10;
        }

    // Diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == 'X') return +10;
        if (board[0][0] == 'O') return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == 'X') return +10;
        if (board[0][2] == 'O') return -10;
    }

    return 0;
}

int minimax(bool isMax) {
    int score = evaluate();

    if (score == 10 || score == -10) return score;
    if (!isMovesLeft()) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (board[i][j] == '_') {
                    board[i][j] = 'X';
                    counter++;
                    best = max(best, minimax(false));
                    board[i][j] = '_';
                }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (board[i][j] == '_') {
                    board[i][j] = 'O';
                    counter++;
                    best = min(best, minimax(true));
                    board[i][j] = '_';
                }
        return best;
    }
}



pair<int, int> findBestMove(char player) {
    int bestVal = (player == 'X') ? -1000 : 1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == '_') {
                board[i][j] = player;
                int moveVal = minimax(player == 'O');
                board[i][j] = '_';

                if ((player == 'X' && moveVal > bestVal) ||
                    (player == 'O' && moveVal < bestVal)) {
                    bestMove.first = i;
                    bestMove.second = j;
                    bestVal = moveVal;
                }
            }

    return bestMove;
}

void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
    cout << "----------\n";
}

void randomFirstMove() {

    int row = rand() % SIZE;
    int col = rand() % SIZE;
    while (board[row][col] != '_') {
        row = rand() % SIZE;
        col = rand() % SIZE;
    }
    board[row][col] = 'X';  // اللاعب الذي يبدأ هو 'X'
    cout << "Player X makes the first random move at position (" << row << ", " << col << ")\n";
}

int main() {
    //srand(time(0));
    pair<int, int> bestMove = findBestMove('X');
    board[bestMove.first][bestMove.second] = 'X';
    //randomFirstMove();  // الخطوة الأولى عشوائيًا من AI
    printBoard();
    char currentPlayer = 'O';

    while (isMovesLeft() && evaluate() == 0) {
        bestMove = findBestMove(currentPlayer);
        board[bestMove.first][bestMove.second] = currentPlayer;

        cout << "Player " << currentPlayer << " moved to (" << bestMove.first << ", " << bestMove.second << ")\n";
        printBoard();

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    int result = evaluate();
    if (result == 10)
        cout << "X wins!\n";
    else if (result == -10)
        cout << "O wins!\n";
    else
        cout << "It's a draw!\n";


    cout<<"count\t"<<counter<<endl;

    return 0;
}
