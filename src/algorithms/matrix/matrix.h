#pragma once

#include <algorithm>
#include <fstream>
#include <functional>
#include <vector>
#include <iostream>


namespace s21 {

template <class T>
class BLAS;

template <class T>
class Matrix {
 public:
  using i_type = unsigned int;
  using base = std::vector<T>;
  inline static double fp_compare_precision = 1e-6;

  Matrix() = default;
  Matrix(i_type rows, i_type cols, T value = T());
  Matrix(i_type rows);
  Matrix(i_type rows, i_type cols, const base &data);
  Matrix(i_type rows, i_type cols, base &&data);
  Matrix(i_type rows, i_type cols, std::ifstream &is);
  Matrix(std::ifstream &is);
  Matrix(const std::initializer_list<std::initializer_list<T>> &data);
  Matrix(i_type rows, i_type cols, const std::function<T(void)> &func);
  Matrix(i_type rows, i_type cols,
         const std::function<T(i_type, i_type)> &func);
  Matrix(i_type rows, i_type cols, const std::function<void(T &)> &func);
  Matrix(i_type rows, i_type cols,
         const std::function<void(i_type, i_type, T &)> &func);

  Matrix(const Matrix &other) = default;
  Matrix(Matrix &&other) = default;
  Matrix &operator=(const Matrix &other) = default;
  Matrix &operator=(Matrix &&other) = default;

  T &operator()(i_type row, i_type col);
  const T &operator()(i_type row, i_type col) const;
  i_type GetRows() const;
  i_type GetCols() const;
  i_type GetRows();
  i_type GetCols();

  void Fill(T value);
  void Fill(const base &data);
  void Fill(base &&data);
  void Fill(const std::initializer_list<std::initializer_list<T>> &data);
  void Fill(const std::function<T(void)> &func);
  void Fill(const std::function<T(i_type, i_type)> &func);
  void Fill(const std::function<void(T &)> &func);
  void Fill(const std::function<void(i_type, i_type, T &)> &func);

  void ForEach(const std::function<void(T &)> &f);
  void ForEach(const std::function<void(i_type, i_type, T &)> &f);
  void ForEach(const std::function<void(const T &)> &f) const;
  void ForEach(const std::function<void(i_type, i_type, const T &)> &f) const;

  struct Row;
  Row operator[](i_type row);
  const Row operator[](i_type row) const;

  static void Sum(const Matrix &a, const Matrix &b, Matrix &c);
  static void Sum(const Matrix &a, T value, Matrix &c);
  static void Sub(const Matrix &a, const Matrix &b, Matrix &c);
  static void Mul(const Matrix &a, const Matrix &b, Matrix &c);
  static void MulABT(const Matrix &a, const Matrix &b, Matrix &c);
  static void MulATB(const Matrix &a, const Matrix &b, Matrix &c);
  static void Inverse(const Matrix &a, Matrix &c);
  static void Mul(const Matrix &a, T value, Matrix &c);
  static T Determinant(const Matrix &a);
  static Matrix Minor(const Matrix &a, int row, int col);
  static Matrix Transpose(const Matrix &a);

  static void Divide(const Matrix &a, Matrix &b, T value);

  void SetRows(i_type rows);

  void Resize(i_type rows, i_type cols, T value = T());
  void Resize(i_type rows, i_type cols, const std::function<T(void)> &func);
  void Resize(i_type rows, i_type cols, const std::function<T(i_type, i_type)> &func);
  void Resize(i_type rows, i_type cols, const std::function<void(T &)> &func);
  void Resize(i_type rows, i_type cols, const std::function<void(i_type, i_type, T &)> &func);


  Matrix &operator+=(const Matrix &other);
  Matrix operator+(const Matrix &other) const;
  Matrix &operator+=(T value);
  Matrix operator+(T value) const;
  Matrix &operator-=(const Matrix &other);
  Matrix operator-(const Matrix &other) const;
  Matrix &operator*=(const Matrix &other);
  Matrix operator*(const Matrix &other) const;
  Matrix &operator*=(const T &value);
  Matrix operator*(const T &value) const;


  bool operator==(const Matrix &other) const;
  bool operator!=(const Matrix &other) const;

  T *Data();
  const T *Data() const;
  base &DataVector();
  const base &DataVector() const;

  void Print(std::ostream &os = std::cout) const;
  void PrintFull(std::ostream &os = std::cout) const;
  void Read(std::istream &is = std::cin);
  void ReadFull(std::istream &is = std::cin);

  friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    matrix.Print(os);
    return os;
  }
  friend std::istream &operator>>(std::istream &is, Matrix &matrix) {
    matrix.Read(is);
    return is;
  }

 private:
  friend class BLAS<T>;
  i_type rows_;
  i_type cols_;
  base data_;
};

template <class T>
Matrix<T>::Matrix(i_type rows, i_type cols, T value)
    : rows_(rows), cols_(cols), data_(rows * cols, value) {}

template <class T>
Matrix<T>::Matrix(i_type rows)
    : rows_(rows), cols_(rows), data_(rows * rows, T()) {}

template <class T>
Matrix<T>::Matrix(i_type rows, i_type cols, const base &data)
    : rows_(rows), cols_(cols), data_(data) {}

template <class T>
Matrix<T>::Matrix(i_type rows, i_type cols, base &&data)
    : rows_(rows), cols_(cols), data_(data) {}

template <class T>
Matrix<T>::Matrix(i_type rows, i_type cols, std::ifstream &is)
    : rows_(rows), cols_(cols), data_(rows * cols) {
  for (auto &value : data_) {
    is >> value;
  }
}

template <class T>
Matrix<T>::Matrix(std::ifstream &is) {
  is >> rows_ >> cols_;
  data_.resize(rows_ * cols_);
  for (auto &value : data_) {
    is >> value;
  }
}

template <class T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> &data)
    : rows_(data.size()), cols_(data.begin()->size()), data_(rows_ * cols_) {
  i_type i = 0;
  for (const auto &row : data) {
    for (const auto &value : row) {
      data_[i++] = value;
    }
  }
}

template <class T>
Matrix<T>::Matrix(i_type rows, i_type cols, const std::function<T(void)> &func)
    : rows_(rows), cols_(cols), data_(rows * cols) {
  std::generate(data_.begin(), data_.end(), func);
}

template <class T>
Matrix<T>::Matrix(i_type rows, i_type cols,
                  const std::function<T(i_type, i_type)> &func)
    : rows_(rows), cols_(cols), data_(rows * cols) {
  for (i_type i = 0; i < rows_; ++i) {
    for (i_type j = 0; j < cols_; ++j) {
      data_[i * cols_ + j] = func(i, j);
    }
  }
}

template <class T>
Matrix<T>::Matrix(i_type rows, i_type cols,
                  const std::function<void(T &)> &func)
    : rows_(rows), cols_(cols), data_(rows * cols) {
  for (auto &value : data_) {
    func(value);
  }
}

template <class T>
Matrix<T>::Matrix(i_type rows, i_type cols,
                  const std::function<void(i_type, i_type, T &)> &func)
    : rows_(rows), cols_(cols), data_(rows * cols) {
  for (i_type i = 0; i < rows_; ++i) {
    for (i_type j = 0; j < cols_; ++j) {
      func(i, j, data_[i * cols_ + j]);
    }
  }
}

template <class T>
T &Matrix<T>::operator()(i_type row, i_type col) {
  return data_[row * cols_ + col];
}

template <class T>
const T &Matrix<T>::operator()(i_type row, i_type col) const {
  return data_[row * cols_ + col];
}

template <class T>
typename Matrix<T>::i_type Matrix<T>::GetRows() const {
  return rows_;
}

template <class T>
typename Matrix<T>::i_type Matrix<T>::GetCols() const {
  return cols_;
}

template <class T>
typename Matrix<T>::i_type Matrix<T>::GetRows() {
  return rows_;
}

template <class T>
typename Matrix<T>::i_type Matrix<T>::GetCols() {
  return cols_;
}

template <class T>
void Matrix<T>::Fill(T value) {
  std::fill(data_.begin(), data_.end(), value);
}

template <class T>
void Matrix<T>::Fill(const base &data) {
  data_ = data;
}

template <class T>
void Matrix<T>::Fill(base &&data) {
  data_ = data;
}

template <class T>
void Matrix<T>::Fill(
    const std::initializer_list<std::initializer_list<T>> &data) {
  rows_ = data.size();
  cols_ = data.begin()->size();
  data_.resize(rows_ * cols_);
  i_type i = 0;
  for (const auto &row : data) {
    for (const auto &value : row) {
      data_[i++] = value;
    }
  }
}

template <class T>
void Matrix<T>::Fill(const std::function<T(void)> &func) {
  std::generate(data_.begin(), data_.end(), func);
}

