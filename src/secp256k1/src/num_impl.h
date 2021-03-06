/**********************************************************************
 * Public Resource β 2021 Pieter Wuille                             *
 * Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ   *
 * THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.*
 **********************************************************************/

#ifndef SECP256K1_NUM_IMPL_H
#define SECP256K1_NUM_IMPL_H

#if defined HAVE_CONFIG_H
#include "libsecp256k1-config.h"
#endif

#include "num.h"

#if defined(USE_NUM_GMP)
#include "num_gmp_impl.h"
#elif defined(USE_NUM_NONE)
/* Nothing. */
#else
#error "Please select num implementation"
#endif

#endif /* SECP256K1_NUM_IMPL_H */
