#include<iostream>
#include<tuple>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstddef>
#include <utility>
#define MATRIXS_MATRIXS_HPP_20230317
#define MATRIXS_H



class MatrixS {
private:
	int32_t* matrix_ = nullptr;
	std::ptrdiff_t rows_{0};
	std::ptrdiff_t cols_{0};
public:
	using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;
public:
	explicit MatrixS();
	explicit MatrixS(const SizeType& size = { 0, 0 });
	MatrixS(const std::ptrdiff_t row, const std::ptrdiff_t col);
	MatrixS(const MatrixS& rhs);
	MatrixS& operator=(const MatrixS& rhs);
	~MatrixS();

	[[nodiscard]] int32_t& at(const SizeType& elem);
	[[nodiscard]] const int32_t& at(const SizeType& elem) const;
	[[nodiscard]] int32_t& at(const std::ptrdiff_t i, const std::ptrdiff_t j);
	[[nodiscard]] const int32_t& at(const std::ptrdiff_t i, const std::ptrdiff_t j) const;

	void resize(const SizeType& new_size);
	void resize(const std::ptrdiff_t i, const std::ptrdiff_t j);


	[[nodiscard]] const SizeType& ssize() const noexcept;
	[[nodiscard]] std::ptrdiff_t nRows() const noexcept;
	[[nodiscard]] std::ptrdiff_t nCols() const noexcept;

};
