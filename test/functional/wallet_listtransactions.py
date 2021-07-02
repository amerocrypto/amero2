#!/usr/bin/env python3
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
"""Test the listtransactions API."""

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import *
from test_framework.mininode import CTransaction
from io import BytesIO

def txFromHex(hexstring):
    tx = CTransaction()
    f = BytesIO(hex_str_to_bytes(hexstring))
    tx.deserialize(f)
    return tx

class ListTransactionsTest(BitcoinTestFramework):
    def set_test_params(self):
        self.num_nodes = 2
        self.set_cache_mocktime()

    def run_test(self):
        # Simple send, 0 to 1:
        txid = self.nodes[0].sendtoaddress(self.nodes[1].getnewaddress(), 0.1)
        self.sync_all()
        assert_array_result(self.nodes[0].listtransactions(),
                           {"txid":txid},
                           {"category":"send","amount":Decimal("-0.1"),"confirmations":0})
        assert_array_result(self.nodes[1].listtransactions(),
                           {"txid":txid},
                           {"category":"receive","amount":Decimal("0.1"),"confirmations":0})
        # mine a block, confirmations should change:
        self.nodes[0].generate(1)
        self.sync_all()
        assert_array_result(self.nodes[0].listtransactions(),
                           {"txid":txid},
                           {"category":"send","amount":Decimal("-0.1"),"confirmations":1})
        assert_array_result(self.nodes[1].listtransactions(),
                           {"txid":txid},
                           {"category":"receive","amount":Decimal("0.1"),"confirmations":1})

        # send-to-self:
        txid = self.nodes[0].sendtoaddress(self.nodes[0].getnewaddress(), 0.2)
        assert_array_result(self.nodes[0].listtransactions(),
                           {"txid":txid, "category":"send"},
                           {"amount":Decimal("-0.2")})
        assert_array_result(self.nodes[0].listtransactions(),
                           {"txid":txid, "category":"receive"},
                           {"amount":Decimal("0.2")})

        # sendmany from node1: twice to self, twice to node2:
        send_to = { self.nodes[0].getnewaddress() : 0.11,
                    self.nodes[1].getnewaddress() : 0.22,
                    self.nodes[0].getnewaddress() : 0.33,
                    self.nodes[1].getnewaddress() : 0.44 }
        txid = self.nodes[1].sendmany("", send_to)
        self.sync_all()
        assert_array_result(self.nodes[1].listtransactions(),
                           {"category":"send","amount":Decimal("-0.11")},
                           {"txid":txid} )
        assert_array_result(self.nodes[0].listtransactions(),
                           {"category":"receive","amount":Decimal("0.11")},
                           {"txid":txid} )
        assert_array_result(self.nodes[1].listtransactions(),
                           {"category":"send","amount":Decimal("-0.22")},
                           {"txid":txid} )
        assert_array_result(self.nodes[1].listtransactions(),
                           {"category":"receive","amount":Decimal("0.22")},
                           {"txid":txid} )
        assert_array_result(self.nodes[1].listtransactions(),
                           {"category":"send","amount":Decimal("-0.33")},
                           {"txid":txid} )
        assert_array_result(self.nodes[0].listtransactions(),
                           {"category":"receive","amount":Decimal("0.33")},
                           {"txid":txid} )
        assert_array_result(self.nodes[1].listtransactions(),
                           {"category":"send","amount":Decimal("-0.44")},
                           {"txid":txid} )
        assert_array_result(self.nodes[1].listtransactions(),
                           {"category":"receive","amount":Decimal("0.44")},
                           {"txid":txid} )

        pubkey = self.nodes[1].getaddressinfo(self.nodes[1].getnewaddress())['pubkey']
        multisig = self.nodes[1].createmultisig(1, [pubkey])
        self.nodes[0].importaddress(multisig["redeemScript"], "watchonly", False, True)
        txid = self.nodes[1].sendtoaddress(multisig["address"], 0.1)
        self.nodes[1].generate(1)
        self.sync_all()
        assert len(self.nodes[0].listtransactions(label="watchonly", count=100, skip=0, include_watchonly=False)) == 0
        assert_array_result(self.nodes[0].listtransactions(label="watchonly", count=100, skip=0, include_watchonly=True),
                            {"category": "receive", "amount": Decimal("0.1")},
                            {"txid": txid, "label": "watchonly"})

if __name__ == '__main__':
    ListTransactionsTest().main()
