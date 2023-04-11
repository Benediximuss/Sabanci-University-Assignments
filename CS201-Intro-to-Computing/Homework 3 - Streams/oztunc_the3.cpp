#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string fixer(string text) {

	char last_char = text[text.length()-1];

	if (last_char == " "[0] || last_char == "\n"[0] || last_char == "\r"[0]) { text = text.substr(0,text.length()-1); }
	
	return text;

}

int index_word(string dom_text, string target_word) {

	string temp_word = "";
	int temp_word_count = 0, target_index = 999;


	for (int i = 0; i < dom_text.length(); i++) {

		if (dom_text[i] != " "[0]) { temp_word += dom_text[i]; }

		if ( dom_text[i] == " "[0] || i == (dom_text.length() - 1) ) { 
			if (temp_word != "") { 
				temp_word_count += 1;
				if (temp_word == target_word) { target_index = temp_word_count; break;}
		} 
	temp_word = ""; }
	}
	
	return target_index;

}




int main() {

	cout << "Hello and welcome to the Hogwarts house sorting hat program!" << endl << "When I call your name, you'll come forth, I shall place the sorting hat on your head, and you will be sorted into your houses." << endl;
	
	string line, filename;
	ifstream input;
	string animal_list, monster_list, personality_list, spell_list, trait_list, class_list;

	while (true) {
		cout << "Enter the name of the key file: "; cin >> filename;
		input.open(filename.c_str());
		if (input.fail()) { cout << "Error: Cannot open file " << filename << endl;}
		else {
			int count = 0;
			while (getline(input, line)) {
				line = fixer(line);
				if (count == 0) {animal_list = line;}
				else if (count == 1) {monster_list = line;}
				else if (count == 2) {personality_list = line;}
				else if (count == 3) {spell_list = line;}
				else if (count == 4) {trait_list = line;}
				else if (count == 5) {class_list = line;}
				count += 1;
			}
			input.close();
			break;
		} 
	} 

	

	string word = "", name, surname, animal, monster, personality, spell, trait, clas, house; 
	int word_number, points;

	while (true) {

		string filename2;

		cout << "Enter the name of the answer file: "; cin >> filename2;

		ifstream input2;

		input2.open(filename2.c_str());

		if (input2.fail()) { cout << "Error: Cannot open file " << filename2 << endl;}
		else {
			while (getline(input2, line)) {

				if (line != "" && line != "\n" && line != "\r") { 

					line = fixer(line);

					word_number = 0;
					points =  0;

					for (int i = 0; i < line.length(); i++) {

					if (line[i] != " "[0]) { word += line[i]; }

					if ( line[i] == " "[0] || i == (line.length() - 1) ) { 
					if (word != "") { word_number += 1;
		
					if (word_number == 1) { name = fixer(word); } 
					else if (word_number == 2) { surname = word; }
						else if (word_number == 3) { animal = word; }
						else if (word_number == 4) { monster = word; }
						else if (word_number == 5) { personality = word; }
						else if (word_number == 6) { spell = word; }
						else if (word_number == 7) { trait = word; }
						else if (word_number == 8) { clas = word; }
											
											} 
							word = ""; }
						}

						points = index_word(animal_list, animal) + index_word(monster_list, monster) + index_word(personality_list, personality) + index_word(spell_list, spell) + index_word(trait_list, trait) + index_word(class_list, clas);

						if (points < 10) {house = "Hufflepuff";}
						else if (10 <= points && points < 15) {house = "Ravenclaw";}
						else if (15 <= points && points < 21) {house = "Gryffindor";}
						else if (21 <= points) {house = "Slytherin";}

						cout << "Oh! we have " << name << " " << surname << " under the sorting hat. " << name << ", you scored " << points << " points, you are a " << house << "!" << endl;
				}
			}
			input2.close();
			break;
		}
	}

	

	return 0;
}

