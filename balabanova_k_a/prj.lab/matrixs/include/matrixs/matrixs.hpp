#include<ostream>
#include<cstdeff>

class MatrixS {
private:
	int** matrix_ = 0;
	int cols_ = 0;
	int rows_ = 0;

public:
	explicit MatrixS();
	explicit MatrixS(int rows, int cols);
	MatrixS(const MatrixS& matrix);
	MatrixS operetor=(const MatrixS& matrix);
	~MatrixS();
	
	[[nodiscard]] std::ptrdiff_t MatrixS::nRows() const noexcept;
	[[nodiscard]] std::ptrdiff_t MatrixS::nCols() const noexcept;
};
