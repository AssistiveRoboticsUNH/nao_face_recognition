#include "../include/speech_recognition/speechrec.h"
#include <sstream>

using namespace std;

int main(int argc, char ** argv){
	ros::init(argc, argv, "speech_rec");
	SpeechRec s;
	//string words = " ";
	//cout << "What words would you like him to recognize:" << endl;
	//getline(cin, words);
	//cout << "You Entered: " << endl << words << endl;
	s.setVocab();
	s.startRec();
	return 0;
}
