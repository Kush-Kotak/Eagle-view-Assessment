#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;

#define MIN_INTENSITY 200

void create_mask_img(vector<cv::Mat>& src, vector<cv::Mat>& dst)
{
    for (int i = 0; i < src.size(); i++)
    {
        dst[i] = Mat::zeros(src[i].size(), CV_8UC1);
        for (int j = 0; j < src[i].rows; j++)
        {
            for (int k = 0; k < src[i].cols; k++)
            {
                Mat temp[3]; 
                split(src[i], temp);
                bool intensity = false;
                for (int c = 0; c < src[i].channels(); c++)
                {
                    if (temp[c].at<uchar>(j, k) > MIN_INTENSITY)
                    {
                        intensity = true;
                    }
                    else
                    {
                        intensity = false;
                        break;
                    }
                }
                if (intensity == true)
                {
                    dst[i].at<uchar>(j, k) = 255;
                }
                temp->release();
            }
        }
    }
}

int main()
{
    string path = "C:\\Users\\iGen Systems\\Desktop\\eagleview_assignment\\";
    std::vector<std::string> imageFilenames = 
    {    
        path + "faroe_island_1.png",
        path + "faroe_island_2.jpg",
        path + "faroe_island_3.jpg",
    };

    std::vector<cv::Mat> images(imageFilenames.size());
    std::vector<cv::Mat> mask_images(imageFilenames.size());

    for (size_t i = 0; i < imageFilenames.size(); ++i) 
    {
        images[i] = imread(imageFilenames[i], IMREAD_ANYCOLOR);
    }
 
    create_mask_img(images, mask_images);
    for (int i = 0; i < mask_images.size(); i++)
    {
        namedWindow("Mask Image", WINDOW_AUTOSIZE);
        cv::imshow("Mask Image", mask_images[i]);
        imwrite(path + "Mask_Image_" + to_string(i+1) + ".bmp", mask_images[i]);
        waitKey(0);
    }

    imageFilenames.clear();
    images.clear();
    mask_images.clear();

    return 0;
}

