#include<string>
#include<fstream>
#include<vector>
#include<cmath>
#include<opencv2/opencv.hpp>
#include<set>
#include<iomanip>


cv::Vec3f getImageCenter(const cv::Mat& img);

cv::Mat transporatedOnDioganal(cv::Mat& img);

cv::Mat getCooccurrenceMatrix(const cv::Mat& img);

cv::Vec3f getMaxEigenvector(const cv::Mat& cooccurrence);

float getAngleRotation(const cv::Vec3f a, const cv::Vec3f b);

cv::Vec3f cross_vec(const cv::Vec3f a, const cv::Vec3f b);

cv::Mat getRotationMatrix(const cv::Vec3f axis, const float theta);

cv::Vec3f matrix_multiply_vector(const cv::Mat& mat, const cv::Vec3f vec);

cv::Mat rotation(cv::Mat& img, const cv::Mat& rot);

cv::Mat transporated(cv::Mat img, cv::Vec3f delta);

void writeVectorsToFile(const std::string& filename, const cv::Mat& img);
