// Public Resource β 2021 ΔπΊππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#include <saltedhasher.h>
#include <random.h>

#include <limits>

SaltedHasherBase::SaltedHasherBase() : k0(GetRand(std::numeric_limits<uint64_t>::max())), k1(GetRand(std::numeric_limits<uint64_t>::max())) {}

SaltedHasherBase StaticSaltedHasher::s;
