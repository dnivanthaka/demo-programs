/*
 * =====================================================================================
 *
 *       Filename:  jumble.cpp
 *
 *    Description:  Word jumble game
 *
 *        Version:  1.0
 *        Created:  08/31/2012 12:41:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    enum fields {WORD, HINT, NUM_FIELDS};
    const int NUM_WORDS = 5;
    const string WORDS[NUM_WORDS][NUM_FIELDS] = 
    {
        {"wall", "Do you feel you're banging your head against something?"},
        {"glasses", "These might help to see the answer."},
        {"labored", "Going slowly, is it?"},
        {"persistent", "Keep at it."},
        {"jumble", "It's what the game is all about."}
    };

    srand( static_cast<unsigned int>(time(0)) );
    int choice = (rand() % NUM_WORDS);
    string theWord = WORDS[choice][WORD];
    string theHint = WORDS[choice][HINT];

    string jumble = theWord;
    int length = jumble.size();

    for( int i = 0; i < length; ++i ){
        int index1 = rand() % length;
        int index2 = rand() % length;

        char temp = jumble[index1];
        jumble[index1] = jumble[index2];
        jumble[index2] = temp;
    }

    cout << "\t\t\tWelcome to word jumble!\n\n";
    cout << "Unscramble the letters to make a word.\n";
    cout << "Enter 'hint' for a hint" << endl;
    cout << "Enter 'quit' to quit the game" << endl;
    cout << "The jumble is: " << jumble;

    string guess;
    cout << "\n\nYour guess: ";
    cin >> guess;

    while( (guess != theWord) && (guess != "quit") ){
        if( guess == "hint" ){
            cout << theHint;
        }else{
            cout << "Sorry, that's not it.";
        }

        cout << "\n\nYour guess:";
        cin >> guess;
    }

    if( guess == theWord ){
        cout << "\nThat's it! You guesses it!\n";
    }

    cout << "\nThanks for playing.\n";

    return 0;
}
