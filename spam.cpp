#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main() {
	
	ifstream input,inputLabel("SPAMTrain.label");
	if(inputLabel.fail()) {
		cerr << "Erro na abertura do arquivo.\n";
		exit(1);
	}

	int nSpam = 0,nHam = 0;

	string nomeEmail,s;
	int num;
	

	map<string,int> spamWords, hamWords, uniqueWords;

	while(!inputLabel.eof()) {
		
		inputLabel >> num;
		inputLabel >> nomeEmail;
		if(num)
			nHam++;
		else
			nSpam++;

		s = "DATA/" + nomeEmail;

		input.close();
		input.open(s.c_str());

		if(input.fail()) {
			cerr << "Erro na abertura do arquivo.\n";
			exit(1);
		}

		while(true) {
			input >> s;
			if(input.eof())
				break;
			if(num) {
				hamWords[s]++;
			}
			else
				spamWords[s]++;
			uniqueWords[s] = 1;
		}
	}
	
	
}