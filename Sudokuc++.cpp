#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>

using namespace std;

const int table_size = 9;
int table[table_size][table_size];
// ya grid print kra ga 
void print_board(const int board[table_size][table_size]) {

    int i = 0;
    // yq loop mai rows mai lines mean grid print hon ga
    while (i < table_size) {
        if (i > 0) {
            if (i % 3 == 0) {
                cout << "---------------------\n";
            }
        }

        int j = 0;
        // Move this inside the outer loop
          // ya wala code col mai lines print krta hai 
        while (j < table_size) {
            if (j > 0) {
                if (j % 3 == 0) {
                    cout << "| ";
                }
            }

            if (board[i][j] == 0) {
                cout << "  ";
            }
            else {
                cout << board[i][j] << " ";
            }

            j++;
        }

        cout << endl;
        i++;
    }
}

// ya wala check krta hai aghr koi number same hai tu false generate nhi ho ga 
// matrix mai 

bool checkmatrix(int startRow, int startCol, int num) {

    for (int i = startRow; i < startRow + 3; i++) {

        for (int j = startCol; j < startCol + 3; j++) {
            if (table[i][j] == num) {

                return false;
            }
        }
    }
    return true;
}
// ya row mai check kra ga ka ya random number same tu nhi aghr same hua tu 
// ya false kr ka same ko remove kr da ga 

bool chkrow(int row, int num) {

    for (int j = 0; j < table_size; j++) {

        if (table[row][j] == num) {

            return false;
        }
    }
    return true;
}
// ya col mai check kra ga ka ya random number same tu nhi aghr same hua tu 
// ya false kr ka same ko remove kr da ga 

bool chkcol(int col, int num) {

    for (int i = 0; i < table_size; i++) {

        if (table[i][col] == num) {

            return false;
        }
    }
    return true;
}
// ya wala function use krda hai random number generate krna ka liya 
void init() {

    // everytime generate a new number 
    srand(time(0));

    for (int i = 0; i < table_size; i++) {

        for (int j = 0; j < table_size; j++) {
            table[i][j] = 0;
        }
    }



    int row, col, num;
    int count = 0;
    // ya condition is liya lagii hai ka 40 random number genarate hun sirf zayda nhi 

    while (count < 41) {

        row = rand() % table_size;
        col = rand() % table_size;
        num = rand() % 9 + 1;

        // Check if the current cell is empty (0)
        if (table[row][col] == 0) {

            if (checkmatrix(row - row % 3, col - col % 3, num)) {

                if (chkrow(row, num)) {
                    // Check if the number is valid in the current row and col
                    if (chkcol(col, num)) {

                        table[row][col] = num;
                        count++;
                    }
                }
            }
        }

    }
}

bool correct(const int board[table_size][table_size], int row, int col, int num) {

    bool isRowValid, isColValid, isMatrixValid;

    isRowValid = chkrow(row, num);

    isColValid = chkcol(col, num);

    isMatrixValid = checkmatrix(row - row % 3, col - col % 3, num);

    return isRowValid && isColValid && isMatrixValid;
}

// play game function 

