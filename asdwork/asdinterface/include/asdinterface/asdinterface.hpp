#ifndef ASDINTERFACE_H
#define ASDINTERFACE_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPaintDevice>
#include <QtGui>
#include <QLCDNumber>
#include <ros/ros.h>
#include <ros/callback_queue.h>
//#include <nao_msgs/JointAnglesWithSpeed.h>
#include <std_msgs/String.h>
#include <naoqi_bridge_msgs/BodyPoseActionGoal.h>
#include <std_srvs/Empty.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <custom_msgs/control_states.h>

namespace Ui{
	class ASDInterface;
}

class ASDInterface : public QWidget{
	Q_OBJECT

	public:
		explicit ASDInterface(QWidget *parent = 0);
		~ASDInterface();
		void imageCallback(const sensor_msgs::ImageConstPtr& msg);
		void controlCallback(const custom_msgs::control_states States);
		void UpdateImage();
		void loopRate(int loop_rates);
		std::string getTimeStamp();
		void waveNao();
	
	private Q_SLOTS:
		void on_Start_clicked();
		void on_Command_clicked();
		void on_Prompt_clicked();
		void on_ShutDown_clicked();
		void on_Bye_clicked();
		void on_MyClock_overflow();

	protected:
		void paintEvent(QPaintEvent *event);
		void timerEvent(QTimerEvent *event);

	private:
		Ui::ASDInterface *ui;
		QBasicTimer Mytimer;
		QTimer *timer;
		QString MyClockTimetext;
		ros::NodeHandle n;
		ros::Publisher pub_speak, pub_pose, pub_move, pub_custom;
		ros::ServiceClient client_stiff, client_record_start, client_record_stop;
		ros::Subscriber sub_cam, sub_custom;
		QImage NaoImg;
		int count;
		std::ofstream fout;
		custom_msgs::control_states controlstate;
};

#endif
	
