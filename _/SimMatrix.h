#ifndef ALGORITHM_SIMMATRIX_H
#define ALGORITHM_SIMMATRIX_H

#include <iostream>
#include <iomanip>
using std::ostream;
using std::cout;
using std::endl;
using std::setw;

template <typename T>
class SimMatrix {
private:
    T** matrix_pt_ = nullptr;
    int rows_ = 0;
    int cols_ = 0;
    void destroy();
    void create(int r, int c);
public:
    SimMatrix() = default;
    SimMatrix(int rows, int columns, const T* m_pt = nullptr);
    explicit SimMatrix(int num);
    SimMatrix(const SimMatrix& sm);  //copy constructor
    SimMatrix(SimMatrix&& sm) noexcept;  //move constructor
    ~SimMatrix();
    int rows() {return rows_;}
    int columns() {return cols_;}
    T sum();
    SimMatrix& operator=(const SimMatrix& sm);  //copy assignment
    SimMatrix& operator=(SimMatrix&& sm);  //move assignment
    SimMatrix operator+(T num) const;
    SimMatrix operator+(const SimMatrix& sm) const;
    SimMatrix operator-(T num) const {return *this + -num;}
    SimMatrix operator-(const SimMatrix& sm) const;
    SimMatrix operator*(T num) const;
    SimMatrix operator*(const SimMatrix& sm) const;
    SimMatrix operator/(T num) const {return *this * (1 / num);}
    SimMatrix hadamard(const SimMatrix& sm) const;
    SimMatrix kronecker(const SimMatrix& sm) const;
    SimMatrix& transposition();
    SimMatrix convolution(const SimMatrix& filter, int stride = 1, int zero_padding = 0);
    void show(int width = 4) const;
    /*template <typename C> friend SimMatrix operator-(T num, const C& sm);
    template <typename C> friend SimMatrix operator/(T num, const C& sm);
    template <typename C> friend ostream& operator<<(ostream& os, SimMatrix<C>& sm);*/
};

template <typename T>
void SimMatrix<T>::create(int r, int c) {
    rows_ = r, cols_ = c;
    matrix_pt_ = new T*[r];
    for (int i = 0; i < r; ++i) matrix_pt_[i] = new T[c];
}

template <typename T>
void SimMatrix<T>::destroy() {
    for (int i = 0; i < rows_; ++i) delete [] matrix_pt_[i];
    delete [] matrix_pt_;
    matrix_pt_ = nullptr;
}

template <typename T>
SimMatrix<T>::SimMatrix(int rows, int columns, const T* m_pt) {
    create(rows, columns);
    if(m_pt)
        for (int j = 0; j < rows; ++j)
            for (int i = 0; i < columns; ++i) matrix_pt_[j][i] = m_pt[i + j * columns];
}

template <typename T>
SimMatrix<T>::SimMatrix(int num): rows_(num), cols_(num) {
    create(num, num);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j) matrix_pt_[i][j] = i == j ? 1 : 0;
}

template <typename T>
SimMatrix<T>::SimMatrix(const SimMatrix &sm) {
    create(sm.rows_, sm.cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j) matrix_pt_[i][j] = sm.matrix_pt_[i][j];
}

template <typename T>
SimMatrix<T>::SimMatrix(SimMatrix &&sm) noexcept {
    rows_ = sm.rows_, cols_ = sm.cols_, matrix_pt_ = sm.matrix_pt_;
    sm.rows_ = sm.cols_ = 0, sm.matrix_pt_ = nullptr;
}

template <typename T>
SimMatrix<T>::~SimMatrix() {
    destroy();
}

template <typename T>
T SimMatrix<T>::sum() {
    T sum = 0;
    for (int i = 0, j; i < rows_; ++i)
        for (j = 0; j < cols_; ++j) sum += matrix_pt_[i][j];
    return sum;
}

template <typename T>
SimMatrix<T>& SimMatrix<T>::operator=(const SimMatrix &sm) {
    if(this == &sm) return *this;
    destroy();
    create(sm.rows_, sm.cols_);
    for (int j = 0; j < sm.rows_; ++j)
        for (int i = 0; i < sm.cols_; ++i) matrix_pt_[j][i] = sm.matrix_pt_[j][i];
    return *this;
}

template <typename T>
SimMatrix<T>& SimMatrix<T>::operator=(SimMatrix &&sm) {
    if(this == &sm) return *this;
    destroy();
    rows_ = sm.rows_, cols_ = sm.cols_, matrix_pt_ = sm.matrix_pt_;
    sm.rows_ = sm.cols_ = 0, sm.matrix_pt_ = nullptr;
    return *this;
}

template <typename T>
SimMatrix<T> SimMatrix<T>::operator+(T num) const {
    SimMatrix tmp(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j) tmp.matrix_pt_[i][j] = matrix_pt_[i][j] + num;
    return tmp;
}

template <typename T>
SimMatrix<T> SimMatrix<T>::operator+(const SimMatrix &sm) const {
    if(rows_ != sm.rows_ || cols_ != sm.cols_) return SimMatrix();
    SimMatrix tmp(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j) tmp.matrix_pt_[i][j] = matrix_pt_[i][j] + sm.matrix_pt_[i][j];
    return tmp;
}

template <typename T>
SimMatrix<T> SimMatrix<T>::operator-(const SimMatrix &sm) const {
    if(rows_ != sm.rows_ || cols_ != sm.cols_) return SimMatrix();
    SimMatrix tmp(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j) tmp.matrix_pt_[i][j] = matrix_pt_[i][j] - sm.matrix_pt_[i][j];
    return tmp;
}

