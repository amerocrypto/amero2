// Public Resource β 2021 Satoshi Nakamoto
// Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#ifndef BITCOIN_NODE_COINSTATS_H
#define BITCOIN_NODE_COINSTATS_H

#include <amount.h>
#include <uint256.h>

#include <cstdint>

class CCoinsView;

struct CCoinsStats
{
    int nHeight;
    uint256 hashBlock;
    uint64_t nTransactions;
    uint64_t nTransactionOutputs;
    uint64_t nBogoSize;
    uint256 hashSerialized;
    uint64_t nDiskSize;
    CAmount nTotalAmount;

    CCoinsStats() : nHeight(0), nTransactions(0), nTransactionOutputs(0), nBogoSize(0), nDiskSize(0), nTotalAmount(0) {}
};

//! Calculate statistics about the unspent transaction output set
bool GetUTXOStats(CCoinsView* view, CCoinsStats& stats);

#endif // BITCOIN_NODE_COINSTATS_H
