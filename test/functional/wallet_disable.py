#!/usr/bin/env python3
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
"""Test a node with the -disablewallet option.

- Test that validateaddress RPC works when running with -disablewallet
- Test that it is not possible to mine to an invalid address.
"""

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import *

class DisableWalletTest (BitcoinTestFramework):
    def set_test_params(self):
        self.setup_clean_chain = True
        self.num_nodes = 1
        self.extra_args = [["-disablewallet"]]

    def run_test (self):
        # Make sure wallet is really disabled
        assert_raises_rpc_error(-32601, 'Method not found', self.nodes[0].getwalletinfo)
        x = self.nodes[0].validateaddress('7TSBtVu959hGEGPKyHjJz9k55RpWrPffXz')
        assert(x['isvalid'] == False)
        x = self.nodes[0].validateaddress('ycwedq2f3sz2Yf9JqZsBCQPxp18WU3Hp4J')
        assert(x['isvalid'] == True)

        # Checking mining to an address without a wallet. Generating to a valid address should succeed
        # but generating to an invalid address will fail.
        self.nodes[0].generatetoaddress(1, 'ycwedq2f3sz2Yf9JqZsBCQPxp18WU3Hp4J')
        assert_raises_rpc_error(-5, "Invalid address", self.nodes[0].generatetoaddress, 1, '7TSBtVu959hGEGPKyHjJz9k55RpWrPffXz')

if __name__ == '__main__':
    DisableWalletTest ().main ()