template <typename T>
SimMatrix<T> SimMatrix<T>::operator*(T num) const {
    SimMatrix tmp(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j) tmp.matrix_pt_[i][j] = matrix_pt_[i][j] * num;
    return tmp;
}

template <typename T>
SimMatrix<T> SimMatrix<T>::operator*(const SimMatrix &sm) const {
    if(cols_ != sm.rows_) return SimMatrix();
    SimMatrix tmp(rows_, sm.cols_);
    for (int i = 0, sum, j, k; i < rows_; ++i)
        for (j = 0; j < sm.cols_; ++j) {
            sum = 0;
            for (k = 0; k < cols_; ++k) sum += matrix_pt_[i][k] * sm.matrix_pt_[k][j];
            tmp.matrix_pt_[i][j] = sum;
        }
    return tmp;
}

template <typename T>
SimMatrix<T> SimMatrix<T>::hadamard(const SimMatrix &sm) const {
    if(rows_ != sm.rows_ || cols_ != sm.cols_) return SimMatrix();
    SimMatrix tmp(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j) tmp.matrix_pt_[i][j] = matrix_pt_[i][j] * sm.matrix_pt_[i][j];
    return tmp;
}

template <typename T>
SimMatrix<T> SimMatrix<T>::kronecker(const SimMatrix &sm) const {
    SimMatrix tmp(rows_ * sm.rows_, cols_ * sm.cols_);
    for (int i = 0, j, k, l, r, c, x, y; i < rows_; ++i) {
        for (j = 0; j < cols_; ++j) {
            r = i * rows_, c = j * cols_, x = 0, y = 0;  //锚点
            for (k = 0; k < sm.rows_; ++k)
                for (l = 0; l < sm.cols_; ++l) {
                    tmp.matrix_pt_[r + x][c + y++] = matrix_pt_[i][j] * sm.matrix_pt_[k][l];
                    if(y == sm.cols_) ++x, y = 0;
                }
        }
    }
    return tmp;
}

template <typename T>
SimMatrix<T>& SimMatrix<T>::transposition() {
    SimMatrix tmp(cols_, rows_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j) tmp.matrix_pt_[j][i] = matrix_pt_[i][j];
    rows_ = tmp.rows_, cols_ = tmp.cols_, matrix_pt_ = tmp.matrix_pt_;
    tmp.rows_ = tmp.cols_ = 0, tmp.matrix_pt_ = nullptr;
    return *this;
}

template <typename T>
SimMatrix<T> SimMatrix<T>::convolution(const SimMatrix &filter, int stride, int zero_padding) {
    double n_ = (cols_ + 2 * zero_padding - filter.cols_) / stride + 1;  //卷积核公式
    if(n_ != (int)n_) return SimMatrix();  //必须为整数
    int n = n_;
    //创建填充后的矩阵
    SimMatrix tmp(zero_padding ? rows_ + 2 * zero_padding : rows_,
            zero_padding ? cols_ + 2 * zero_padding : cols_);
    for (int i = 0, j; i < tmp.rows_; ++i){
        for (j = 0; j < tmp.cols_; ++j)
            if(zero_padding)
                if(i < zero_padding || j < zero_padding)
                    tmp.matrix_pt_[i][j] = 0;
                else if(tmp.rows_ - i <= zero_padding || tmp.cols_ - j <= zero_padding)
                    tmp.matrix_pt_[i][j] = 0;
                else
                    tmp.matrix_pt_[i][j] = matrix_pt_[i - zero_padding][j - zero_padding];
            else
                tmp.matrix_pt_[i][j] = matrix_pt_[i][j];
    }
    //创建卷积矩阵
    SimMatrix conv(n, n);
    int ni = 0, nj = 0;
    //卷积操作
    int i = 0, j, sum, i_ = tmp.rows_ - filter.rows_, j_ = tmp.cols_ - filter.cols_, k, l;
    for (; i <= i_; i += stride) {
        for (j = 0; j <= j_; j += stride) {
            sum = 0;
            for (k = 0; k < filter.rows_; ++k)
                for (l = 0; l < filter.cols_; ++l)
                    sum += filter.matrix_pt_[k][l] * tmp.matrix_pt_[i + k][j + l];
            conv.matrix_pt_[ni][nj++] = sum;
            if(nj == n) ++ni, nj = 0;
        }
    }
    return conv;
}

template <typename T>
void SimMatrix<T>::show(int width) const {
    cout << '[';
    for (int i = 0; i < rows_; ++i) {
        if(i) cout << setw(2);
        cout << '[';
        for (int j = 0; j < cols_; ++j) cout << setw(width) << matrix_pt_[i][j];
        cout << ']';
        if(i != rows_ - 1) cout << endl;
    }
    cout << "]\n";
}

/*template <typename T, typename C>
SimMatrix<T> operator-(T num, const C &sm) {
    SimMatrix<T> tmp(sm.rows_, sm.cols_);
    for (int i = 0; i < sm.rows_; ++i)
        for (int j = 0; j < sm.cols_; ++j) tmp.matrix_pt_[i][j] = num - sm.matrix_pt_[i][j];
    return tmp;
}

template <typename T, typename C>
SimMatrix<T> operator/(T num, const C &sm) {
    SimMatrix<T> tmp(sm.rows_, sm.cols_);
    for (int i = 0; i < sm.rows_; ++i)
        for (int j = 0; j < sm.cols_; ++j) tmp.matrix_pt_[i][j] = num / sm.matrix_pt_[i][j];
    return tmp;
}*/

template <typename T>
ostream& operator<<(ostream &os, SimMatrix<T> &sm) {
    sm.show();
    return os;
}

#endif //ALGORITHM_SIMMARTRIX_H
