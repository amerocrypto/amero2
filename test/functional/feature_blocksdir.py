#!/usr/bin/env python3
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
"""Test the blocksdir option.
"""

import os
import shutil

from test_framework.test_framework import BitcoinTestFramework, initialize_datadir


class BlocksdirTest(BitcoinTestFramework):
    def set_test_params(self):
        self.setup_clean_chain = True
        self.num_nodes = 1

    def run_test(self):
        self.stop_node(0)
        shutil.rmtree(self.nodes[0].datadir)
        initialize_datadir(self.options.tmpdir, 0, self.chain)
        self.log.info("Starting with non exiting blocksdir ...")
        blocksdir_path = os.path.join(self.options.tmpdir, 'blocksdir')
        self.nodes[0].assert_start_raises_init_error(["-blocksdir=" + blocksdir_path], 'Error: Specified blocks directory "' +
                                            blocksdir_path + '" does not exist.')
        os.mkdir(blocksdir_path)
        self.log.info("Starting with exiting blocksdir ...")
        self.start_node(0, ["-blocksdir=" + blocksdir_path])
        self.log.info("mining blocks..")
        self.nodes[0].generate(10)
        assert os.path.isfile(os.path.join(blocksdir_path, self.chain, "blocks", "blk00000.dat"))
        assert os.path.isdir(os.path.join(self.nodes[0].datadir, self.chain, "blocks", "index"))


if __name__ == '__main__':
    BlocksdirTest().main()
