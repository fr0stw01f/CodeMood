/*************************************************************************
  >    File Name: OpenMP.cpp
  >       Author: tangzh
  >         Mail: tangzhnju@gmail.com 
  > Created Time: Wed 05 Jun 2013 10:22:27 PM CST
 ************************************************************************/

#include <iostream>
#include <ctime>

#include <omp.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>

using namespace std;

void add()
{
	int a = 0;
	for (int i=0;i<100000000;i++)
		a++;
}

void test_01()
{
	clock_t t1 = clock();
#pragma omp parallel for
	for (int i=0;i<8;i++)
		add();
	clock_t t2 = clock();
	std::cout<<"time: "<<t2-t1<<std::endl;
}

void test_02()
{
#pragma omp parallel for
	for (int i=0;i<10;i++)
		std::cout<<i<<std::endl;
}

void test_03()
{
	int sum = 0;
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
#pragma omp parallel for
	for (int i=0;i<10;i++)
		sum = sum + a[i];
	std::cout<<"sum: "<<sum<<std::endl;
}

void test_04()
{
	int sum = 0;
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int coreNum = omp_get_num_procs();//获得处理器个数
	int* sumArray = new int[coreNum];//对应处理器个数，先生成一个数组
	for (int i=0;i<coreNum;i++)//将数组各元素初始化为0
		sumArray[i] = 0;
#pragma omp parallel for
	for (int i=0;i<10;i++)
	{
		int k = omp_get_thread_num();//获得每个线程的ID
		sumArray[k] = sumArray[k]+a[i];
	}
	for (int i = 0;i<coreNum;i++)
		sum = sum + sumArray[i];
	std::cout<<"sum: "<<sum<<std::endl;
}

void test_05()
{
	int sum = 0;
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
#pragma omp parallel for reduction(+:sum)
	for (int i=0;i<10;i++)
		sum = sum + a[i];
	std::cout<<"sum: "<<sum<<std::endl;
}

void test_06()
{
	int max = 0;
	int a[10] = {11,2,33,49,113,20,321,250,689,16};
#pragma omp parallel for
	for (int i=0;i<10;i++)
	{
		int temp = a[i];
#pragma omp critical
		{
			if (temp > max)
				max = temp;
		}
	}
	std::cout<<"max: "<<max<<std::endl;
}

void test_07()
{
	cv::SurfFeatureDetector detector( 400 );    
	cv::SurfDescriptorExtractor extractor;
	cv::BruteForceMatcher<cv::L2<float> > matcher;
	std::vector< cv::DMatch > matches;
	cv::Mat im0,im1;
	std::vector<cv::KeyPoint> keypoints0,keypoints1;
	cv::Mat descriptors0, descriptors1;
	double t1 = omp_get_wtime( );
	//先处理第一幅图像
	im0 = cv::imread("rgb0.jpg", CV_LOAD_IMAGE_GRAYSCALE );
	detector.detect( im0, keypoints0);
	extractor.compute( im0,keypoints0,descriptors0);
	std::cout<<"find "<<keypoints0.size()<<"keypoints in im0"<<std::endl;
	//再处理第二幅图像
	im1 = cv::imread("rgb1.jpg", CV_LOAD_IMAGE_GRAYSCALE );
	detector.detect( im1, keypoints1);
	extractor.compute( im1,keypoints1,descriptors1);
	std::cout<<"find "<<keypoints1.size()<<"keypoints in im1"<<std::endl;
	double t2 = omp_get_wtime( );
	std::cout<<"time: "<<t2-t1<<std::endl;
	matcher.match( descriptors0, descriptors1, matches );
	cv::Mat img_matches;
	cv::drawMatches( im0, keypoints0, im1, keypoints1, matches, img_matches ); 
	cv::namedWindow("Matches",CV_WINDOW_AUTOSIZE);
	cv::imshow( "Matches", img_matches );
	cv::waitKey(0);
}
void test_08()
{
	int imNum = 2;
	std::vector<cv::Mat> imVec(imNum);
	std::vector<std::vector<cv::KeyPoint>>keypointVec(imNum);
	std::vector<cv::Mat> descriptorsVec(imNum);
	cv::SurfFeatureDetector detector( 400 );    cv::SurfDescriptorExtractor extractor;
	cv::BruteForceMatcher<cv::L2<float> > matcher;
	std::vector< cv::DMatch > matches;
	char filename[100];
	double t1 = omp_get_wtime( );
#pragma omp parallel for
	for (int i=0;i<imNum;i++){
		sprintf(filename,"rgb%d.jpg",i);
		imVec[i] = cv::imread( filename, CV_LOAD_IMAGE_GRAYSCALE );
		detector.detect( imVec[i], keypointVec[i] );
		extractor.compute( imVec[i],keypointVec[i],descriptorsVec[i]);
		std::cout<<"find "<<keypointVec[i].size()<<"keypoints in im"<<i<<std::endl;
	}
	double t2 = omp_get_wtime( );
	std::cout<<"time: "<<t2-t1<<std::endl;
	matcher.match( descriptorsVec[0], descriptorsVec[1], matches );
	cv::Mat img_matches;
	cv::drawMatches( imVec[0], keypointVec[0], imVec[1], keypointVec[1], matches, img_matches ); 
	cv::namedWindow("Matches",CV_WINDOW_AUTOSIZE);
	cv::imshow( "Matches", img_matches );
	cv::waitKey(0);
}