void play_game() {
    int score = 0;
    int wrong_guess = 0;
    cout << "Initial Sudoku Board:" << endl;

    // Print board because we need a board here to play a game 
    print_board(table);


    // this is count the wrong gusses if the 3 gusses wrong 


   // jab thk true hai tu ya chalta raha ga 
    while (true) {

        int Row_Num, Col_Num, Num;


        cout << "Score of Game is :" << score << endl;
        cout << "Wrong_gusess are " << wrong_guess << endl;
        cout << "Enter -1 to return to the menu." << endl;
        cout << "Enter the row number (1-9): ";


        // row number jis mai number enter krna hai
        cin >> Row_Num;

        // aghar exist krna chahta ho tu -1 enter kr do
        if (Row_Num == -1) {
            cout << "Returning to the menu." << endl;
            return;
        }
        // col  number jis mai number enter krna hai

        cout << "Enter the column number (1-9), or enter -1 to return to the menu: ";
        cin >> Col_Num;

        // aghar exist krna chahta ho tu -1 enter kr do

        if (Col_Num == -1) {
            cout << "Returning to the menu." << endl;
            return;
        }

        cout << "Enter the number (1-9) to fill in the cell, or enter -1 to return to the menu: ";
        cin >> Num;

        if (Num == -1) {
            cout << "Returning to the menu." << endl;
            return;
        }

        // Validate input   1 sa bari aur 9 sa choti ya 9 huni chahiye 
        if (Row_Num < 1) {
            cout << "Invalid input. Row number must be greater than or equal to 1." << endl;
            continue;
        }
        if (Row_Num > 9) {
            cout << "Invalid input. Row number must be less than or equal to 9." << endl;
            continue;
        }
        if (Col_Num < 1) {
            cout << "Invalid input. Column number must be greater than or equal to 1." << endl;
            continue;
        }
        if (Col_Num > 9) {
            cout << "Invalid input. Column number must be less than or equal to 9." << endl;
            continue;
        }
        if (Num < 1) {
            cout << "Invalid input. Number must be greater than or equal to 1." << endl;
            continue;
        }
        if (Num > 9) {
            cout << "Invalid input. Number must be less than or equal to 9." << endl;
            continue;
        }


        Row_Num--;
        Col_Num--;




        if (table[Row_Num][Col_Num] == 0) {

            if (!correct(table, Row_Num, Col_Num, Num)) {

                cout << "Invalid input. Same number already exists in the same row or column." << endl;

                wrong_guess++;

                if (wrong_guess == 3) {
                    cout << "You have made three consecutive wrong guesses. Exiting game." << endl;
                    return;
                }
                continue;
            }



            wrong_guess = 0;

            table[Row_Num][Col_Num] = Num;

            score += 100;

            ofstream scoreFile("scores.txt", ios::app);

            if (scoreFile.is_open()) {

                // ya file mai cout kr ga 
                scoreFile << score << endl;

                scoreFile.close();
            }
            else {

                cout << "Error: Unable to save score." << endl;

            }

            cout << "Updated Sudoku Board:" << endl;

            // for clear the first board


            system("cls");

            print_board(table);

            bool Full = true;
            for (int i = 0; i < table_size; i++) {

                for (int j = 0; j < table_size; j++) {

                    if (table[i][j] == 0) {

                        Full = false;

                        break;
                    }
                }
                if (!Full) {

                    break;

                }
            }

            if (Full) {

                cout << "Congratulations! You have solved the Sudoku puzzle!" << endl;

                // Update score and save to file

                score += 100;
                // write kra ga aur pechala score ko append kr da ka next mai 
                ofstream scoreFile("scores.txt", ios::app);

                if (scoreFile.is_open()) {

                    // ya file mai cout kr ga 
                    scoreFile << score << endl;

                    scoreFile.close();
                }
                else {

                    cout << "Error: Unable to save score." << endl;

                }

                return;
            }
        }
        else {

            cout << "This cell is already filled. Please choose an empty cell." << endl;

        }
    }
}

void credits() {

    //  ya libaray slow krti ko text ko generate 

    this_thread::sleep_for(chrono::seconds(0));
    cout << "\t\t\t<================================================================================>" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\t\t\t|                                CREDITS                                          |" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\t\t\t<================================================================================>" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\t\t\t|               Sudoku Game created by Haseeb zahid                               |" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\t\t\t<================================================================================>" << endl;

    this_thread::sleep_for(chrono::seconds(1));
}

void instructions() {
    // ya instrution print kra ga

    this_thread::sleep_for(chrono::seconds(1));
    cout << setw(40) << "<================================================================================>" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << setw(40) << "|                                INSTRUCTIONS                                    |" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << setw(40) << "<================================================================================>" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << setw(40) << "| 1. Sudoku is played on a 9x9 grid." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << setw(40) << "| 2. The grid is divided into nine 3x3 subgrids, each containing 9 cells." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << setw(40) << "| 3. To solve the puzzle, each row, column, and subgrid must contain all the digits" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << setw(40) << "|    from 1 to 9 without repetition." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << setw(40) << "| 4. You need to fill in the missing numbers based on the above rules." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << setw(40) << "| 5. Enter the row, column, and number to fill the grid, or enter -1 to return to the" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << setw(40) << "| menu." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << setw(40) << "<================================================================================>" << endl;
    this_thread::sleep_for(chrono::seconds(1));

}

