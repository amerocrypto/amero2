// Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#ifndef BITCOIN_RPC_REGISTER_H
#define BITCOIN_RPC_REGISTER_H

/** These are in one header file to avoid creating tons of single-function
 * headers for everything under src/rpc/ */
class CRPCTable;

/** Register block chain RPC commands */
void RegisterBlockchainRPCCommands(CRPCTable &tableRPC);
/** Register P2P networking RPC commands */
void RegisterNetRPCCommands(CRPCTable &tableRPC);
/** Register miscellaneous RPC commands */
void RegisterMiscRPCCommands(CRPCTable &tableRPC);
/** Register mining RPC commands */
void RegisterMiningRPCCommands(CRPCTable &tableRPC);
/** Register raw transaction RPC commands */
void RegisterRawTransactionRPCCommands(CRPCTable &tableRPC);
/** Register masternode RPC commands */
void RegisterMasternodeRPCCommands(CRPCTable &tableRPC);
/** Register CoinJoin RPC commands */
void RegisterCoinJoinRPCCommands(CRPCTable &tableRPC);
/** Register governance RPC commands */
void RegisterGovernanceRPCCommands(CRPCTable &tableRPC);
/** Register Evo RPC commands */
void RegisterEvoRPCCommands(CRPCTable &tableRPC);
/** Register Quorums RPC commands */
void RegisterQuorumsRPCCommands(CRPCTable &tableRPC);

static inline void RegisterAllCoreRPCCommands(CRPCTable &t)
{
    RegisterBlockchainRPCCommands(t);
    RegisterNetRPCCommands(t);
    RegisterMiscRPCCommands(t);
    RegisterMiningRPCCommands(t);
    RegisterRawTransactionRPCCommands(t);
    RegisterMasternodeRPCCommands(t);
    RegisterCoinJoinRPCCommands(t);
    RegisterGovernanceRPCCommands(t);
    RegisterEvoRPCCommands(t);
    RegisterQuorumsRPCCommands(t);
}

#endif // BITCOIN_RPC_REGISTER_H
