
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include <ros/package.h>

using namespace cv;
using namespace std;

int main( int argc, char** argv ) {
 
    /***********************************************/
    
    // Get path of image

    string file_path;
    file_path = ros::package::getPath("face_recognition");
    file_path+= "/sample_faces/matt_smith/matt_smith_4.jpg";

    /***********************************************/
    
    // Open image in window
    
    Mat image;
    image = imread(file_path, CV_LOAD_IMAGE_COLOR);   
  
    cout << "Image is at location " << file_path << endl;

    if( image.empty() ) {                              
        cout <<  "Could not open or find the image at location " << file_path << endl ;
        return -1;
    }
 
    namedWindow( "Display Window", WINDOW_AUTOSIZE );
    
 //  getchar();
    
    imshow("Display Window", image);                   

 //   getchar();

    waitKey(0);                                          
    destroyWindow("Display Window");
   
    /***********************************************/

    return 0;

}



