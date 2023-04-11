#include <iostream>
#include "strutils.h"

using namespace std;

bool word_isalpha(string word) {

	int len = word.length(), count = 0;

	for (int i=0; i < len; i++) {
	if (isalpha(word[i])) { count++; }		
	}

	if (count == len) {return true;}
	else {return false;}
}

int string_count(string entered_String, string wanted_Character) {

	int count = 0;

	for (int i = 0; i < entered_String.length(); i++) {
		if (entered_String[i] == wanted_Character[0]) {count++;}
	}

	return count;
}

void hang_the_man(int number, string wordfn){

	if (number == 1) {cout << "You have no free guess left." << endl << "The word is: " << wordfn << endl;}
	else if (number == 2) {cout << "You have lost a leg!" << endl << "The word is: " << wordfn << endl;}
	else if (number == 3) {cout << "You have lost a leg!" << endl << "The word is: " << wordfn << endl;}
	else if (number == 4) {cout << "You have lost an arm!" << endl << "The word is: " << wordfn << endl;}
	else if (number == 5) {cout << "You have lost an arm!" << endl << "The word is: " << wordfn << endl;}
	else if (number == 6) {cout << "You have lost a head! GAME OVER!" << endl;}

}



int main() {

	cout << "Welcome to the HANGMAN GAME" << endl << "---------------------------" << endl;

	string player1, player2, mainword; 

	cout << "Player one, please enter your name: " ; cin >> player1;
	cout << "Player two, please enter your name: " ; cin >> player2;
	cout << "OK " << player1 << " and " << player2 << ". Let's start the game!" << endl;
	cout << player1 << ", please input the word you want " << player2 << " to guess: "; cin >> mainword;	


	while (true)
	{ if (word_isalpha(mainword)) {break;}
	else { cout << "Invalid word! Try again." << endl; cout << player1 << ", please input the word you want Baris to guess: "; cin >> mainword;} }

	ToLower(mainword);
	
	string hidden = ""; for (int i = 0; i < mainword.length(); i++) { hidden += "-"; }

	cout << player2 << ", you have 1 free guess, after that you will lose limbs!" << endl << "The word is: " << hidden << endl;


	string option, guessed_letter, guessed_letters = "", guessed_word; int wrong_guesses = 0;

	while (true) {

		if (wrong_guesses == 6) { cout << player2 << " lost the game :("; break;}
		else {

		cout << player2 << ", do you want to guess the word(1) or guess a letter(2)? "; cin >> option;
		
		if (option == "2") {

		cout << "Your guess: "; cin >> guessed_letter; 
		if (guessed_letter.length() != 1) {cout << "Invalid entry! Try again." << endl << "The word is: " << hidden << endl;} 
		else {
			if (word_isalpha(guessed_letter)) {
				if (string_count(guessed_letters, guessed_letter) == 0) {
					ToLower(guessed_letter);
				if (string_count(mainword, guessed_letter) == 0) { wrong_guesses++; hang_the_man(wrong_guesses, hidden); guessed_letters += guessed_letter; } 
				else {  for (int i = 0; i < mainword.length(); i++) {if (mainword[i] == guessed_letter[0]) { hidden[i] = guessed_letter[0]; }}  
				cout << "The word is: " << hidden << endl; guessed_letters += guessed_letter; 
				if (hidden == mainword) { cout << "Congratulations " << player2 << ", you won!" << endl << player2 << " won the game!"; break;} } 
				} 
				else { cout << "Guess entered before! Try again." << endl << "The word is: " << hidden << endl; } 
			} 
			else {cout << "Invalid entry! Try again." << endl << "The word is: " << hidden << endl;} 
				}
		}  

		else if (option == "1") {

			cout << "Your guess: "; cin >> guessed_word;

			if (word_isalpha(guessed_word)) { 
				ToLower(guessed_word);
				if (guessed_word == mainword) { cout << "The word is: " << mainword << endl << "Congratulations " << player2 << ", you won!" << endl << player2 << " won the game!"; break; } 
				else { wrong_guesses++; hang_the_man(wrong_guesses, hidden); }
			} 
			else { cout << "Invalid entry! Try again." << endl << "The word is: " << hidden << endl; }
		   } 

		else { cout << "Invalid option!" << endl << "The word is: " << hidden << endl; }

		} 
    }

	return 0 ;
}
