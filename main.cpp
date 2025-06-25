#include <bits/stdc++.h>
using namespace std;

class Game {
public:
    vector<char> board = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

    char player(const vector<char>& s) {
        int movesPlayed = 0;
        for (char m : s) {
            if (m != ' ') movesPlayed++;
        }
        return movesPlayed % 2 == 0 ? 'X' : 'O';
    }

    vector<int> actions(const vector<char>& s) {
        vector<int> legalMoves;
        for (int i = 0; i < 9; i++) {
            if (s[i] == ' ') legalMoves.push_back(i);
        }
        return legalMoves;
    }

    void result(vector<char>& s, int a) {
        char currentPlayer = player(s);
        s[a] = currentPlayer;
    }

    bool terminal(const vector<char>& s) {
        // Check win conditions
        vector<vector<int>> winConditions = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
            {0, 4, 8}, {2, 4, 6}
        };
        for (auto cond : winConditions) {
            if (s[cond[0]] != ' ' && s[cond[0]] == s[cond[1]] && s[cond[1]] == s[cond[2]])
                return true;
        }
        // Check for draw
        for (char c : s) {
            if (c == ' ') return false;
        }
        return true;
    }

    int utility(const vector<char>& s) {
        vector<vector<int>> winConditions = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
            {0, 4, 8}, {2, 4, 6}
        };
        for (auto cond : winConditions) {
            if (s[cond[0]] != ' ' && s[cond[0]] == s[cond[1]] && s[cond[1]] == s[cond[2]]) {
                return s[cond[0]] == 'X' ? 1 : -1;
            }
        }
        return 0; // Draw
    }
};

void printboard(const vector<char>& s) {
    system("clear"); 
    for (int i = 0; i < 9; ++i) {
        if (s[i] == ' ')
            cout << i;
        else
            cout << s[i];
        if (i % 3 == 2)
            cout << endl;
        else
            cout << " ";
        // if (i == 2 || i == 5) cout << "\n";  
    }
}

int main() {
    Game game;
    vector<char> board = game.board;

    cout << endl << "*******************************************" << endl;
    cout << "Welcome" << endl;
    cout << "Play and Enjoy Tic Tac Toe" << endl;
    cout << "Player X always plays first." << endl;
    cout << "Game board Design: " << endl;
    cout << 0 << " " << 1 << " " << 2 << endl;
    cout << 3 << " " << 4 << " " << 5 << endl;
    cout << 6 << " " << 7 << " " << 8 << endl;
    cout << "Enter the number where you want to play a move" << endl;

    while (!game.terminal(board)) {
        printboard(board);
        char current = game.player(board);
        cout << "Player " << current << " Turn: ";

        if (current == 'X') {
            int input;
            cin >> input;
            vector<int> legal = game.actions(board);
            if (find(legal.begin(), legal.end(), input) == legal.end()) {
                cout << "Invalid move. Try again." << endl;
                continue;
            }
            game.result(board, input);
        } else {
            // AI picks random move
            vector<int> legal = game.actions(board);
            int ai_move = legal[rand() % legal.size()];
            cout << "AI chooses: " << ai_move << endl;
            game.result(board, ai_move);
        }
    }
    printboard(board);
    int score = game.utility(board);
    if (score == 1) cout << "X wins!" << endl;
    else if (score == -1) cout << "O wins!" << endl;
    else cout << "It's a draw!" << endl;
}
