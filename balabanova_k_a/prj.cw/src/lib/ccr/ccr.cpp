#include "include/ccr/ccr.hpp"

/**
 * @brief getImageCenter - получение центра масс облака точек 
 * @param img матрица изображения типа cv::Mat
 * @return вектор типа cv::Vec3f - цнтр масс облака точек
 */
cv::Vec3f getImageCenter(const cv::Mat& img){
	cv::Vec3f centre (0.0f, 0.0f, 0.0f);
    for (int row = 0; row < img.rows; row++) {
        for (int col = 0; col < img.cols; col++) {
            cv::Vec3f pixel = img.at<cv::Vec3f>(row, col);
            centre += pixel;
        }
    }
	centre /= (img.rows * img.cols);//??
	return centre;
}

/**
 * @brief transporatedOnDioganal - перемещение облака точек в начало координат RGB куба
 * @param img матрица обрабатываемого изображения типа cv::Mat
 * @return преобразованная матрица изображения типа cv::Mat
 */
cv::Mat transporatedOnDioganal(cv::Mat& img){
    cv::Vec3f centre = getImageCenter(img);
	for (int row = 0; row < img.rows; row++) {
        for (int col = 0; col < img.cols; col++) {
			img.at<cv::Vec3f>(row, col) -= centre;
        }
    }
	return img;
}

/**
 * @brief getCooccurrenceMatrix - получение матрицы ковариации для облака точек изображения
 * @param img матрица обрабатываемого изображения типа cv::Mat
 * @return матрица коварияции типа cv::Mat
 */
cv::Mat getCooccurrenceMatrix(const cv::Mat& img){
    cv::Vec3f centre = getImageCenter(img);
    cv::Mat cooccurrence(3, 3, CV_32FC1);
	cooccurrence.at<float>(0,0) = 0.0f;
	cooccurrence.at<float>(0,1) = 0.0f;
	cooccurrence.at<float>(0,2) = 0.0f;
	cooccurrence.at<float>(1,0) = 0.0f;
	cooccurrence.at<float>(1,1) = 0.0f;
	cooccurrence.at<float>(1,2) = 0.0f;
	cooccurrence.at<float>(2,0) = 0.0f;
	cooccurrence.at<float>(2,1) = 0.0f;
	cooccurrence.at<float>(2,2) = 0.0f;
	for (int row = 0; row < img.rows; ++row) {
        for (int col = 0; col < img.cols; ++col) {
            cv::Vec3f pixel = img.at<cv::Vec3f>(row, col);
            cv::Vec3f delta = pixel - centre;
			cooccurrence.at<float>(0,0) += (delta[0] * delta[0]);
			cooccurrence.at<float>(0,1) += (delta[0] * delta[1]);
			cooccurrence.at<float>(0,2) += (delta[0] * delta[2]);
			cooccurrence.at<float>(1,0) += (delta[1] * delta[0]);
			cooccurrence.at<float>(1,1) += (delta[1] * delta[1]);
			cooccurrence.at<float>(1,2) += (delta[1] * delta[2]);
			cooccurrence.at<float>(2,0) += (delta[2] * delta[0]);
			cooccurrence.at<float>(2,1) += (delta[2] * delta[1]);
			cooccurrence.at<float>(2,2) += (delta[2] * delta[2]);
        }
    }

	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			cooccurrence.at<float>(i,j) /= (img.rows * img.cols);
		}
	}
    return cooccurrence;
}

/**
 * @brief getMaxEigenvector нахождение обственного вектора матрицы коварации, соответствующего наибольшему собственному числу
 * @param cooccurrence матрица обрабатываемого изображения типа cv::Mat
 * @return нормализованный собственный вектор типа cv::Vec3f
 */
cv::Vec3f getMaxEigenvector(const cv::Mat& img){
    cv::Mat cooccurrence(img);
    cv::Mat eigenvalues, eigenvectors;
    cv::eigen(cooccurrence, eigenvalues, eigenvectors);
    
    int max_idx = 0;
    for (int i = 0; i < eigenvalues.rows; ++i) {
        if (eigenvalues.at<float>(i, 0) > eigenvalues.at<float>(max_idx, 0)) {
            max_idx = i;
        }
    }
    
    cv::Mat max_eigenvector = eigenvectors.row(max_idx);
    cv::normalize(max_eigenvector, max_eigenvector);
    return max_eigenvector;
}

/**
 * @brief getAngleRotation нахождение угла между векторами
 * @param a вектор типа cv::Vec3f
 * @param b вектор типа cv::Vec3f
 * @return угол между векторами типа float измеренный в радианах
 */
