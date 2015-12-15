#include "../include/asdinterface/asdinterface.hpp"
#include "../include/asdinterface/ui_asdinterface.hpp"
#include <string.h>

// Class Constructor
//  Initializes QT slots and widgets, subscribers, 
//  publishers, services and other various variables
ASDInterface::ASDInterface(QWidget *parent) : QWidget(parent), ui(new Ui::ASDInterface){
	
    /************************************************/    

	// Sets up qt slots and widgets

    timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(on_MyClock_overflow()));
	Mytimer.start(100, this);
	timer->start(100);
	ui->setupUi(this);

    /************************************************/    

	// Initializes ROS and other variables

    ros::start();       // initializes ros
    name = "nobody";    // initializes name field to nobody
	count = 0;          // initializes count to 0 
                        // so program can go through ros::spinOnce 
                        // 10 times to solve issue with seg fault

    /************************************************/    

    // Initializes publishers

    pub_custom = n.advertise<custom_msgs::control_states>("/control_msgs", 100);                // for state change functionality
    pub_facerec = n.advertise<face_recognition::FRClientGoal>("/fr_order", 100);                // for face recognition functionality
	pub_speak = n.advertise<std_msgs::String>("/speech", 100);                                  // for nao speech functionality
	//pub_pose = n.advertise<naoqi_bridge_msgs::BodyPoseActionGoal>("/body_pose/goal", 100);    // for nao pose functionality
 
    /************************************************/    
  
    // Initializes subscribers

	sub_cam = n.subscribe("/nao_robot/camera/top/camera/image_raw", 100, &ASDInterface::imageCallback1, this);  // gets raw image from camera
	sub_custom = n.subscribe("/control_msgs", 100, &ASDInterface::controlCallback, this);                       // gets state status
    //sub_frstatus = n.subscribe("/face_recognition/status", 100, &ASDInterface::frStatusCallback, this);       // gets face recognition status  

    /************************************************/    

    // Initializes service clients

	//client_stiff = n.serviceClient<std_srvs::Empty>("/body_stiffness/enable", 100);   // service client to unstiffen nao
	//client_record_start = n.serviceClient<std_srvs::Empty>("/data_logger/start");     // service client to start rosbag
	//client_record_stop = n.serviceClient<std_srvs::Empty>("/data_logger/stop");       // service client to stop rosbag

    /************************************************/    

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
//      Retrain database on possible new images (order_id = 3)
//      Run continuous face recognition (order_id = 1)
void ASDInterface::on_WhoAmI_clicked(){

    /************************************************/    
	
    // Retrain database...
    
    face_recognition::FRClientGoal command;

    command.order_id = 3;
    command.order_argument = "none";
    pub_facerec.publish(command);

    ros::Duration(2).sleep();
    
    /************************************************/    
    
    // Run continuous face recognition...

    command.order_id = 1;
    command.order_argument = "none";
    pub_facerec.publish(command);
 
    sub_cam = n.subscribe("/face_recognition/image_raw", 100, &ASDInterface::imageCallback2, this); //subcriber to get image
 
    /************************************************/    

}

// When learn name button clicked...
//      NAO asks for your name
//      Speech to text retrieves name
void ASDInterface::on_LearnName_clicked(){
			
    /************************************************/    

    // NAO asks for your name

    std::cout << "What is your name?: " << std::endl;

    /************************************************/    

    // Learn name from std input

    std::cin >> name;
    std::cout << "Hello " << name << std::endl;
    std::cout << "I never forget a face. Click the 'Learn Face' button" << std::endl;
    std::cout << "so that I can learn what your face looks like!" << std::endl;
	
    /************************************************/    

}

// When learn face button clicked...
//      Fetches name
//      Takes training images of person
void ASDInterface::on_LearnFace_clicked(){
		
    /************************************************/    

    // Fetch name... 
    
    face_recognition::FRClientGoal command;
    command.order_argument = name;
    
    /************************************************/    
    
    // Take training images of person...

    command.order_id = 2;
    pub_facerec.publish(command);
	 
    sub_cam = n.subscribe("/face_recognition/image_raw", 100, &ASDInterface::imageCallback2, this); //subcriber to get image

    /************************************************/    

}

// When reset button clicked...
//      Return to normal camera view
void ASDInterface::on_Reset_clicked(){
	
    /************************************************/    

    // Return to normal camera view...
    
    face_recognition::FRClientGoal command;

    sub_cam = n.subscribe("/nao_robot/camera/top/camera/image_raw", 100, &ASDInterface::imageCallback1, this); //subcriber to get image
    
    /************************************************/    

}

// When shutdown button clicked...
//      Nao says goodbye
//      Nao returns to crouching position
//      Shuts down nodes
//      Shuts down ROS 
//      Quits the program 
void ASDInterface::on_ShutDown_clicked(){
			
    /************************************************/    

    // Nao says goodbye...    

    std_msgs::String words;
    words.data = "Goodbye";
    pub_speak.publish(words);
	
    /************************************************/    

    // Nao returns to crouching position

    //naoqi_bridge_msgs::BodyPoseActionGoal pose;
    //pose.goal_pose_name = "Crouch";
    //pub_pose.publish(pose);

    /************************************************/    
	
    // Exit Fserver...
    
    face_recognition::FRClientGoal command;

    command.order_id = 4;
    command.order_argument = "none";
    pub_facerec.publish(command);
 
    /************************************************/    

	// Exit asdinterface...

	controlstate.shutdown = true;
	pub_custom.publish(controlstate);
 
    /************************************************/    

    // Shuts down ROS
	ros::shutdown();

    /************************************************/    
   
    // Quits the program 
	exit(0);
 
    /************************************************/    

}

/* Updates image data and gui */
void ASDInterface::timerEvent(QTimerEvent*) {
	UpdateImage();
	update();
}

/* Call back to store image data from camera using ROS and converts it to QImage */
void ASDInterface::imageCallback1(const sensor_msgs::ImageConstPtr& msg){
	QImage myImage(&(msg->data[0]), msg->width, msg->height, QImage::Format_RGB888);
	NaoImg = myImage.rgbSwapped();
	//NaoImg = myImage;
    count++;
}

/* Call back to store image data from camera using ROS and converts it to QImage */
void ASDInterface::imageCallback2(const sensor_msgs::ImageConstPtr& msg){
	QImage myImage(&(msg->data[0]), msg->width, msg->height, QImage::Format_RGB888);
	NaoImg = myImage.rgbSwapped();
	//NaoImg = myImage;
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


/* Face Recognition Status Callback */
void ASDInterface::frStatusCallback(const actionlib_msgs::GoalStatusArray& Status){
    current_status = Status;
}


