
/*************************************************/

// Include Statements

#include "facedetect_class.h"

/*************************************************/

// Namespace Declarations

using namespace cv;
using namespace std;

/*************************************************/

// FaceDetect Member Function Definitions

        /*************************************************/

        // Constructor
        FaceDetect::FaceDetect() : transporter(node) {

                // Load the cascades
                if( !face_cascade.load( "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml" ) ) {
                    printf("--(!)Error loading face cascade\n");
                    return;
                };

                // Subscribe to input video feed 
                image_subscriber = transporter.subscribe("/nao_robot/camera/front/image_raw", 1, &FaceDetect::process_camera, this);
                //image_subscriber = transporter.subscribe("/usb_cam/image_raw", 1, &FaceDetect::process_camera, this);
    
        }
 
        /*************************************************/

        // Generate opencv image from ros image
        void FaceDetect::process_camera(const sensor_msgs::ImageConstPtr& msg) {
     
            /*************************************************/

            // Convert ros image to opencv image

            // Create the pointer
            cv_bridge::CvImagePtr cv_ptr;
    
            try {
                // Assigns pointer to output of fuction which converts an image to a mat
                cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
            }
    
            catch (cv_bridge::Exception& e) {
                // Report error if this fails
                ROS_ERROR("cv_bridge exception: %s", e.what());
                return;
            }
 
            /*************************************************/

            // Detect faces on the video stream       
            detectAndDisplay(cv_ptr->image);
     
            /*************************************************/
 
        }
 
        /*************************************************/

        // Detect and Display Function
        
        void FaceDetect::detectAndDisplay(Mat frame) {
 
            vector<Rect> faces;
            Mat frame_gray;

            cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
            equalizeHist( frame_gray, frame_gray );

            // Detect faces
            face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

            // Draw circle around detected faces
            for ( size_t i = 0; i < faces.size(); i++ ) {

                Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
                ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

                Mat faceROI = frame_gray( faces[i] );

            }
 
            // Make a window to put it in 
            namedWindow("Face Detector");
            imshow("Face Detector", frame);//cv_ptr->image);
            waitKey(3);
 
            /*************************************************/

        }

                

        /*************************************************/


