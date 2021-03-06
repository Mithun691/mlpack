/**
 * @file core/cereal/pointer_vector_variant_wrapper.hpp
 * @author Omar Shrit
 *
 * Implementation of a boost::variant wrapper to enable the serialization of
 * the pointers inside boost variant in cereal
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_CORE_CEREAL_POINTER_VECTOR_VARIANT_WRAPPER_HPP
#define MLPACK_CORE_CEREAL_POINTER_VECTOR_VARIANT_WRAPPER_HPP

#include "pointer_wrapper.hpp"
#include "pointer_variant_wrapper.hpp"
#include "pointer_vector_wrapper.hpp"

namespace cereal {

// Forward declaration
template<typename... VariantTypes>
class PointerVectorVariantWrapper;

/**
 * Serialize a std::vector of boost variants in which the variant in each boost
 * variant is a raw pointer.
 * This wrapper will wrap each boost variant independently by encapsulating each
 * boost variant into the PoninterVariantWrapper we have created already.
 *
 * @param t A reference to a vector of boost variants that holds raw pointer.
 */
template<typename... VariantTypes>
inline PointerVectorVariantWrapper<VariantTypes...>
make_vector_pointer_variant(std::vector<boost::variant<VariantTypes...>>& t)
{
  return PointerVectorVariantWrapper<VariantTypes...>(t);
}

/**
 * The objective of this class is to create a wrapper for
 * a vector of boost::variant that holds pointer.
 * Cereal supports the serialization of boost::variant, but 
 * we need to serialize it if it holds a vector of boost::variant that holds a
 * pointers.
 */
template<typename... VariantTypes>
class PointerVectorVariantWrapper
{
 public:
  PointerVectorVariantWrapper(
      std::vector<boost::variant<VariantTypes...>>& vecPointerVar)
      : vectorPointerVariant(vecPointerVar)
  {}

  template<class Archive>
  void save(Archive& ar) const
  {
    size_t vecSize = vectorPointerVariant.size();
    ar(CEREAL_NVP(vecSize));
    for (size_t i = 0; i < vectorPointerVariant.size(); ++i)
    {
      ar(CEREAL_VARIANT_POINTER(vectorPointerVariant.at(i)));
    }
  }

  template<class Archive>
  void load(Archive& ar)
  {
    size_t vecSize = 0;
    ar(CEREAL_NVP(vecSize));
    vectorPointerVariant.resize(vecSize);
    for (size_t i = 0; i < vectorPointerVariant.size(); ++i)
    {
      ar(CEREAL_VARIANT_POINTER(vectorPointerVariant.at(i)));
    }
  }

 private:
  std::vector<boost::variant<VariantTypes...>>& vectorPointerVariant;
};

/**
 * Cereal does not support the serialization of raw pointer.
 * This macro enable developers to serialize a std vector that holds boost::variants
 * that holds raw pointers by using the above PointerVectorVariantWrapper class
 * which replace the internal raw pointers by smart pointer internally.
 *
 * @param T std::vector<boost::variant> that holds raw pointer to be serialized.
 */
#define CEREAL_VECTOR_VARIANT_POINTER(T) cereal::make_vector_pointer_variant(T)

} // namespace cereal

#endif // CEREAL_POINTER_VECTOR_VARIANT_WRAPPER_HPP

