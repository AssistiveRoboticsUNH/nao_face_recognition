#include "../include/asdinterface/asdinterface.hpp"
#include "../include/asdinterface/ui_asdinterface.hpp"
#include <string.h>


/* Class Constructor: Initializes all of the QT slots and widgets, and initializes all of the subscribers,
 * publishers, and services */
ASDInterface::ASDInterface(QWidget *parent) : QWidget(parent), ui(new Ui::ASDInterface){
	
	/* Sets up UI */
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(on_MyClock_overflow()));
	Mytimer.start(100, this);
	timer->start(100);
	ui->setupUi(this);

	/* Sets up ROS */
	ros::start();
	count = 0; //sets count to 0 so program can go through ros::spinOnce 10 times to solve issue with seg fault
	pub_speak = n.advertise<std_msgs::String>("/speech", 100); //publisher to make nao talk
	pub_pose = n.advertise<naoqi_bridge_msgs::BodyPoseActionGoal>("/body_pose/goal", 100); //publisher to make nao switch poses
	client_stiff = n.serviceClient<std_srvs::Empty>("/body_stiffness/enable", 100); //service client to unstiffen nao
	client_record_start = n.serviceClient<std_srvs::Empty>("/data_logger/start"); // service client to start rosbag
	client_record_stop = n.serviceClient<std_srvs::Empty>("/data_logger/stop"); //service client to stop rosbag
	sub_cam = n.subscribe("/face_recognition/image_raw", 100, &ASDInterface::imageCallback, this); //subcriber to get image
	sub_custom = n.subscribe("control_msgs", 100, &ASDInterface::controlCallback, this); // subscriber to get state status
	pub_custom = n.advertise<custom_msgs::control_states>("/control_msgs", 100); // advertises state status

	/* Creates file path to put timestamps in txt document */
	std::string file_path;
	//file_path = getenv("asdinterface");
	//file_path += "data/timestamps.txt";
	fout.open("~/asd_data/timestmaps/timestamps.txt", std::ofstream::out | std::ofstream::app);
	std::string timestamp;
	timestamp = getTimeStamp();
	fout << "UI LAUNCHED: " << timestamp << "\n\n";
}

/* Destructor: Frees space in memory where ui was allocated */
ASDInterface::~ASDInterface(){
	delete ui;
}

/* When clock is overflowed, update time */
void ASDInterface::on_MyClock_overflow(){
	QTime time = QTime::currentTime();
	QString text = time.toString("mm:ss");
	ui->MyClock->display(text);
}

/* Updates the displayed Image on UI */
void ASDInterface::UpdateImage(){
	ros::spinOnce(); //spins to call callback to update image information
}

/* Paints the camera image and clock to the UI */
void ASDInterface::paintEvent(QPaintEvent *event){
	QPainter myPainter(this);
	QPointF p(100, 80);
	QPointF p1(435, 170);
	myPainter.drawText(p1, MyClockTimetext); // Draws clock to ui
	if(count >= 10){ // first few frames are corrupted, so cannot draw image until it gets atleast 10 frames of the video stream
		myPainter.drawImage(p, NaoImg); //draws camera image on screen
	}
}

// When who am i  button clicked...
//      Retrain system
//      Run continuous face recognition
void ASDInterface::on_WhoAmI_clicked(){
	
	// Prints that button was clocked 
	ROS_INFO("Who Am I Button Clicked...\n");

}

// When learn name button clicked...
//      NAO asks for your name
//      Speech to text retrieves name
void ASDInterface::on_LearnName_clicked(){
	
	// Prints that button was clocked 
	ROS_INFO("Learn Name Button Clicked...\n");

}

// When learn face button clicked...
//      Fetches name
//      Takes training images of the person
void ASDInterface::on_LearnFace_clicked(){
	
	// Prints that button was clocked 
	ROS_INFO("Learn Face Button Clicked...\n");

}

// When start button clicked...
//      Launch face recognition server
//      Launch face recognition client
void ASDInterface::on_Start_clicked(){
	
	// Prints that button was clocked 
	ROS_INFO("Start Button Clicked...\n");

}

// When shutdown button clicked...
//      Shuts down ROS 
//      Quits the program 
void ASDInterface::on_ShutDown_clicked(){
		
	// Prints that button was clocked 
	ROS_INFO("Shutdown Button Clicked...\n");

	// publish shutdown to controlstate to get other nodes to terminate
	controlstate.shutdown = true;
	pub_custom.publish(controlstate);

	ros::shutdown();
	exit(0);

}

/* Updates image data and gui */
void ASDInterface::timerEvent(QTimerEvent*) {
	UpdateImage();
	update();
}

/* Call back to store image data from camera using ROS and converts it to QImage */
void ASDInterface::imageCallback(const sensor_msgs::ImageConstPtr& msg){
	QImage myImage(&(msg->data[0]), msg->width, msg->height, QImage::Format_RGB888);
	//NaoImg = myImage.rgbSwapped();
	NaoImg = myImage;
    count++;
}

/* Loop rate to make NAO wait for i amount of seconds */
void ASDInterface::loopRate(int loop_times){
	ros::Rate loop_rate(15);
	for(int i = 0; i < loop_times; i++){
		loop_rate.sleep();
	}
}

/* Gets the current timestamp whenever it is called */
std::string ASDInterface::getTimeStamp(){
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,80,"%Y-%m-%d-%H-%M-%S", timeinfo);
	std::string str(buffer);
	return str;
}

/* Custom Msg Callback */
void ASDInterface::controlCallback(const custom_msgs::control_states States){
	controlstate = States;
}
