// Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#ifndef BITCOIN_CONSENSUS_MERKLE_H
#define BITCOIN_CONSENSUS_MERKLE_H

#include <stdint.h>
#include <vector>

#include <primitives/transaction.h>
#include <primitives/block.h>
#include <uint256.h>

uint256 ComputeMerkleRoot(std::vector<uint256> hashes, bool* mutated = nullptr);

/*
 * Compute the Merkle root of the transactions in a block.
 * *mutated is set to true if a duplicated subtree was found.
 */
uint256 BlockMerkleRoot(const CBlock& block, bool* mutated = nullptr);

#endif // BITCOIN_CONSENSUS_MERKLE_H
