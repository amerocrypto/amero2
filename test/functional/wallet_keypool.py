#!/usr/bin/env python3
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
"""Test the wallet keypool and interaction with wallet encryption/locking."""

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import *

class KeyPoolTest(BitcoinTestFramework):
    def set_test_params(self):
        self.num_nodes = 1
        self.extra_args = [['-usehd=0']]

    def run_test(self):
        nodes = self.nodes

        # Encrypt wallet and wait to terminate
        nodes[0].encryptwallet('test')
        # Keep creating keys
        addr = nodes[0].getnewaddress()

        assert_raises_rpc_error(-12, "Error: Keypool ran out, please call keypoolrefill first", nodes[0].getnewaddress)

        # put three new keys in the keypool
        nodes[0].walletpassphrase('test', 12000)
        nodes[0].keypoolrefill(3)
        nodes[0].walletlock()

        # drain the keys
        addr = set()
        addr.add(nodes[0].getrawchangeaddress())
        addr.add(nodes[0].getrawchangeaddress())
        addr.add(nodes[0].getrawchangeaddress())
        # assert that three unique addresses were returned
        assert(len(addr) == 3)
        # the next one should fail
        assert_raises_rpc_error(-12, "Keypool ran out", nodes[0].getrawchangeaddress)

        # refill keypool with three new addresses
        nodes[0].walletpassphrase('test', 1)
        nodes[0].keypoolrefill(3)
        # test walletpassphrase timeout
        time.sleep(1.1)
        assert_equal(nodes[0].getwalletinfo()["unlocked_until"], 0)

        # drain them by mining
        nodes[0].generate(1)
        nodes[0].generate(1)
        nodes[0].generate(1)
        assert_raises_rpc_error(-12, "Keypool ran out", nodes[0].generate, 1)

if __name__ == '__main__':
    KeyPoolTest().main()
