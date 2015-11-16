

/*************************************************/

// Include Statements

// For ros functionality
#include <ros/ros.h>

// For camera functionality
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

// For face tracking functionality
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
 
/*************************************************/

// Namespace declarations

using namespace std;

/*************************************************/

// Class declarations

class FaceDetect {

    private:

        /*************************************************/

        ros::NodeHandle node;
        image_transport::ImageTransport transporter;
    
        image_transport::Subscriber image_subscriber;
        image_transport::Publisher image_publisher;

        cv::CascadeClassifier face_cascade;
        string OPENCV_WINDOW;

        /*************************************************/


    public:

        /*************************************************/

        // Constructor
        FaceDetect();
   
        // Generate opencv image from ros image
        void process_camera(const sensor_msgs::ImageConstPtr& msg);

        // Detect and Display Function
        void detectAndDisplay(cv::Mat frame); 

        /*************************************************/

};

/*************************************************/


