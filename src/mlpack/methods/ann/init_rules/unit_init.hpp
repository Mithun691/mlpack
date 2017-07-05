/**
 * @file unit_init.hpp
 * @author Sumedh Ghaisas
 *
 * Intialization rule for the neural networks. This simple initialization is
 * performed by assigning a unit matrix (matrix of all ones) to the weight
 * matrix.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_METHODS_ANN_INIT_RULES_UNIT_INIT_HPP
#define MLPACK_METHODS_ANN_INIT_RULES_UNIT_INIT_HPP

#include <mlpack/prereqs.hpp>

namespace mlpack {
namespace ann /** Artificial Neural Network. */ {

/**
 * This class is used to initialize randomly the weight matrix.
 */
class UnitInitialization
{
 public:
  /**
   *  Create the UnitInitialization object.
   */
  UnitInitialization() { /* Nothing to do here */ }

  /**
   * Initialize the elements of the specified weight matrix.
   *
   * @param W Weight matrix to initialize.
   * @param rows Number of rows.
   * @param cols Number of columns.
   */
  template<typename eT>
  void Initialize(arma::Mat<eT>& W, const size_t rows, const size_t cols)
  {
    W = arma::ones<arma::Mat<eT> >(rows, cols);
  }

  /**
   * Initialize the elements of the specified weight (3rd order tensor).
   *
   * @param W Weight matrix to initialize.
   * @param rows Number of rows.
   * @param cols Number of columns.
   */
  template<typename eT>
  void Initialize(arma::Cube<eT>& W,
                  const size_t rows,
                  const size_t cols,
                  const size_t slices)
  {
    W = arma::ones<arma::Cube<eT> >(rows, cols, slices);
  }
}; // class UnitInitialization

} // namespace ann
} // namespace mlpack

#endif
