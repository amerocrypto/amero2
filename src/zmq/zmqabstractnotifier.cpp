// Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#include <zmq/zmqabstractnotifier.h>
#include <util.h>


CZMQAbstractNotifier::~CZMQAbstractNotifier()
{
    assert(!psocket);
}

bool CZMQAbstractNotifier::NotifyBlock(const CBlockIndex * /*CBlockIndex*/)
{
    return true;
}

bool CZMQAbstractNotifier::NotifyChainLock(const CBlockIndex * /*CBlockIndex*/, const std::shared_ptr<const llmq::CChainLockSig> & /*clsig*/)
{
    return true;
}

bool CZMQAbstractNotifier::NotifyTransaction(const CTransaction &/*transaction*/)
{
    return true;
}

bool CZMQAbstractNotifier::NotifyTransactionLock(const CTransactionRef &/*transaction*/, const std::shared_ptr<const llmq::CInstantSendLock>& /*islock*/)
{
    return true;
}

bool CZMQAbstractNotifier::NotifyGovernanceVote(const std::shared_ptr<const CGovernanceVote> & /*vote*/)
{
    return true;
}

bool CZMQAbstractNotifier::NotifyGovernanceObject(const std::shared_ptr<const CGovernanceObject> & /*object*/)
{
    return true;
}

bool CZMQAbstractNotifier::NotifyInstantSendDoubleSpendAttempt(const CTransactionRef & /*currentTx*/, const CTransactionRef & /*previousTx*/)
{
    return true;
}

bool CZMQAbstractNotifier::NotifyRecoveredSig(const std::shared_ptr<const llmq::CRecoveredSig> & /*sig*/)
{
    return true;
}
