#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

int main() {
	
	ifstream input("SPAMTrain.label");
	if(input.fail()) {
		cerr << "Erro na abertura do arquivo.\n";
		exit(1);
	}

	vector<string> filenames;
	vector<bool> labels;
	
	bool isSpam;
	string name;
	while(!input.eof()) {
		input >> isSpam;
		input >> name;
		//cout << isSpam << name;
		labels.push_back(isSpam);
		filenames.push_back(name);
	}

	int nSpam = 0,nHam = 0,nSpamWords = 0, nHamWords = 0;

	string nomeEmail,s;
	int num;
	
	map<string,int> spamWords, hamWords, uniqueWords;

	//for(itNames = filenames.begin(), itLabels = labels.begin(); itNames!=filenames.end(); itLabels++,itNames++) {
	int i;
	for(i = 0; i < 0.8*filenames.size(); i++)	{
		input.close();
		input.open(("DATA/" + filenames[i]).c_str());
		//cout << filenames[i];
		if(input.fail()) {
			cerr << "Erro na abertura do arquivo.\n";
			exit(1);
		}

		if(labels[i])
			nHam++;
		else
			nSpam++;


		while(true) {
			input >> s;
			if(input.eof())
				break;
			if(labels[i]) {
				hamWords[s]++;
				nHamWords++;
			} else {
				spamWords[s]++;
				nSpamWords++;
			}
			uniqueWords[s] = 1;
		}
	}

	cout << spamWords.size() << " " << hamWords.size() << " " << uniqueWords.size() << endl;
	
	double threshold;
	double k = 1;
	double pSpam = (nSpam + k)/(nHam + nSpam + 2), pHam = 1 - pSpam;
	double pm_spam,pm_ham,pm,x_spam,x_ham;
	map<string,int>::iterator it;

	double pSpam_m;
	double mediaPSpam = 0;
	int count = 0,correctPredictions = 0;
	for(;i < 0.9*filenames.size();i++) {
		input.close();
		input.open(("DATA/" + filenames[i]).c_str());

		if(input.fail()) {
			cerr << "Erro na abertura do arquivo.\n";
			exit(1);
		}

		pm = pm_spam = pm_ham = 0;
		cout << endl << filenames[i] << " ";// << endl;

		while(true) {
			input >> s;
			if(input.eof())
				break;
			
			it = spamWords.find(s);
			if(it != spamWords.end()) {
				x_spam = (it->second + k)/(nSpamWords + k*uniqueWords.size());
				//cout << it->second << "pms" << pm_spam << " ";
			} else {
				x_spam = k/(nSpamWords + k*uniqueWords.size());
			}
			pm_spam += log10(x_spam);

			it = hamWords.find(s);
			if(it != hamWords.end()) {
				x_ham = (it->second + k)/(nHamWords + k*uniqueWords.size());
				//cout << it->second << "pmh" << pm_ham << " ";
			} else {
				x_ham = k/(nHamWords + k*uniqueWords.size());
			}
			pm_ham += log10(x_ham);
			cout << "_pm_spam: " << pm_spam << " _pm_ham: " << pm_ham;
		}
		pm_ham += log10(pHam);
		pm_spam += log10(pSpam);

		if(labels[i]==(pm_spam < pm_ham)) {
			
		}
		cout << "\n_label: " << labels[i] << " _media: " << mediaPSpam << " _sum: " << pow(10,log10(pSpam)+log10(pm_spam)-log10(pm)) << endl ;
	}
	cout << mediaPSpam << endl;
	threshold = mediaPSpam/count;
	cout << "Threshold: " << threshold*100 << "%" << endl;

	for(;i<filenames.size();i++) {

	}

	return 0;
}