template <class T>
void Matrix<T>::Fill(const std::function<T(i_type, i_type)> &func) {
  for (i_type i = 0; i < rows_; ++i) {
    for (i_type j = 0; j < cols_; ++j) {
      data_[i * cols_ + j] = func(i, j);
    }
  }
}

template <class T>
void Matrix<T>::Fill(const std::function<void(T &)> &func) {
  for (auto &value : data_) {
    func(value);
  }
}

template <class T>
void Matrix<T>::Fill(const std::function<void(i_type, i_type, T &)> &func) {
  for (i_type i = 0; i < rows_; ++i) {
    for (i_type j = 0; j < cols_; ++j) {
      func(i, j, data_[i * cols_ + j]);
    }
  }
}

template <class T>
void Matrix<T>::ForEach(const std::function<void(T &)> &f) {
  for (auto &value : data_) {
    f(value);
  }
}

template <class T>
void Matrix<T>::ForEach(const std::function<void(i_type, i_type, T &)> &f) {
  for (i_type i = 0; i < rows_; ++i) {
    for (i_type j = 0; j < cols_; ++j) {
      f(i, j, data_[i * cols_ + j]);
    }
  }
}

template <class T>
void Matrix<T>::ForEach(const std::function<void(const T &)> &f) const {
  for (const auto &value : data_) {
    f(value);
  }
}

template <class T>
void Matrix<T>::ForEach(
    const std::function<void(i_type, i_type, const T &)> &f) const {
  for (i_type i = 0; i < rows_; ++i) {
    for (i_type j = 0; j < cols_; ++j) {
      f(i, j, data_[i * cols_ + j]);
    }
  }
}

template <class T>
struct Matrix<T>::Row {
  Matrix &m;
  i_type row;
  Row(Matrix &matrix, i_type row) : m(matrix), row(row) {}
  T &operator[](i_type col) { return m(row, col); }
};

template <class T>
typename Matrix<T>::Row Matrix<T>::operator[](i_type row) {
  return Row(*this, row);
}

template <class T>
const typename Matrix<T>::Row Matrix<T>::operator[](i_type row) const {
  return Row(*this, row);
}

template <class T>
void Matrix<T>::Sum(const Matrix &a, const Matrix &b, Matrix &c) {
  if (a.rows_ != b.rows_ || a.cols_ != b.cols_ || a.rows_ != c.rows_ ||
      a.cols_ != c.cols_) {
    throw std::runtime_error("Matrix::Sum: different sizes");
  }
  const T *a_data = a.Data();
  const T *b_data = b.Data();
  T *c_data = c.Data();
  for (i_type i = 0; i < a.rows_; ++i) {
    for (i_type j = 0; j < a.cols_; ++j) {
      c_data[i * a.cols_ + j] =
          a_data[i * a.cols_ + j] + b_data[i * a.cols_ + j];
    }
  }
}

template <class T>
void Matrix<T>::Sum(const Matrix &a, T value, Matrix &c) {
  if (a.rows_ != c.rows_ || a.cols_ != c.cols_) {
    throw std::runtime_error("Matrix::Sum: different sizes");
  }
  const T *a_data = a.Data();
  T *c_data = c.Data();
  for (i_type i = 0; i < a.rows_; ++i) {
    for (i_type j = 0; j < a.cols_; ++j) {
      c_data[i * a.cols_ + j] = a_data[i * a.cols_ + j] + value;
    }
  }
}

template <class T>
void Matrix<T>::Sub(const Matrix &a, const Matrix &b, Matrix &c) {
  if (a.rows_ != b.rows_ || a.cols_ != b.cols_ || a.rows_ != c.rows_ ||
      a.cols_ != c.cols_) {
    throw std::runtime_error("Matrix::Sub: different sizes");
  }
  const T *a_data = a.Data();
  const T *b_data = b.Data();
  T *c_data = c.Data();
  for (i_type i = 0; i < a.rows_; ++i) {
    for (i_type j = 0; j < a.cols_; ++j) {
      c_data[i * a.cols_ + j] =
          a_data[i * a.cols_ + j] - b_data[i * a.cols_ + j];
    }
  }
}

