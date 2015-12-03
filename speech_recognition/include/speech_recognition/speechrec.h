#ifndef SPEECHREC_H
#define SPEECHREC_H

#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_srvs/Empty.h>
#include <nao_msgs/WordRecognized.h>
#include <naoqi_bridge_msgs/SetSpeechVocabularyActionGoal.h>

using namespace std;

class SpeechRec{
	public:
		SpeechRec();
		~SpeechRec();
		void setVocab();
		void startRec();
		void wordRec();
		void stopRec();
		void wordCallback(const nao_msgs::WordRecognized);

	private:
		ros::NodeHandle n;
		ros::Publisher pub_vocab, pub_rec, pub_talk;
		ros::Subscriber sub_vocab, sub_rec;
		ros::ServiceClient start_rec, stop_rec;
		nao_msgs::WordRecognized received;
};

#endif