float getAngleRotation(const cv::Vec3f a, const cv::Vec3f b) {
    float dot_product = a.dot(b);
    float norm_a = cv::norm(a);
    float norm_b = cv::norm(b);
    float cos_theta = dot_product / (norm_a * norm_b);
    float theta = std::acos(cos_theta);
    return theta;
}

/**
 * @brief cross_vec - векторное произведение вектороа
 * @param a вектор типа cv::Vec3f
 * @param b вектор типа cv::Vec3f
 * @return нормализованный вектор типа cv::Vec3f
 */
cv::Vec3f cross_vec(const cv::Vec3f a, const cv::Vec3f b) {
    cv::Vec3f result = a.cross(b);
    cv::normalize(result, result);
    return result;
}

/**
 * @brief getRotationMatrix создание матрицы вращения отн-но некоторой оси на определенный угол
 * @param axis вектор типа cv::Vec3f, отн-но которого осуществляется вращение
 * @param theta угол типа float, измеренный в радианах, на которвй осуществляется 
 * @return матрица вращения типа cv::Mat 
 */
cv::Mat getRotationMatrix(const cv::Vec3f axis, const float theta){
	cv::Mat rot(3, 3, CV_32FC1);
	rot.at<float>(0,0) = axis[0] * axis[0] * (1.0f - std::cos(theta)) + std::cos(theta);;
	rot.at<float>(0,1) = axis[0] * axis[1] * (1.0f - std::cos(theta)) - axis[2] * std::sin(theta);;
	rot.at<float>(0,2) = axis[0] * axis[2] * (1.0f - std::cos(theta)) + axis[1] * std::sin(theta);
	rot.at<float>(1,0) = axis[1] * axis[0] * (1.0f - std::cos(theta)) + axis[2] * std::sin(theta);
	rot.at<float>(1,1) = axis[1] * axis[1] * (1.0f - std::cos(theta)) + std::cos(theta);
	rot.at<float>(1,2) = axis[1] * axis[2] * (1.0f - std::cos(theta)) - axis[0] * std::sin(theta);
	rot.at<float>(2,0) = axis[2] * axis[0] * (1.0f - std::cos(theta)) - axis[1] * std::sin(theta);
	rot.at<float>(2,1) = axis[2] * axis[1] * (1.0f - std::cos(theta)) + axis[0] * std::sin(theta);
	rot.at<float>(2,2) = axis[2] * axis[2] * (1.0f - std::cos(theta)) + std::cos(theta);
    return rot;
}

/**
 * @brief matrix_multiply_vector - умножение матрицы размером 3*3 на вектор размером 1*3
 * @param mat матрица типа cv::Mat 
 * @param vec вектор типа cv::Vec3f
 * @return вектор типа cv::Vec3f
 */
cv::Vec3f matrix_multiply_vector(const cv::Mat& mat, const cv::Vec3f vec) {
    cv::Mat result = mat * cv::Mat(vec);
    return cv::Vec3f(result.at<float>(0, 0), result.at<float>(1, 0), result.at<float>(2, 0));
}

/**
 * @brief rotation - вращение облака точек в RGB кубе
 * @param img матрица изображения типа cv::Mat
 * @param mat матрица вращения типа cv::Mat 
 * @return преобразованная матрица изображения типа cv::Mat
 */
cv::Mat rotation(cv::Mat& img, const cv::Mat& rot){
    for (int row = 0; row < img.rows; row++) {
        for (int col = 0; col < img.cols; col++) {
            cv::Vec3f pixel = img.at<cv::Vec3f>(row, col);
            img.at<cv::Vec3f>(row, col) = matrix_multiply_vector(rot, pixel);
        }
    }
	return img;
}

/**
 * @brief transporated - перемещение облака точек в RGB кубе
 * @param img матрица изображения типа cv::Mat
 * @param delta вектор типа cv::Vec3f, на который смещается облако
 * @return преобразованная матрица изображения типа cv::Mat
 */
cv::Mat transporated(cv::Mat img, cv::Vec3f delta){
    for (int row = 0; row < img.rows; row++) {
        for (int col = 0; col < img.cols; col++) {
            cv::Vec3f pixel = img.at<cv::Vec3f>(row, col);
            pixel += delta;
            if(pixel[0] < 0){
                pixel[0] = 0;
            }
            if(pixel[1] < 0){
                pixel[1] = 0;
            }
            if(pixel[2] < 0){
                pixel[2] = 0;
            }
            if(pixel[0] > 1){
                pixel[0] = 1;
            }
            if(pixel[1] > 1){
                pixel[1] = 1;
            }
            if(pixel[2] > 1){
                pixel[2] = 1;
            }
			img.at<cv::Vec3f>(row, col) = pixel;
        }
    }
	return img;
}