void test_09()
{
	cv::SurfFeatureDetector detector( 400 );    cv::SurfDescriptorExtractor extractor;
	cv::BruteForceMatcher<cv::L2<float> > matcher;
	std::vector< cv::DMatch > matches;
	cv::Mat im0,im1;
	std::vector<cv::KeyPoint> keypoints0,keypoints1;
	cv::Mat descriptors0, descriptors1;
	double t1 = omp_get_wtime( );
#pragma omp parallel sections
	{
#pragma omp section
		{
			std::cout<<"processing im0"<<std::endl;
			im0 = cv::imread("rgb0.jpg", CV_LOAD_IMAGE_GRAYSCALE );
			detector.detect( im0, keypoints0);
			extractor.compute( im0,keypoints0,descriptors0);
			std::cout<<"find "<<keypoints0.size()<<"keypoints in im0"<<std::endl;
		}
#pragma omp section
		{
			std::cout<<"processing im1"<<std::endl;
			im1 = cv::imread("rgb1.jpg", CV_LOAD_IMAGE_GRAYSCALE );
			detector.detect( im1, keypoints1);
			extractor.compute( im1,keypoints1,descriptors1);
			std::cout<<"find "<<keypoints1.size()<<"keypoints in im1"<<std::endl;
		}
	}
	double t2 = omp_get_wtime( );
	std::cout<<"time: "<<t2-t1<<std::endl;
	matcher.match( descriptors0, descriptors1, matches );
	cv::Mat img_matches;
	cv::drawMatches( im0, keypoints0, im1, keypoints1, matches, img_matches ); 
	cv::namedWindow("Matches",CV_WINDOW_AUTOSIZE);
	cv::imshow( "Matches", img_matches );
	cv::waitKey(0);
}

#define NUMBER 100  
#define DELAY 5  
char wndname[] = "Drawing Demo";  
  
CvScalar random_color(CvRNG* rng)  
{  
    int icolor = cvRandInt(rng);  
    return CV_RGB(icolor&255, (icolor>>8)&255, (icolor>>16)&255);  
}  

