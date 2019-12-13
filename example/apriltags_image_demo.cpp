#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Apriltag lib
#include "apriltags/TagDetector.h"
#include "apriltags/Tag16h5.h"
#include "apriltags/Tag25h7.h"
#include "apriltags/Tag25h9.h"
#include "apriltags/Tag36h11.h"
#include "apriltags/Tag36h9.h"

int main(int argc, char* argv[])
{
    // read image
    std::string image_path = "/home/tusimple/Pictures/apriltag.png";
    cv::Mat image = cv::imread(image_path);
    //transfrom to gray 
    cv::Mat img_gray;
    cv::cvtColor(image, img_gray, cv::COLOR_BGR2GRAY);
    //detect aruco
    // init tagcodes
    AprilTags::TagCodes tagCodes = AprilTags::tagCodes36h11;
    // init tag detector
    std::shared_ptr<AprilTags::TagDetector> tagDetector = std::make_shared<AprilTags::TagDetector>(tagCodes);
    // AprilTags::TagDetector* tagDetector =new AprilTags::TagDetector(tagCodes);
    std::vector<AprilTags::TagDetection> detection = tagDetector->extractTags(img_gray);
    //image show
    // for(int i=0;i<detection.size();i++)
    for(auto iter = detection.begin();iter != detection.end();iter++)
    {
        iter->draw(image);
    }
    cv::imshow("Detection",image);
    cv::waitKey(0);

    return 0;
}