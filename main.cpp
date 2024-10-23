#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <list>
#include <string>

using namespace std;

list<string> aiMoves;
string pc, ec;
char letter, eletter, lguess;
int number, enumber, nguess;
bool pwin = false, ewin = false;

void defLetter() {
    cout << "Enter your base coordinate (Letter, A - C): " << endl;
    cin >> letter;
    letter = toupper(letter);
    if (letter == 'A' || letter == 'B' || letter == 'C') {
        cout << "You entered: " << letter << endl;
    } else {
        cout << "Please enter a different letter." << endl;
        defLetter();
    }
}

void defNumber() {
    cout << "Enter your base coordinate (Number, 1-3): " << endl;
    cin >> number;
    if (number > 3 || number < 1) {
        cout << "Please enter a different number." << endl;
        defNumber();
    } else {
        cout << "You entered: " << to_string(number) << endl;
    }
}

void defAiLetter() {
    int temp = rand() % 3;
    if (temp == 0) {
        eletter = 'A';
    } else if (temp == 1) {
        eletter = 'B';
    } else {
        eletter = 'C';
    }
}

void defAiNumber() {
    enumber = rand() % 3 + 1;
}

void playerMoveLetter() {
    cout << "Guess the enemy coordinate's letter (Letter, A - C): " << endl;
    cin >> lguess;
    lguess = toupper(lguess);
    if (lguess == 'A' || lguess == 'B' || lguess == 'C') {
        cout << "You entered: " << lguess << endl;
    } else {
        cout << "Please enter a different letter." << endl;
        playerMoveLetter();
    }
}

void playerMoveNumber() {
    cout << "Guess the enemy coordinate's number (Number, 1-3): " << endl;
    cin >> nguess;
    if (nguess > 3 || nguess < 1) {
        cout << "Please enter a different number." << endl;
        playerMoveNumber();
    } else {
        cout << "You entered: " << to_string(nguess) << endl;
    }
}

bool isDuplicate(string move) {
    for (const string& m : aiMoves) {
        if (m == move) {
            return true;
        }
    }
    return false;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    defAiLetter();
    defAiNumber();

    ec = eletter + to_string(enumber);

    defLetter();
    defNumber();

    pc = letter + to_string(number);
    cout << "Your coordinate is: " << pc << endl;

    while (!pwin && !ewin) {
        playerMoveLetter();
        playerMoveNumber();
        string temp = lguess + to_string(nguess);
        if (temp == ec) {
            cout << "You win!" << endl;
            pwin = true;
        } else {
            string aiGuess;
            do {
                defAiNumber();
                defAiLetter();
                aiGuess = eletter + to_string(enumber);
            } while (isDuplicate(aiGuess));

            aiMoves.push_back(aiGuess);
            cout << "The enemy guessed: " << aiGuess << endl;

            if (aiGuess == pc) {
                cout << "You lose!" << endl;
                ewin = true;
            }
        }
    }
    return 0;
}
