/* text concordance program from class 1107, but using the STL as much as
 *  possible to avoid reinventing the wheel
 * 
 * written by Dalton Maahs
 * ****************************************************************************/

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//map word->line positions
typedef map<string, vector<int> > Concordance; // Concordance: words -> line numbers

const int SIZE = 26; //number of letter in the alphabet

void read(istream &in, Concordance concords[SIZE]);
void display(ostream &out, Concordance (&concords)[SIZE]);  //pass the array by reference so i can use range based for loops on it

int main() {
    //declare an array of concordances for each letter
    Concordance concords[SIZE];
	string document;
	
	cout << "Enter file path: ";
	cin >> document;
	
    ifstream in("document.txt");
    if (!in) {
		cout << "Err: File not Found.\n";
		return 1;
	}

    //read words and line numbers into the concordance
    read(in, concords);

    display(cout, concords);

    return 0;
}

void display(ostream &out, Concordance (&concords)[26]) {
    for (const Concordance &c : concords) {  //for each concordance, c
        if (!c.empty()) {
            out << c.begin()->first[0] << ":";  //display the first letter

            for (const auto &[word, lines] : c) {  //for each word and vector of lines in the concordance c
                out << "\t" << word << " \t\t(";  //display the word

                for (int n : lines)  //display each line number
                    out << n << " ";
                out << ")" << endl;
            }
        }
    }
}

void read(istream &in, Concordance concords[SIZE]) {
    istringstream ss;
    string temp;
    int line = 1;

    //get a new line
    while (getline(in, temp)) {  //
        line++;  //increment linenumber
        ss.str(temp);  //set ss' buffer to an entire line

        //iterate though each word on the line
        while (ss >> temp) {  //processe each word

            //remove non-alpha chars at front
            while (temp.size() > 0 && !isalpha(temp[0])) {
                temp = temp.substr(1, temp.size());
            }

            //remmove non-alpha char at end
            while (temp.size() > 0 && !isalpha(temp[temp.size() - 1])) {
                temp = temp.substr(0, temp.size() - 1);
            }

            //set to all upper
            for (char &ch : temp)
                ch = toupper(ch);

            //if temp isn't empty after removing non-alpha characters
            //then add the line number to the key of the appropriate concordance
            if (temp.size() > 0)
                concords[temp[0] - 'A'][temp].push_back(line);
        }
        ss.clear();
    }
}