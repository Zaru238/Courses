#pragma once

#include <cstddef>

#include <array>
#include <iostream>
#include <tuple>

template <size_t N>
class Matrix {
 public:
  static constexpr size_t kDataSize = N * N;

  using DataType = std::array<ssize_t, kDataSize>;

  Matrix();
  Matrix(const Matrix&) = default;
  explicit Matrix(const DataType&);

  Matrix& operator=(const Matrix&) = default;

  void set_data(const DataType&);
  const DataType& get_data() const;

  Matrix operator+(const Matrix&) const;
  Matrix operator-(const Matrix&) const;

  Matrix standart_multiply(const Matrix&) const;
  Matrix strassen_multiply(const Matrix&) const;

  void print() const;

 private:
  template <size_t P>
  friend class Matrix;

  using Submatrice = Matrix<N/2>;
  using Submatrices =
      std::tuple<Submatrice, Submatrice, Submatrice, Submatrice>;

  Matrix strassen_multiply_impl(const Matrix&) const;

    // If N > M than cut off spare rows and columns
  // If N < M that fill in new rows and columns with zeros
  template <size_t M>
  Matrix<M> resize() const;

  Submatrices decompose() const;
  void compose(const Submatrices&);

  DataType data_;
};

template <size_t N>
Matrix<N>::Matrix() : data_({}) {
  static_assert(N != 0, "Matrix dimension cannot equal zero");
}

template <size_t N>
Matrix<N>::Matrix(const DataType& data) : data_(data) {
  static_assert(N != 0, "Matrix dimension cannot equal zero");
}

template <size_t N>
void Matrix<N>::set_data(const DataType& data) {
  data_ = data;
}

template <size_t N>
const typename Matrix<N>::DataType& Matrix<N>::get_data() const {
  return data_;
}

template <size_t N>
Matrix<N> Matrix<N>::operator+(const Matrix& other) const {
  Matrix answer;

  for (size_t i = 0; i < kDataSize; ++i) {
    answer.data_[i] = this->data_[i] + other.data_[i];
  }

  return answer;
}

template <size_t N>
Matrix<N> Matrix<N>::operator-(const Matrix& other) const {
  Matrix answer;

  for (size_t i = 0; i < kDataSize; ++i) {
    answer.data_[i] = this->data_[i] - other.data_[i];
  }

  return answer;
}

template <size_t N>
Matrix<N> Matrix<N>::standart_multiply(const Matrix& other) const {
  Matrix answer;

  if constexpr (1 == N) {
    answer.data_ = {this->data_[0] * other.data_[1]};
    return answer;
  }

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      size_t sum {};

      for (size_t k = 0; k < N; ++k) {
        sum += this->data_[i*N + k] * other.data_[N*k + j];
      }

      answer.data_[i*N + j] = sum;
    }
  }

  return answer;
}

#include <cassert>

constexpr size_t pow_of_2_contains(size_t dimension) {
  // Number size is too big for Strassen multiplication usage
  assert((dimension != size_t(-1)) || (dimension < ((size_t(-1)) >> 1)));
  // Dimension cannot equal zero
  assert(dimension != 0);

  --dimension;
  dimension |= (dimension >> 1);
  dimension |= (dimension >> 2);
  dimension |= (dimension >> 4);
  dimension |= (dimension >> 8);
  dimension |= (dimension >> 16);
  dimension |= (dimension >> 32);

  dimension = dimension + 1;

  return dimension;
}

template <size_t N>
Matrix<N> Matrix<N>::strassen_multiply(const Matrix& other) const {
  // Supplement matix dimension to power of two
  constexpr size_t kPreferredSize = pow_of_2_contains(N);

  if constexpr (kPreferredSize == N) {
    return strassen_multiply_impl(other);
  } else {
    auto temp = this->resize<kPreferredSize>();
    auto other_temp = other.resize<kPreferredSize>();
    temp = temp.strassen_multiply(other_temp);
    return temp.template resize<N>();
  }
}

