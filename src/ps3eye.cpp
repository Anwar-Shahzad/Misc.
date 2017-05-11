#include "opencv2/opencv.hpp"
#include "context.h"
#include "frame_function.h"
#include <iostream>

//#include <opencv2/tracking/tracking.hpp>
#include  <opencv2/video/tracking.hpp>
using namespace cv;
using namespace std;

int run_camera(Context& context)
{
    VideoCapture cap(1); // open the default camera
    if(!cap.isOpened()){  // check if we succeeded
        std::cout << "No Camera detected." << std::endl;
        return -1;
    }
    // Mat edges;
    namedWindow("Input",1);
    namedWindow("Output",1);

    Mat frame(480, 640, CV_8UC3);
    //Ptr<Tracker> tracker = Tracker::create (" MIL ");
    //Rect2d bbox(287,23,86,320);
    //tracker->init(frame,bbox);
    
    for(;;)
      {
        cap >> frame; // get a new frame from camera

        imshow("Input", frame);
        
        int size = context.height*context.width*3;

        vector<uint8_t> destimg((uint8_t*) frame.data, (uint8_t*)frame.data+size);
        frame_function(context, destimg);

	        Mat m(480, 640, CV_8UC3, (uint8_t*) &destimg[0]);
	//tracker->update(frame,bbox);
	//rectangle(frame,bbox,Scalar(255,0,0),2,1);
	
        imshow("Output", frame);

        char instruction = waitKey(1);
	//a = 97, i = 105,
	if (instruction == 105){
	  context.use_invert = true;
	}
	 if (instruction == 102){
	  context.use_flip = true;
	}
	 if (instruction == 97){
	    context.use_average = true;
	}
	 if (instruction == 99){
	   context.use_average = false;
	   context.use_flip = false;
	   context.use_invert = false;
	 }

	 
	
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