template <class T>
void Matrix<T>::Mul(const Matrix &a, const Matrix &b, Matrix &c) {
  if (a.cols_ != b.rows_ || a.rows_ != c.rows_ || b.cols_ != c.cols_) {
    throw std::runtime_error("Matrix::Mul: different sizes");
  }
  const T *a_data = a.Data();
  const T *b_data = b.Data();
  T *c_data = c.Data();
  for (i_type i = 0; i < a.rows_; ++i) {
    for (i_type j = 0; j < b.cols_; ++j) {
      T sum = 0;
      for (i_type k = 0; k < a.cols_; ++k) {
        sum += a_data[i * a.cols_ + k] * b_data[k * b.cols_ + j];
      }
      c_data[i * b.cols_ + j] = sum;
    }
  }
}

template<class T>
void Matrix<T>::MulABT(const Matrix &a, const Matrix &b, Matrix &c) {
  if (a.cols_ != b.cols_ || a.rows_ != c.rows_ || b.rows_ != c.cols_) {
    throw std::runtime_error("Matrix::MulABT: different sizes");
  }
  const T *a_data = a.Data();
  const T *b_data = b.Data();
  T *c_data = c.Data();
  for (i_type i = 0; i < a.rows_; ++i) {
    for (i_type j = 0; j < b.rows_; ++j) {
      T sum = 0;
      for (i_type k = 0; k < a.cols_; ++k) {
        sum += a_data[i * a.cols_ + k] * b_data[j * b.cols_ + k];
      }
      c_data[i * b.rows_ + j] = sum;
    }
  }
}

template<class T>
void Matrix<T>::MulATB(const Matrix &a, const Matrix &b, Matrix &c) {
  if (a.rows_ != b.rows_ || a.cols_ != c.rows_ || b.cols_ != c.cols_) {
    throw std::runtime_error("Matrix::MulATB: different sizes");
  }
  const T *a_data = a.Data();
  const T *b_data = b.Data();
  T *c_data = c.Data();
  for (i_type i = 0; i < a.cols_; ++i) {
    for (i_type j = 0; j < b.cols_; ++j) {
      T sum = 0;
      for (i_type k = 0; k < a.rows_; ++k) {
        sum += a_data[k * a.cols_ + i] * b_data[k * b.cols_ + j];
      }
      c_data[i * b.cols_ + j] = sum;
    }
  }
}

template<class T>
void Matrix<T>::Divide(const Matrix &a, Matrix &b, T value) {
  if (a.rows_ != b.rows_ || a.cols_ != b.cols_) {
    throw std::runtime_error("Matrix::Divide: different sizes");
  }
  const T *a_data = a.Data();
  T *b_data = b.Data();
  for (i_type i = 0; i < a.rows_; ++i) {
    for (i_type j = 0; j < a.cols_; ++j) {
      b_data[i * a.cols_ + j] = a_data[i * a.cols_ + j] / value;
    }
  }
}

template<class T>
void Matrix<T>::Inverse(const Matrix &a, Matrix &c) {
  if (a.rows_ != a.cols_ || a.rows_ != c.rows_ || a.cols_ != c.cols_) {
    throw std::runtime_error("Matrix::Inverse: incorrect sizes");
  }

  T det = Determinant(a);
  if (det == 0) {
    throw std::runtime_error("Matrix::Inverse: matrix is singular (non-invertible)");
  }

  int n = a.rows_;

  Matrix<T> minors(n, n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      Matrix<T> minor = Minor(a, i, j);
      
      T minor_det = Determinant(minor);
      
      minors(i, j) = (i + j) % 2 == 0 ? minor_det : -minor_det;
    }
  }
  Matrix<T> adj = Transpose(minors);
  Divide(adj, c, det);
}

template<class T>
T Matrix<T>::Determinant(const Matrix &a) {
  if (a.rows_ != a.cols_) {
    throw std::runtime_error("Matrix::Determinant: matrix is not square");
  }
  int n = a.rows_;
  if (n == 1) {
    return a(0, 0);
  }
  if (n == 2) {
    return a(0, 0) * a(1, 1) - a(0, 1) * a(1, 0);
  }
  T det = 0;
  for (int j = 0; j < n; j++) {
    T cofactor = a(0, j) * Determinant(Minor(a, 0, j));
    if (j % 2 == 0) {
      det += cofactor;
    } else {
      det -= cofactor;
    }
  }
  
  return det;
}