void display_score() {
    // ya  3 time max score print krna ka liya 

    cout << "Top Three Scores of All Time:" << endl;

    ifstream scorefile("scores.txt");// file name scores.txt

    if (scorefile.is_open()) {
        // open  file to add score 

        int max_score[3] = { 0 };

        int score;

        while (scorefile >> score) {

            for (int i = 0; i < 3; ++i) {   // three time loop 
                if (score > max_score[i]) {      // aghar score zayda ho ga phayla max sa tu score add ho jya ga max mai 

                    for (int j = 2; j > i; --j) {   //ya pher phayla max ko dusra py la jya ga 

                        max_score[j] = max_score[j - 1];
                    }

                    max_score[i] = score;   // ider zayda score save ho ga max score mai 

                    break;

                }
            }
        }
        scorefile.close();   // aur file close ho jya gii 

        for (int i = 0; i < 3; ++i) { // ya wali loop score print kara gii max three wala 

            cout << "Score " << i + 1 << " : " << max_score[i] << endl;
        }
    }
    else {

        cout << "No scores available." << endl;

    }
}

int main() {

    system("title Sudoku Game");

    system("color A");

    system("cls");


    init();


    cout << setw(40) << "***************************************************************" << endl;
    cout << setw(40) << "||***********************************************************||" << endl;
    cout << setw(40) << "||                                                           ||" << endl;
    cout << setw(40) << "||               WELCOME TO SUDOKU GAME!!!!!                 ||" << endl;
    cout << setw(40) << "||               Fill in the missing numbers                 ||" << endl;
    cout << setw(40) << "||                  Good Luck and Have Fun!                  ||" << endl;
    cout << setw(40) << "||                                                           ||" << endl;
    cout << setw(40) << "||***********************************************************||" << endl;
    cout << setw(40) << "***************************************************************" << endl;

    while (true)
    {

        // take a choice from the user to see the menu ka wo kiya krna chahta hai

        int choice;

        cout << endl << endl;

        // Printing lines with a delay of 1 second between each line
        cout << "\t\t\t<================================================================================>" << endl;
        this_thread::sleep_for(chrono::seconds(1));

        cout << "\t\t\t|                                OPTIONS                                          |" << endl;
        this_thread::sleep_for(chrono::seconds(1));

        cout << "\t\t\t<================================================================================>" << endl;
        this_thread::sleep_for(chrono::seconds(1));

        cout << "\t\t\t| [1] Play Sudoku" << endl;
        this_thread::sleep_for(chrono::seconds(1));

        cout << "\t\t\t| [2] View the Sudoku Board" << endl;
        this_thread::sleep_for(chrono::seconds(1));

        cout << "\t\t\t| [3] Instructions" << endl;
        this_thread::sleep_for(chrono::seconds(1));

        cout << "\t\t\t| [4] Credits" << endl;
        this_thread::sleep_for(chrono::seconds(1));

        cout << "\t\t\t| [5] Show Scores" << endl;
        this_thread::sleep_for(chrono::seconds(1));

        cout << "\t\t\t| [6] Exit" << endl;
        this_thread::sleep_for(chrono::seconds(1));

        cout << "\t\t\t<================================================================================>" << endl;
        this_thread::sleep_for(chrono::seconds(1));

        cout << "\t\t\tEnter your choice: ";

        // now enter a choice here between 1 to 6

        system("color B"); // Change color to blue

        cin >> choice;

        system("color A"); // Change color back to green

        system("cls"); // for clear screen 

        switch (choice) {

        case 1:

            init();
            // ya wala case game khelna ka liya use hota hai 

            play_game();

            break;
        case 2:
            // ya board print kra ga 
            print_board(table);

            break;
        case 3:

            instructions();
            // ya wala case game ko kesa khalna hai us ka liya 
            break;

        case 4:
            credits();          // ya wala case game bana wala ka name print kra ga simple 
            break;

        case 5:
            display_score();
            // ya wala case game ka score batya ga kitna hai 
            break;

        case 6:
            //  ya game sa niklana ka liya haia 
            cout << " Good bye Take care ):" << endl;
            return 0;

        default:

            cout << "Invalid choice. Please enter a valid option." << endl;
        }

        system("pause");

        system("cls");
    }



    system("pause");
    return 0;
}
