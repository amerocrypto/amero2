// Public Resource β 2021 ΔπΊππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#include <evo/evodb.h>

std::unique_ptr<CEvoDB> evoDb;

CEvoDBScopedCommitter::CEvoDBScopedCommitter(CEvoDB &_evoDB) :
    evoDB(_evoDB)
{
}

CEvoDBScopedCommitter::~CEvoDBScopedCommitter()
{
    if (!didCommitOrRollback)
        Rollback();
}

void CEvoDBScopedCommitter::Commit()
{
    assert(!didCommitOrRollback);
    didCommitOrRollback = true;
    evoDB.CommitCurTransaction();
}

void CEvoDBScopedCommitter::Rollback()
{
    assert(!didCommitOrRollback);
    didCommitOrRollback = true;
    evoDB.RollbackCurTransaction();
}

CEvoDB::CEvoDB(size_t nCacheSize, bool fMemory, bool fWipe) :
    db(fMemory ? "" : (GetDataDir() / "evodb"), nCacheSize, fMemory, fWipe),
    rootBatch(db),
    rootDBTransaction(db, rootBatch),
    curDBTransaction(rootDBTransaction, rootDBTransaction)
{
}

void CEvoDB::CommitCurTransaction()
{
    LOCK(cs);
    curDBTransaction.Commit();
}

void CEvoDB::RollbackCurTransaction()
{
    LOCK(cs);
    curDBTransaction.Clear();
}

bool CEvoDB::CommitRootTransaction()
{
    LOCK(cs);
    assert(curDBTransaction.IsClean());
    rootDBTransaction.Commit();
    bool ret = db.WriteBatch(rootBatch);
    rootBatch.Clear();
    return ret;
}

bool CEvoDB::VerifyBestBlock(const uint256& hash)
{
    // Make sure evodb is consistent.
    // If we already have best block hash saved, the previous block should match it.
    uint256 hashBestBlock;
    if (!Read(EVODB_BEST_BLOCK, hashBestBlock)) {
        return false;
    }
    return hashBestBlock == hash;
}

void CEvoDB::WriteBestBlock(const uint256& hash)
{
    Write(EVODB_BEST_BLOCK, hash);
}
