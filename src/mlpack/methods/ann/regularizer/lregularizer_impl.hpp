/**
 * @file methods/ann/regularizer/lregularizer_impl.hpp
 * @author Saksham Bansal
 *
 * Implementation of template specializations of LRegularizer class.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_METHODS_ANN_LREGULARIZER_IMPL_HPP
#define MLPACK_METHODS_ANN_LREGULARIZER_IMPL_HPP

// In case it hasn't been included.
#include "lregularizer.hpp"

namespace mlpack {
namespace ann {

template<int Power>
LRegularizer<Power>::LRegularizer(double factor) :
    factor(factor)
{
  // Nothing to do here
}

// Unspecialized implementation. This should almost never be used...
template<int Power>
template<typename MatType>
void LRegularizer<Power>::Evaluate(const MatType& weight, MatType& gradient)
{
  gradient += arma::vectorise(arma::pow(weight, Power - 1) * Power * factor);
}

// L1-Regularizer specializations.
template<>
template<typename MatType>
void LRegularizer<1>::Evaluate(const MatType& weight, MatType& gradient)
{
  gradient += arma::vectorise(factor * weight / arma::abs(weight));
}

// L2-Regularizer specializations.
template<>
template<typename MatType>
void LRegularizer<2>::Evaluate(const MatType& weight, MatType& gradient)
{
  gradient += arma::vectorise(2 * factor * weight);
}

template<int Power>
template<typename Archive>
void LRegularizer<Power>::serialize(
    Archive& ar, const unsigned int /* version */)
{
  ar & BOOST_SERIALIZATION_NVP(factor);
}

} // namespace ann
} // namespace mlpack

#endif