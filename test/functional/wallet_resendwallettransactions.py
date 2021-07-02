#!/usr/bin/env python3
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
"""Test resendwallettransactions RPC."""

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import assert_equal, assert_raises_rpc_error

class ResendWalletTransactionsTest(BitcoinTestFramework):
    def set_test_params(self):
        self.num_nodes = 1
        self.extra_args = [['--walletbroadcast=false']]

    def run_test(self):
        # Should raise RPC_WALLET_ERROR (-4) if walletbroadcast is disabled.
        assert_raises_rpc_error(-4, "Error: Wallet transaction broadcasting is disabled with -walletbroadcast", self.nodes[0].resendwallettransactions)

        # Should return an empty array if there aren't unconfirmed wallet transactions.
        self.stop_node(0)
        self.start_node(0, extra_args=[])
        assert_equal(self.nodes[0].resendwallettransactions(), [])

        # Should return an array with the unconfirmed wallet transaction.
        txid = self.nodes[0].sendtoaddress(self.nodes[0].getnewaddress(), 1)
        assert_equal(self.nodes[0].resendwallettransactions(), [txid])

if __name__ == '__main__':
    ResendWalletTransactionsTest().main()
