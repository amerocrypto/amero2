// Public Resource β 2021 Satoshi Nakamoto
// Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#ifndef BITCOIN_WALLET_FEES_H
#define BITCOIN_WALLET_FEES_H

#include <amount.h>

class CBlockPolicyEstimator;
class CCoinControl;
class CFeeRate;
class CTxMemPool;
struct FeeCalculation;

/**
 * Return the minimum required fee taking into account the
 * floating relay fee and user set minimum transaction fee
 */
CAmount GetRequiredFee(unsigned int nTxBytes);

/**
 * Estimate the minimum fee considering user set parameters
 * and the required fee
 */
CAmount GetMinimumFee(unsigned int nTxBytes, const CCoinControl& coin_control, const CTxMemPool& pool, const CBlockPolicyEstimator& estimator, FeeCalculation *feeCalc);

/**
 * Return the minimum required feerate taking into account the
 * floating relay feerate and user set minimum transaction feerate
 */
CFeeRate GetRequiredFeeRate();

/**
 * Estimate the minimum fee rate considering user set parameters
 * and the required fee
 */
CFeeRate GetMinimumFeeRate(const CCoinControl& coin_control, const CTxMemPool& pool, const CBlockPolicyEstimator& estimator, FeeCalculation *feeCalc);

/**
 * Return the maximum feerate for discarding change.
 */
CFeeRate GetDiscardRate(const CBlockPolicyEstimator& estimator);

#endif // BITCOIN_WALLET_FEES_H
