// Public Resource β 2021 ΔπΊππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#ifndef BITCOIN_MASTERNODE_MASTERNODE_PAYMENTS_H
#define BITCOIN_MASTERNODE_MASTERNODE_PAYMENTS_H

#include <util.h>
#include <core_io.h>
#include <key.h>
#include <net_processing.h>
#include <utilstrencodings.h>

#include <evo/deterministicmns.h>

class CMasternodePayments;

/// TODO: all 4 functions do not belong here really, they should be refactored/moved somewhere (main.cpp ?)
bool IsBlockValueValid(const CBlock& block, int nBlockHeight, CAmount blockReward, std::string& strErrorRet);
bool IsBlockPayeeValid(const CTransaction& txNew, int nBlockHeight, CAmount blockReward);
void FillBlockPayments(CMutableTransaction& txNew, int nBlockHeight, CAmount blockReward, std::vector<CTxOut>& voutMasternodePaymentsRet, std::vector<CTxOut>& voutSuperblockPaymentsRet);

extern CMasternodePayments mnpayments;

//
// Masternode Payments Class
// Keeps track of who should get paid for which blocks
//

class CMasternodePayments
{
public:
    static bool GetBlockTxOuts(int nBlockHeight, CAmount blockReward, std::vector<CTxOut>& voutMasternodePaymentsRet);
    static bool IsTransactionValid(const CTransaction& txNew, int nBlockHeight, CAmount blockReward);

    static bool GetMasternodeTxOuts(int nBlockHeight, CAmount blockReward, std::vector<CTxOut>& voutMasternodePaymentsRet);
};

#endif // BITCOIN_MASTERNODE_MASTERNODE_PAYMENTS_H
