// Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#ifndef BITCOIN_RPC_RAWTRANSACTION_H
#define BITCOIN_RPC_RAWTRANSACTION_H

class CBasicKeyStore;
struct CMutableTransaction;
class UniValue;

/** Sign a transaction with the given keystore and previous transactions */
UniValue SignTransaction(CMutableTransaction& mtx, const UniValue& prevTxs, CBasicKeyStore *keystore, bool tempKeystore, const UniValue& hashType);

#endif // BITCOIN_RPC_RAWTRANSACTION_H