template<class T>
Matrix<T> Matrix<T>::Minor(const Matrix &a, int row, int col) {
  Matrix minor(a.rows_ - 1, a.cols_ - 1);
  int minor_row = 0;
  for (int i = 0; i < a.rows_; i++) {
    if (i == row) {
      continue;
    }
    int minor_col = 0;
    for (int j = 0; j < a.cols_; j++) {
      if (j == col) {
        continue;
      }
      minor(minor_row, minor_col) = a(i, j);
      ++minor_col;
    }
    ++minor_row;
  }
  return minor;
}

template<class T>
Matrix<T> Matrix<T>::Transpose(const Matrix &a) {
  Matrix<T> transpose(a.cols_, a.rows_);
  for (int i = 0; i < a.rows_; i++) {
    for (int j = 0; j < a.cols_; j++) {
      transpose(j, i) = a(i, j);
    }
  }
  return transpose;
}


template <class T>
void Matrix<T>::Mul(const Matrix &a, T value, Matrix &c) {
  if (a.rows_ != c.rows_ || a.cols_ != c.cols_) {
    throw std::runtime_error("Matrix::Mul: different sizes");
  }
  T *a_data = a.Data();
  T *c_data = c.Data();
  for (i_type i = 0; i < a.rows_; ++i) {
    for (i_type j = 0; j < a.cols_; ++j) {
      c_data[i * a.cols_ + j] = a_data[i * a.cols_ + j] * value;
    }
  }
}

template <class T>
Matrix<T> &Matrix<T>::operator+=(const Matrix &other) {
  Sum(*this, other, *this);
  return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix &other) const {
  Matrix result(rows_, cols_);
  Sum(*this, other, result);
  return result;
}

template <class T>
Matrix<T> &Matrix<T>::operator+=(T value) {
  Sum(*this, value, *this);
  return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+(T value) const {
  Matrix result(rows_, cols_);
  Sum(*this, value, result);
  return result;
}

template <class T>
Matrix<T> &Matrix<T>::operator-=(const Matrix &other) {
  Sum(*this, other * -1, *this);
  return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix &other) const {
  Matrix result(rows_, cols_);
  Sum(*this, other * -1, result);
  return result;
}

template <class T>
Matrix<T> &Matrix<T>::operator*=(const Matrix &other) {
  Mul(*this, other, *this);
  return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix &other) const {
  Matrix result(rows_, other.cols_);
  Mul(*this, other, result);
  return result;
}

template <class T>
Matrix<T> &Matrix<T>::operator*=(const T &value) {
  Mul(*this, value, *this);
  return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const T &value) const {
  Matrix result(rows_, cols_);
  Mul(*this, value, result);
  return result;
}

template <class T>
bool Matrix<T>::operator==(const Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  if constexpr (std::is_floating_point_v<T>) {
    for (i_type i = 0; i < rows_; ++i) {
      for (i_type j = 0; j < cols_; ++j) {
        if (std::abs(data_[cols_ * i + j] - other.data_[cols_ * i + j]) >
            fp_compare_precision) {
          return false;
        }
      }
    }
  } else {
    for (i_type i = 0; i < rows_; ++i) {
      for (i_type j = 0; j < cols_; ++j) {
        if (data_[cols_ * i + j] != other.data_[cols_ * i + j]) {
          return false;
        }
      }
    }
  }
  return true;
}

template <class T>
bool Matrix<T>::operator!=(const Matrix &other) const {
  return !(*this == other);
}

template <class T>
void Matrix<T>::Print(std::ostream &os) const {
  for (i_type i = 0; i < rows_; ++i) {
    for (i_type j = 0; j < cols_; ++j) {
      os << data_[i * cols_ + j] << '\t';
    }
    os << '\n';
  }
}

template <class T>
void Matrix<T>::PrintFull(std::ostream &os) const {
  os << rows_ << '\t' << cols_ << '\n';
  Print(os);
}

template <class T>
void Matrix<T>::Read(std::istream &is) {
  for (auto &value : data_) {
    is >> value;
  }
}

template <class T>
void Matrix<T>::ReadFull(std::istream &is) {
  is >> rows_ >> cols_;
  data_.resize(rows_ * cols_);
  Read(is);
}

template <class T>
T *Matrix<T>::Data() {
  return data_.data();
}

template <class T>
const T *Matrix<T>::Data() const {
  return data_.data();
}

template <class T>
typename Matrix<T>::base &Matrix<T>::DataVector() {
  return data_;
}

template <class T>
const typename Matrix<T>::base &Matrix<T>::DataVector() const {
  return data_;
}

}  // namespace s21
