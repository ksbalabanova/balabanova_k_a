#include <matrixs/matrixs.hpp>

explicit MatrixS::MatrixS() {
	cols_ = 0;
	rows_ = 0;
	matrix_ = nullptr;
}

explicit MatrixS::MatrixS(int rows, int cols) {
	rows_ = rows;
	cols_ = cols;
	matrix_ = (int**) new (int*) [rows_];
	for (int i = 0; i < rows_; ++i) {
		matrix_[i] = (int*) new int[cols_];
	}
	//мы заполняем массив нулями или он остается пустым?

	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			matrix_[i][j] = 0;
		}
	}
}

MatrixS::MatrixS(const MatrixS& matrix) {
	rows_ = matrix.rows_;
	cols_ = matrix.cols_;
	matrix_ = (int**) new (int*)[rows_];
	for (int i = 0; i < rows_; ++i) {
		matrix_[i] = (int*) new int[cols_];
	}
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			matrix_[i][j] = matrix[i][j];
		}
	}
}

MatrixS MatrixS::operator=(const MatrixS& matrix){
		if (cols_ > 0) {
			for (int i = 0; i < rows_; ++i) {
				delete[] matrix_[i];
			}
		}
		if (rows_ > 0) {
			delete[] matrix_;
		}
		rows_ = matrix.rows_;
		cols_ = matrix.cols_;
		matrix_ = (int**) new (int*)[rows_];
		for (int i = 0; i < rows_; ++i) {
			matrix_[i] = (int*) new int[cols_];
		}
		for (int i = 0; i < rows_; ++i) {
			for (int j = 0; j < cols_; ++j) {
				matrix_[i][j] = matrix[i][j];
			}
		}
		return *this;
}

MatrixS::~MatrixS() {
	if (cols_ > 0) {
		for (int i = 0; i < rows_; ++i) {
			delete[] matrix_[i];
		}
	}
	if (rows_ > 0) {
		delete[] matrix_;
	}
}

[[nodiscard]] std::ptrdiff_t MatrixS::nRows() const noexcept {
	return rows_;
}

[[nodiscard]] std::ptrdiff_t MatrixS::nCols() const noexcept {
	return cols_;
}
