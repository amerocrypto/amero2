#!/usr/bin/env python3
# Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
# Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
"""Test the getchaintips RPC.

- introduce a network split
- work on chains of different lengths
- join the network together again
- verify that getchaintips now returns two chain tips.
"""

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import assert_equal

class GetChainTipsTest (BitcoinTestFramework):
    def set_test_params(self):
        self.num_nodes = 4

    def run_test (self):
        tips = self.nodes[0].getchaintips ()
        assert_equal (len (tips), 1)
        assert_equal (tips[0]['branchlen'], 0)
        assert_equal (tips[0]['height'], 200)
        assert_equal (tips[0]['status'], 'active')

        # Split the network and build two chains of different lengths.
        self.split_network ()
        self.nodes[0].generate(10)
        self.nodes[2].generate(20)
        self.sync_all(self.nodes[:2])
        self.sync_all(self.nodes[2:])

        tips = self.nodes[1].getchaintips ()
        assert_equal (len (tips), 1)
        shortTip = tips[0]
        assert_equal (shortTip['branchlen'], 0)
        assert_equal (shortTip['height'], 210)
        assert_equal (tips[0]['status'], 'active')

        tips = self.nodes[3].getchaintips ()
        assert_equal (len (tips), 1)
        longTip = tips[0]
        assert_equal (longTip['branchlen'], 0)
        assert_equal (longTip['height'], 220)
        assert_equal (tips[0]['status'], 'active')

        # Join the network halves and check that we now have two tips
        # (at least at the nodes that previously had the short chain).
        self.join_network ()

        tips = self.nodes[0].getchaintips ()
        assert_equal (len (tips), 2)
        assert_equal (tips[0], longTip)

        assert_equal (tips[1]['branchlen'], 10)
        assert_equal (tips[1]['status'], 'valid-fork')
        # We already checked that the long tip is the active one,
        # update data to verify that the short tip matches the expected one.
        tips[1]['branchlen'] = 0
        tips[1]['status'] = 'active'
        tips[1]['forkpoint'] = tips[1]['hash']
        assert_equal (tips[1], shortTip)

if __name__ == '__main__':
    GetChainTipsTest ().main ()