int test_10()
{
    int line_type = CV_AA; // change it to 8 to see non-antialiased graphics  
    int i;  
    CvPoint pt1,pt2;  
    double angle;  
    CvSize sz;  
    CvPoint  ptt[6];  
    CvPoint* pt[2];  
    int  arr[2];  
    CvFont font;  
    CvRNG rng;  
    int width = 1000, height = 700;  
    int width3 = width*3, height3 = height*3;  
    CvSize text_size;  
    int ymin = 0;  
    // Load the source image  
    IplImage* image = cvCreateImage( cvSize(width,height), 8, 3 );  
    IplImage* image2;  
  
    // Create a window  
    cvNamedWindow(wndname, 1 );  
    cvZero( image );  
    cvShowImage(wndname,image);  
    cvWaitKey(DELAY);  
  
    rng = cvRNG((unsigned)-1);  
    pt[0] = &(ptt[0]);  
    pt[1] = &(ptt[3]);  
  
    arr[0] = 3;  
    arr[1] = 3;  
  
    for (i = 0; i< NUMBER; i++)  
    {  
        pt1.x=cvRandInt(&rng) % width3 - width;  
        pt1.y=cvRandInt(&rng) % height3 - height;  
        pt2.x=cvRandInt(&rng) % width3 - width;  
        pt2.y=cvRandInt(&rng) % height3 - height;  
  
        cvLine( image, pt1, pt2, random_color(&rng), cvRandInt(&rng)%10, line_type, 0 );  
        cvShowImage(wndname,image);  
        if(cvWaitKey(DELAY) >= 0) return 0;  
    }  
  
    for (i = 0; i< NUMBER; i++)  
    {  
        pt1.x=cvRandInt(&rng) % width3 - width;  
        pt1.y=cvRandInt(&rng) % height3 - height;  
        pt2.x=cvRandInt(&rng) % width3 - width;  
        pt2.y=cvRandInt(&rng) % height3 - height;  
  
        cvRectangle( image,pt1, pt2, random_color(&rng), cvRandInt(&rng)%10-1, line_type, 0 );  
        cvShowImage(wndname,image);  
        if(cvWaitKey(DELAY) >= 0) return 0;  
    }  
  
    for (i = 0; i< NUMBER; i++)  
    {  
        pt1.x=cvRandInt(&rng) % width3 - width;  
        pt1.y=cvRandInt(&rng) % height3 - height;  
        sz.width =cvRandInt(&rng)%200;  
        sz.height=cvRandInt(&rng)%200;  
        angle = (cvRandInt(&rng)%1000)*0.180;  
  
        cvEllipse( image, pt1, sz, angle, angle - 100, angle + 200,  
                   random_color(&rng), cvRandInt(&rng)%10-1, line_type, 0 );  
        cvShowImage(wndname,image);  
        if(cvWaitKey(DELAY) >= 0) return 0;  
    }  
  
    for (i = 0; i< NUMBER; i++)  
    {  
        pt[0][0].x=cvRandInt(&rng) % width3 - width;  
        pt[0][0].y=cvRandInt(&rng) % height3 - height;  
        pt[0][1].x=cvRandInt(&rng) % width3 - width;  
        pt[0][1].y=cvRandInt(&rng) % height3 - height;  
        pt[0][2].x=cvRandInt(&rng) % width3 - width;  
        pt[0][2].y=cvRandInt(&rng) % height3 - height;  
        pt[1][0].x=cvRandInt(&rng) % width3 - width;  
        pt[1][0].y=cvRandInt(&rng) % height3 - height;  
        pt[1][1].x=cvRandInt(&rng) % width3 - width;  
        pt[1][1].y=cvRandInt(&rng) % height3 - height;  
        pt[1][2].x=cvRandInt(&rng) % width3 - width;  
        pt[1][2].y=cvRandInt(&rng) % height3 - height;  
  
        cvPolyLine( image, pt, arr, 2, 1, random_color(&rng), cvRandInt(&rng)%10, line_type, 0 );  
        cvShowImage(wndname,image);  
        if(cvWaitKey(DELAY) >= 0) return 0;  
    }  
  
    for (i = 0; i< NUMBER; i++)  
    {  
        pt[0][0].x=cvRandInt(&rng) % width3 - width;  
        pt[0][0].y=cvRandInt(&rng) % height3 - height;  
        pt[0][1].x=cvRandInt(&rng) % width3 - width;  
        pt[0][1].y=cvRandInt(&rng) % height3 - height;  
        pt[0][2].x=cvRandInt(&rng) % width3 - width;  
        pt[0][2].y=cvRandInt(&rng) % height3 - height;  
        pt[1][0].x=cvRandInt(&rng) % width3 - width;  
        pt[1][0].y=cvRandInt(&rng) % height3 - height;  
        pt[1][1].x=cvRandInt(&rng) % width3 - width;  
        pt[1][1].y=cvRandInt(&rng) % height3 - height;  
        pt[1][2].x=cvRandInt(&rng) % width3 - width;  
        pt[1][2].y=cvRandInt(&rng) % height3 - height;  
  
        cvFillPoly( image, pt, arr, 2, random_color(&rng), line_type, 0 );  
        cvShowImage(wndname,image);  
        if(cvWaitKey(DELAY) >= 0) return 0;  
    }  
  
    for (i = 0; i< NUMBER; i++)  
    {  
        pt1.x=cvRandInt(&rng) % width3 - width;  
        pt1.y=cvRandInt(&rng) % height3 - height;  
  
        cvCircle( image, pt1, cvRandInt(&rng)%300, random_color(&rng),  
                  cvRandInt(&rng)%10-1, line_type, 0 );  
        cvShowImage(wndname,image);  
        if(cvWaitKey(DELAY) >= 0) return 0;  
    }  
  
    for (i = 1; i< NUMBER; i++)  
    {  
        pt1.x=cvRandInt(&rng) % width3 - width;  
        pt1.y=cvRandInt(&rng) % height3 - height;  
  
        cvInitFont( &font, cvRandInt(&rng) % 8,  
                    (cvRandInt(&rng)%100)*0.05+0.1, (cvRandInt(&rng)%100)*0.05+0.1,  
                    (cvRandInt(&rng)%5)*0.1, cvRound(cvRandInt(&rng)%10), line_type );  
  
        cvPutText( image, "Testing text rendering!", pt1, &font, random_color(&rng));  
        cvShowImage(wndname,image);  
        if(cvWaitKey(DELAY) >= 0) return 0;  
    }  
  
    cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX, 3, 3, 0.0, 5, line_type );  
  
    cvGetTextSize( "OpenCV forever!", &font, &text_size, &ymin );  
  
    pt1.x = (width - text_size.width)/2;  
    pt1.y = (height + text_size.height)/2;  
    image2 = cvCloneImage(image);  
  
    for( i = 0; i < 255; i++ )  
    {  
        cvSubS( image2, cvScalarAll(i), image, 0 );  
        cvPutText( image, "OpenCV forever!", pt1, &font, CV_RGB(255,i,i));  
        cvShowImage(wndname,image);  
        if(cvWaitKey(DELAY) >= 0) return 0;  
    }  
  
    // Wait for a key stroke; the same function arranges events processing  
    cvWaitKey(0);  
    cvReleaseImage(&image);  
    cvReleaseImage(&image2);  
    cvDestroyWindow(wndname);   
	return 0;
}

int main(int argc, char* argv[])
{
//	test_01();
//	test_02();
//	test_03();
//	test_04();
//	test_05();
//	test_06();
//	test_07();
//	test_08();
//	test_09();
	test_10();

	return 0;
}


