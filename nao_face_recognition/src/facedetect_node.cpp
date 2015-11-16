
#include "facedetect_class.cpp"

int main(int argc, char* argv[]) {

    ros::init(argc, argv, "image_converter");
    FaceDetect face;
    
    ros::spin();

    return 0;

}






