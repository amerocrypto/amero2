// Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#ifndef BITCOIN_ZMQ_ZMQABSTRACTNOTIFIER_H
#define BITCOIN_ZMQ_ZMQABSTRACTNOTIFIER_H

#include <zmq/zmqconfig.h>

class CBlockIndex;
class CGovernanceObject;
class CGovernanceVote;
class CZMQAbstractNotifier;

namespace llmq {
    class CChainLockSig;
    class CInstantSendLock;
    class CRecoveredSig;
} // namespace llmq

typedef CZMQAbstractNotifier* (*CZMQNotifierFactory)();

class CZMQAbstractNotifier
{
public:
    CZMQAbstractNotifier() : psocket(nullptr) { }
    virtual ~CZMQAbstractNotifier();

    template <typename T>
    static CZMQAbstractNotifier* Create()
    {
        return new T();
    }

    std::string GetType() const { return type; }
    void SetType(const std::string &t) { type = t; }
    std::string GetAddress() const { return address; }
    void SetAddress(const std::string &a) { address = a; }

    virtual bool Initialize(void *pcontext) = 0;
    virtual void Shutdown() = 0;

    virtual bool NotifyBlock(const CBlockIndex *pindex);
    virtual bool NotifyChainLock(const CBlockIndex *pindex, const std::shared_ptr<const llmq::CChainLockSig>& clsig);
    virtual bool NotifyTransaction(const CTransaction &transaction);
    virtual bool NotifyTransactionLock(const CTransactionRef& transaction, const std::shared_ptr<const llmq::CInstantSendLock>& islock);
    virtual bool NotifyGovernanceVote(const std::shared_ptr<const CGovernanceVote>& vote);
    virtual bool NotifyGovernanceObject(const std::shared_ptr<const CGovernanceObject>& object);
    virtual bool NotifyInstantSendDoubleSpendAttempt(const CTransactionRef& currentTx, const CTransactionRef& previousTx);
    virtual bool NotifyRecoveredSig(const std::shared_ptr<const llmq::CRecoveredSig>& sig);

protected:
    void *psocket;
    std::string type;
    std::string address;
};

#endif // BITCOIN_ZMQ_ZMQABSTRACTNOTIFIER_H
