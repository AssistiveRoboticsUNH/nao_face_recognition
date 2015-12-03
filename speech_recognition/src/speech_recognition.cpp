#include "../include/speech_recognition/speechrec.h"

SpeechRec::SpeechRec(){
	pub_vocab = n.advertise<naoqi_bridge_msgs::SetSpeechVocabularyActionGoal>("/speech_vocabulary_action/goal", 10);
	sub_rec = n.subscribe<nao_msgs::WordRecognized>("/word_recognized", 100, &SpeechRec::wordCallback, this);
	start_rec = n.serviceClient<std_srvs::Empty>("/start_recognition");
	stop_rec = n.serviceClient<std_srvs::Empty>("/stop_recognition");
	pub_talk = n.advertise<std_msgs::String>("/speech", 100);

}

SpeechRec::~SpeechRec(){
	stopRec();
}

void SpeechRec::setVocab(){
	naoqi_bridge_msgs::SetSpeechVocabularyActionGoal msg;
	msg.goal.words.push_back("hello"); //= "hello";
	ROS_INFO_STREAM("MSG IS: " << msg.goal.words[0]);
	pub_vocab.publish(msg);
}

void SpeechRec::startRec(){
	std_srvs::Empty start;
	start_rec.call(start);
	ros::spin();
}

void SpeechRec::stopRec(){
	std_srvs::Empty stop;
	stop_rec.call(stop);
}

void SpeechRec::wordRec(){
	if(received.words[0] == "hello" && received.confidence_values[0] > 0.5){
		std_msgs::String response;
		response.data = received.words[0] + " Recognized!";
		ROS_INFO_STREAM("RECOGNIZED " << received.words[0] << " With a confidence level of: " << received.confidence_values[0]);
		pub_talk.publish(response);
		//stopRec();
		//ros::Duration(2).sleep();
		//ros::shutdown();
	}
	else{
		ros::Duration(1).sleep();
	}		
}

void SpeechRec::wordCallback(const nao_msgs::WordRecognized words){
	received = words;
	if(received.words[0] == "hello" && received.confidence_values[0] > 0.5){
		wordRec();
	}
}