/**
 * @brief writeVectorsToFile - создание файла .tex для демонстрации алгоритма
 * @param filename название файла
 * @param image матрица изображения типа cv::Mat
 */
void writeVectorsToFile(const std::string& filename, const cv::Mat& img) {
    std::ofstream outputfile(filename);
    float eps = 0.02;
    //cv::Mat img = remove_duplicates(image);
    outputfile << '\\' << "documentclass{article}" << std::endl;
    outputfile << '\\' << "usepackage{amsmath}" << std::endl;
    outputfile << '\\' << "usepackage{tikz}" << std::endl;
    outputfile << '\\' << "usetikzlibrary{arrows}" << std::endl;
    outputfile << '\\' << "begin{document}" << std::endl;
    outputfile << '\\' << "begin{tikzpicture}[x=7cm,y=7cm,z=7cm,>=stealth]" << std::endl;
    outputfile << '\\' << "draw[->] (xyz cs:x=-0.5) -- (xyz cs:x=1) node[above] {$x$};" << std::endl;
    outputfile << '\\' << "draw[->] (xyz cs:y=-0.5) -- (xyz cs:y=1) node[right] {$z$};" << std::endl;
    outputfile << '\\' << "draw[->] (xyz cs:z=-0.5) -- (xyz cs:z=1) node[above] {$y$};" << std::endl;
    outputfile << '\\' << "foreach " << '\\' << "coo in {-0.5,-0.4,...,1}" << std::endl;
    outputfile << '{' << std::endl;
    outputfile << '\\' << "draw (" << '\\' << "coo,-0.5pt) -- (" << '\\' << "coo,0.5pt);" << std::endl;
    outputfile << '\\' << "draw (-0.5pt," << '\\' << "coo) -- (0.5pt," << '\\' << "coo);" << std::endl;
    outputfile << '\\' << "draw (xyz cs:y=-0.02pt,z=" << '\\' << "coo) -- (xyz cs:y=0.02pt,z=" << '\\' << "coo);" << std::endl;
    outputfile << '}' << std::endl;
    outputfile << '\\' << "foreach " << '\\' << "coo in {-0.5,0.5,1}" << std::endl;
    outputfile << '{' << std::endl;
    outputfile << '\\' << "draw[thick] (" << '\\' << "coo,-0.3pt) -- (" << '\\' << "coo,0.3pt) node[below=6pt] {" << '\\' << "coo};" << std::endl;
    outputfile << '\\' << "draw[thick] (-3pt," << '\\' << "coo) -- (3pt," << '\\' << "coo) node[left=6pt] {" << '\\' << "coo};" << std::endl;
    outputfile << '\\' << "draw[thick] (xyz cs:y=-0.03pt,z=" << '\\' << "coo) -- (xyz cs:y=0.03pt,z=" << '\\' << "coo) node[below=2pt] {" << '\\' << "coo};" << std::endl;
    outputfile << '}' << std::endl;
    outputfile << "$0$" << std::endl;
    cv::Vec3f black (0.0f, 0.0f, 0.0f);
	for (int row = 1; row < img.rows ; ++row) {
        for (int col = 1; col < img.cols; ++col) {
            cv::Vec3f pixel = img.at<cv::Vec3f>(row, col);
            cv::Vec3f pixel_up = img.at<cv::Vec3f>(row - 1, col);
            cv::Vec3f pixel_left = img.at<cv::Vec3f>(row, col - 1);
            if(((std::abs(pixel_up[0] - pixel[0]) > eps) && (std::abs(pixel_up[1] - pixel[1]) > eps) && (std::abs(pixel_up[2] - pixel[2]) > eps)) && ((std::abs(pixel_left[0] - pixel[0])> eps) && (std::abs(pixel_left[1] - pixel[1])> eps) && (std::abs(pixel_left[2] - pixel[2])> eps))){
            outputfile <<  '\\' << "draw[fill=black] (xyz cs:x=" << pixel[0] << ",y=" << pixel[1] << ",z=" << pixel[2] << ") circle (1pt);"<< std::endl;
            }
        }
    }
    outputfile << '\\' << "end{tikzpicture}" << std::endl;
    outputfile << '\\' << "end{document}" << std::endl;
    outputfile.close(); // закрытие файла
}
