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

    msg.goal.words.push_back("hello");
    pub_vocab.publish(msg);
    msg.goal.words.push_back("blue");
    pub_vocab.publish(msg);
    msg.goal.words.push_back("goodbye");
    pub_vocab.publish(msg);
	
    for (int i = 0; i < msg.goal.words.size(); i++) {
        ROS_INFO_STREAM("MSG IS: " << msg.goal.words[i]);
    }


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
		
	naoqi_bridge_msgs::SetSpeechVocabularyActionGoal msg;
    std_msgs::String response;
    
    for (int i = 0; i < msg.goal.words.size(); i++) {

        if(received.words.back() == msg.goal.words[i]) {
			response.data = received.words.back() + " Recognized!";
	    	ROS_INFO_STREAM("RECOGNIZED " << received.words.back() << " With a confidence level of: " << received.confidence_values.back());
		    pub_talk.publish(response);
        }
        
        else{
		    ros::Duration(1).sleep();
	    }		

    }

		//stopRec();
		//ros::Duration(2).sleep();
		//ros::shutdown();
}

void SpeechRec::wordCallback(const nao_msgs::WordRecognized words){

    received = words;

    if(received.confidence_values.back() > 0.5) {
        wordRec();
    }

}
