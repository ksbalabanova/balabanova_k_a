#include<iostream>
#include<ccr/ccr.hpp>
#include<srgb/srgb.hpp>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Usage: <image_file> <function_name>" << std::endl;
        return -1;
    }
    // Считывание изображения из файла
    cv::Mat img = cv::imread(argv[1]);
    // Проверка, что изображение было успешно считано
    if (img.empty()) {
        std::cout << "Could not read image file: " << argv[1] << std::endl;
        return -1;
    }
    std::string function_name = argv[2];

    if (function_name == "image_processing") {
		std::string place_result;
		std::cout << "Enter the location of the processed image: " << std::endl;
		std::cin >> place_result;
		//cv::Mat img = cv::imread("/Users/balabashka/code/balabanova_k_a/photo_test/testbook2.jpeg");
		img = vision::srgb_to_linear(img);
		cv::Vec3f centre = getImageCenter(img);
		img = transporatedOnDioganal (img);
		cv::Mat E = getCooccurrenceMatrix(img);
		cv::Vec3f e1 = getMaxEigenvector(E);
		cv::Vec3f w(1.0f/std::pow(3.0f, 0.5), 1.0f/std::pow(3.0f, 0.5),1.0f/std::pow(3.0f, 0.5));
		float theta = getAngleRotation(e1, w);
		cv::Vec3f axis = cross_vec(e1, w);
		cv::Mat rot = getRotationMatrix(axis,theta);
		img = rotation(img, rot);
		float incr(centre[0] * w[0] + centre[1] * w[1] + centre[2] * w[2]);
		cv::Vec3f delta(incr * w[0], incr * w[1], incr * w[2]);
		img = transporated(img, delta);
		cv::Mat output = vision::linear_to_srgb(img);
		cv::imwrite(place_result, output);
        return 0;

	}
	else if (function_name == "visualisations"){
		std::string filename_1 = "output1.tex";
        std::string filename_2 = "output2.tex";
        std::string filename_3 = "output3.tex";
        std::string filename_4 = "output4.tex";

		img = vision::srgb_to_linear(img);
		writeVectorsToFile(filename_1, img);
		cv::Vec3f centre = getImageCenter(img);
		img = transporatedOnDioganal (img);
		writeVectorsToFile(filename_2, img);
		cv::Mat E = getCooccurrenceMatrix(img);
		cv::Vec3f e1 = getMaxEigenvector(E);
		cv::Vec3f w(1.0f/std::pow(3.0f, 0.5), 1.0f/std::pow(3.0f, 0.5),1.0f/std::pow(3.0f, 0.5));
		float theta = getAngleRotation(e1, w);
		cv::Vec3f axis = cross_vec(e1, w);
		cv::Mat rot = getRotationMatrix(axis,theta);
		img = rotation(img, rot);
		writeVectorsToFile(filename_3, img);
		float incr(centre[0] * w[0] + centre[1] * w[1] + centre[2] * w[2]);
		cv::Vec3f delta(incr * w[0], incr * w[1], incr * w[2]);
		img = transporated(img, delta);
		writeVectorsToFile(filename_4, img);

		return 0;
	}
	else {
        std::cout << "Unknown function: " << function_name << std::endl;
        return -1;
    }
}