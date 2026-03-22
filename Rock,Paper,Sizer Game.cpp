#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Function prototypes
void showMenu();
int getPlayerChoice();
int getComputerChoice(int rockCount, int paperCount, int scissorCount);
string determineWinner(int player, int computer);
string choiceToWord(int choice);
void showScoreboard(int playerScore, int computerScore, int draws);

// ================= MAIN =================
int main()
{
    srand(time(0));

    char playAgain;

    // AI memory
    int rockCount = 0, paperCount = 0, scissorCount = 0;

    // Scoreboard
    int playerScore = 0, computerScore = 0, draws = 0;

    cout << "===== SMART ROCK PAPER SCISSORS =====\n";

    do
    {
        showMenu();

        int player = getPlayerChoice();

        // Update history for AI learning
        if (player == 1) rockCount++;
        else if (player == 2) paperCount++;
        else scissorCount++;

        int computer = getComputerChoice(rockCount, paperCount, scissorCount);

        cout << "\nYou chose: " << choiceToWord(player) << endl;
        cout << "Computer chose: " << choiceToWord(computer) << endl;

        string result = determineWinner(player, computer);
        cout << "\nResult: " << result << endl;

        // Update scores
        if (result == "You Win!") playerScore++;
        else if (result == "Computer Wins!") computerScore++;
        else draws++;

        // Show scoreboard
        showScoreboard(playerScore, computerScore, draws);

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\nFinal ";
    showScoreboard(playerScore, computerScore, draws);

    cout << "\nThanks for playing!\n";
    return 0;
}

// ================= MENU =================
void showMenu()
{
    cout << "\n1. Rock\n";
    cout << "2. Paper\n";
    cout << "3. Scissors\n";
}

// ================= INPUT VALIDATION =================
int getPlayerChoice()
{
    int choice;

    while (true)
    {
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter numbers only.\n";
            continue;
        }

        if (choice < 1 || choice > 3)
        {
            cout << "Choice must be between 1 and 3.\n";
            continue;
        }

        return choice;
    }
}

// ================= SMART AI =================
int getComputerChoice(int rockCount, int paperCount, int scissorCount)
{
    // First few rounds random
    if (rockCount + paperCount + scissorCount <= 3)
        return rand() % 3 + 1;

    // Predict most frequent player move
    if (rockCount >= paperCount && rockCount >= scissorCount)
        return 2; // Paper beats Rock

    else if (paperCount >= rockCount && paperCount >= scissorCount)
        return 3; // Scissors beats Paper

    else
        return 1; // Rock beats Scissors
}

// ================= WORD CONVERSION =================
string choiceToWord(int choice)
{
    if (choice == 1) return "Rock";
    if (choice == 2) return "Paper";
    return "Scissors";
}

// ================= WINNER LOGIC =================
string determineWinner(int player, int computer)
{
    if (player == computer)
        return "Draw!";

    if ((player == 1 && computer == 3) ||
        (player == 2 && computer == 1) ||
        (player == 3 && computer == 2))
        return "You Win!";

    return "Computer Wins!";
}

// ================= SCOREBOARD =================
void showScoreboard(int playerScore, int computerScore, int draws)
{
    cout << "\n===== SCOREBOARD =====\n";
    cout << "Player Wins   : " << playerScore << endl;
    cout << "Computer Wins : " << computerScore << endl;
    cout << "Draws         : " << draws << endl;
}
