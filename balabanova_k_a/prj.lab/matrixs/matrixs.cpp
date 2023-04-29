#include <matrixs/matrixs.hpp>

MatrixS::MatrixS() {
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
}

MatrixS::MatrixS(const SizeType& size)
{
    if (std::get<1>(size) < 0 || std::get<0>(size) < 0) {
        throw std::invalid_argument("Invalid");
    }
    cols_ = std::get<1>(size);
    rows_ = std::get<0>(size);

    matrix_ = new int32_t[cols_ * rows_];
    for (std::ptrdiff_t i = 0; i < cols_ * rows_; ++i) {
        matrix_[i] = 0;
    }
}

MatrixS::MatrixS(const std::ptrdiff_t row, const std::ptrdiff_t col) {
    if (col < 0 || row < 0) {
        throw std::invalid_argument("Invalid");
    }
    rows_ = row;
    cols_ = col;
    matrix_ = new int32_t[cols_ * rows_];
    for (std::ptrdiff_t i = 0; i < cols_ * rows_; ++i) {
        matrix_[i] = 0;
    }
}


MatrixS::MatrixS(const MatrixS& rhs) {
    rows_ = rhs.rows_;
    cols_ = rhs.cols_;
    matrix_ = new int[cols_ * rows_];
    for (std::ptrdiff_t i = 0; i < cols_ * rows_; ++i){
        matrix_[i] = rhs.matrix_[i];
    }
}

MatrixS::~MatrixS() {
    if (matrix_ != nullptr) {
        delete[] matrix_;
    }
}

MatrixS& MatrixS::operator=(const MatrixS& rhs) {
    rows_ = rhs.rows_;
    cols_ = rhs.cols_;
    matrix_ = new int[rows_ * cols_];
    for (int i = 0; i < (rows_ * cols_); ++i) {
        matrix_[i] = rhs.matrix_[i];
    }
    return *this;
}

int32_t& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) {
    if (i < 0 || j < 0 || i >= rows_ || j >= cols_) {
        throw std::invalid_argument("Invalid");
    }
    if (i>= rows_ || j>= cols_) {
        throw std::invalid_argument("Invalid");
    }
    return matrix_[i * cols_ + j];
}

int32_t& MatrixS::at(const SizeType& elem) {
    if (std::get<0>(elem) < 0 || std::get<1>(elem) < 0) {
        throw std::invalid_argument("Invalid");
    }
    if (std::get<0>(elem) >= rows_ || std::get<1>(elem) >= cols_) {
        throw std::invalid_argument("Invalid");
    }
    return matrix_[std::get<0>(elem) * cols_ + std::get<1>(elem)];
};

const int32_t& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) const {
    if (i < 0 || j < 0) {
        throw std::invalid_argument("Invalid");
    }
    if (i >= rows_ || j >= cols_) {
        throw std::invalid_argument("Invalid");
    }
    return matrix_[i * cols_ + j];
}

const int32_t& MatrixS::at(const SizeType& elem) const {
    if (std::get<0>(elem) < 0 || std::get<1>(elem) < 0) {
        throw std::invalid_argument("Invalid");
    }
    if (std::get<0>(elem) >= rows_ || std::get<1>(elem) >= cols_) {
        throw std::invalid_argument("Invalid");
    }
    return matrix_[std::get<0>(elem) * cols_ + std::get<1>(elem)];
}

void MatrixS::resize(const std::ptrdiff_t i, const std::ptrdiff_t j) {
    if (i <= 0 || j <= 0) {
        throw std::invalid_argument("Invalid");
    }
    else {
        int32_t* matrix_new = new int32_t[i *j];
        for (std::ptrdiff_t i = 0; i < i * j; i++) {
            matrix_new[i] = 0;
        }
        for (std::ptrdiff_t i = 0; i < i && i < rows_; ++i) {
            for (std::ptrdiff_t j = 0; j < j && j < cols_; ++j) {
                matrix_new[i * j + j] = this->at(i, j);
            }
        }
        rows_ = i;
        cols_ = j;

        delete[] matrix_;
        matrix_ = matrix_new;
        matrix_new= nullptr;
    }
}

void MatrixS::resize(const SizeType& size) {
    this->resize(std::get<0>(size), std::get<1>(size));
}

const MatrixS::SizeType& MatrixS::ssize() const noexcept {
    return { rows_, cols_ };
}

std::ptrdiff_t MatrixS::nRows() const noexcept {
    return rows_;
}

std::ptrdiff_t MatrixS::nCols() const noexcept {
    return cols_;
}
