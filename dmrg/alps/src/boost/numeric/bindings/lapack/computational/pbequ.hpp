//
// Copyright (c) 2002--2010
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PBEQU_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_PBEQU_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/bandwidth.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/uplo_tag.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for pbequ is the netlib-compatible backend.
//
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end LAPACK-routine.
//
namespace detail {

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * float value-type.
//
template< typename UpLo >
inline std::ptrdiff_t pbequ( const UpLo, const fortran_int_t n,
        const fortran_int_t kd, const float* ab, const fortran_int_t ldab,
        float* s, float& scond, float& amax ) {
    fortran_int_t info(0);
    LAPACK_SPBEQU( &lapack_option< UpLo >::value, &n, &kd, ab, &ldab, s,
            &scond, &amax, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename UpLo >
inline std::ptrdiff_t pbequ( const UpLo, const fortran_int_t n,
        const fortran_int_t kd, const double* ab, const fortran_int_t ldab,
        double* s, double& scond, double& amax ) {
    fortran_int_t info(0);
    LAPACK_DPBEQU( &lapack_option< UpLo >::value, &n, &kd, ab, &ldab, s,
            &scond, &amax, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t pbequ( const UpLo, const fortran_int_t n,
        const fortran_int_t kd, const std::complex<float>* ab,
        const fortran_int_t ldab, float* s, float& scond, float& amax ) {
    fortran_int_t info(0);
    LAPACK_CPBEQU( &lapack_option< UpLo >::value, &n, &kd, ab, &ldab, s,
            &scond, &amax, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t pbequ( const UpLo, const fortran_int_t n,
        const fortran_int_t kd, const std::complex<double>* ab,
        const fortran_int_t ldab, double* s, double& scond, double& amax ) {
    fortran_int_t info(0);
    LAPACK_ZPBEQU( &lapack_option< UpLo >::value, &n, &kd, ab, &ldab, s,
            &scond, &amax, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to pbequ.
//
template< typename Value, typename Enable = void >
struct pbequ_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct pbequ_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename VectorS >
    static std::ptrdiff_t invoke( const MatrixAB& ab, VectorS& s,
            real_type& scond, real_type& amax ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixAB >::type uplo;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixAB >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixAB >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorS >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorS >::value) );
        BOOST_ASSERT( bindings::bandwidth(ab, uplo()) >= 0 );
        BOOST_ASSERT( bindings::size_column(ab) >= 0 );
        BOOST_ASSERT( bindings::size_minor(ab) == 1 ||
                bindings::stride_minor(ab) == 1 );
        BOOST_ASSERT( bindings::stride_major(ab) >= bindings::bandwidth(ab,
                uplo())+1 );
        return detail::pbequ( uplo(), bindings::size_column(ab),
                bindings::bandwidth(ab, uplo()), bindings::begin_value(ab),
                bindings::stride_major(ab), bindings::begin_value(s), scond,
                amax );
    }

};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct pbequ_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixAB, typename VectorS >
    static std::ptrdiff_t invoke( const MatrixAB& ab, VectorS& s,
            real_type& scond, real_type& amax ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixAB >::type uplo;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixAB >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorS >::value) );
        BOOST_ASSERT( bindings::bandwidth(ab, uplo()) >= 0 );
        BOOST_ASSERT( bindings::size_column(ab) >= 0 );
        BOOST_ASSERT( bindings::size_minor(ab) == 1 ||
                bindings::stride_minor(ab) == 1 );
        BOOST_ASSERT( bindings::stride_major(ab) >= bindings::bandwidth(ab,
                uplo())+1 );
        return detail::pbequ( uplo(), bindings::size_column(ab),
                bindings::bandwidth(ab, uplo()), bindings::begin_value(ab),
                bindings::stride_major(ab), bindings::begin_value(s), scond,
                amax );
    }

};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the pbequ_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for pbequ. Its overload differs for
//
template< typename MatrixAB, typename VectorS >
inline std::ptrdiff_t pbequ( const MatrixAB& ab, VectorS& s,
        typename remove_imaginary< typename bindings::value_type<
        MatrixAB >::type >::type& scond, typename remove_imaginary<
        typename bindings::value_type< MatrixAB >::type >::type& amax ) {
    return pbequ_impl< typename bindings::value_type<
            MatrixAB >::type >::invoke( ab, s, scond, amax );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