template <size_t N>
Matrix<N> Matrix<N>::strassen_multiply_impl(const Matrix& other) const {
  static_assert(!(N & (N - 1)), "Dimension should be a power of two");

  if constexpr (N < 3) {
    return standart_multiply(other);
  } else {
    // Algorithm description https://en.wikipedia.org/wiki/Strassen_algorithm
    const auto [a11, a12, a21, a22] = this->decompose();
    const auto [b11, b12, b21, b22] = other.decompose();

    const auto m1 = (a11 + a22).strassen_multiply_impl(b11 + b22);
    const auto m2 = (a21 + a22).strassen_multiply_impl(b11);
    const auto m3 = a11.strassen_multiply_impl(b12 - b22);
    const auto m4 = a22.strassen_multiply_impl(b21 - b11);
    const auto m5 = (a11 + a12).strassen_multiply_impl(b22);
    const auto m6 = (a21 - a11).strassen_multiply_impl(b11 + b12);
    const auto m7 = (a12 - a22).strassen_multiply_impl(b21 + b22);

    const auto c11 = m1 + m4 - m5 + m7;
    const auto c12 = m3 + m5;
    const auto c21 = m2 + m4;
    const auto c22 = m1 - m2 + m3 + m6;

    Matrix answer;
    answer.compose(std::tie(c11, c12, c21, c22));

    return answer;
  }
}

template <size_t N>
template <size_t M>
Matrix<M> Matrix<N>::resize() const {
  if constexpr (N == M) {
    return *this;
  }

  typename Matrix<M>::DataType answer_data{};

  if constexpr (M > N) {
    // Fill initial elements with values from original matrix
    // All remaining elements filled with zeros
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        answer_data[i * M + j] = this->data_[i * N + j];
      }
    }
  } else {
    // Fill all elements with initial elements of original matrix
    for (size_t i = 0; i < M; ++i) {
      for (size_t j = 0; j < M; ++j) {
        answer_data[i * M + j] = this->data_[i * N + j];
      }
    }
  }

  return Matrix<M>(answer_data);
}

template <size_t N>
typename Matrix<N>::Submatrices Matrix<N>::decompose() const {
  static_assert((!(N % 2)) && (N > 1), "Matrix dimension should be even");
  Matrix<N/2> top_left;
  for (size_t i = 0; i < N/2; ++i) {
    for (size_t j = 0; j < N/2; ++j) {
      top_left.data_[i*N/2 + j] = this->data_[i*N + j];
    }
  }
  Matrix<N/2> top_right;
  for (size_t i = 0; i < N/2; ++i) {
    for (size_t j = 0; j < N/2; ++j) {
      top_right.data_[i*N/2 + j] = this->data_[i*N + N/2 + j];
    }
  }
  Matrix<N/2> bottom_left;
  for (size_t i = 0; i < N/2; ++i) {
    for (size_t j = 0; j < N/2; ++j) {
      bottom_left.data_[i*N/2 + j] = this->data_[(N/2 + i)*N + j];
    }
  }
  Matrix<N/2> bottom_right;
  for (size_t i = 0; i < N/2; ++i) {
    for (size_t j = 0; j < N/2; ++j) {
      bottom_right.data_[i*N/2 + j] = this->data_[(N/2 + i)*N + N/2 + j];
    }
  }

  return std::tie(top_left, top_right, bottom_left, bottom_right);
}

template <size_t N>
void Matrix<N>::compose(const Submatrices& submatr) {
  const auto& top_left = std::get<0>(submatr);
  for (size_t i = 0; i < N/2; ++i) {
    for (size_t j = 0; j < N/2; ++j) {
      this->data_[i*N + j] = top_left.data_[i*N/2 + j];
    }
  }
  const auto& top_right = std::get<1>(submatr);
  for (size_t i = 0; i < N/2; ++i) {
    for (size_t j = 0; j < N/2; ++j) {
      this->data_[i*N + N/2 + j] = top_right.data_[i*N/2 + j];
    }
  }
  const auto& bottom_left = std::get<2>(submatr);
  for (size_t i = 0; i < N/2; ++i) {
    for (size_t j = 0; j < N/2; ++j) {
      this->data_[(N/2 + i)*N + j] = bottom_left.data_[i*N/2 + j];
    }
  }
  const auto& bottom_right = std::get<3>(submatr);
  for (size_t i = 0; i < N/2; ++i) {
    for (size_t j = 0; j < N/2; ++j) {
      this->data_[(N/2 + i)*N + N/2 + j] = bottom_right.data_[i*N/2 + j];
    }
  }
}

template <size_t N>
void Matrix<N>::print() const {
  std::cout << "Matrix dump" << std::endl;
  for (size_t i = 0; i < N; ++i){
    for (size_t j = 0; j < N; ++j) {
      std::cout << this->data_[i*N + j] << " ";
    }
    std::cout<<std::endl;
  }
  std::cout<<std::endl;
}
