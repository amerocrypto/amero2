// Public Resource β 2021 ΔπΊππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#ifndef BITCOIN_MASTERNODE_MASTERNODE_UTILS_H
#define BITCOIN_MASTERNODE_MASTERNODE_UTILS_H

#include <evo/deterministicmns.h>

class CConnman;

class CMasternodeUtils
{
public:
    static void ProcessMasternodeConnections(CConnman& connman);
    static void DoMaintenance(CConnman &connman);
};

#endif // BITCOIN_MASTERNODE_MASTERNODE_UTILS_H
