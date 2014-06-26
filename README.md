Bitcoin Malleability Research
=====================================
Install(Debian/Ubuntu)
---------------
**Git**
```bash
git clone https://github.com/hophacker/bitcoin_malleability
git checkout malleability_detection
```

**Required Libraries**

```bash
sudo apt-get install autoconf2.13  libdb5.1++-dev g++  make libboost1.54-all-dev
sudo apt-get install libqt4-core libqt4-gui libqt4-dev openssl libssl-dev
sudo apt-get install pkg-config
```
**Comiple**
```bash
./autogen.sh
./configure --with-incompatible-bdb
make
make install
```



**Run**

Running Options: 
* -noBlkInfo
* -noTXInfo
* -noMerkleTreeInfo
* -printblockMai
* -startHeight
* -endHeight

Running Examples:
* `./bitcoind -printblockMai -noMerkleTreeInfo -noBlkInfo -startHeight=300000 -endHeight=310000`: dump transactions information from blockheight 300000 to blockheight 310000 without information of block or merkle tree 

**Reference**

[Installing bitcoin in ubuntu](http://birdchan.com/home/2013/11/26/installing-bitcoin-in-ubuntu/)




**documentation**
Go to the “bitcoin” folder and copy the configuration file there, generate, open: 
```bash
~$ cd bitcoin
~$ doxygen bitcoind.dox
~$ cd html
~$ open index.html
```

**Reading the code**
* [Client Initialization and Startup](https://en.bitcoin.it/wiki/Satoshi_Client_Initialization_and_Startup)
* [Running Bitcoin](https://en.bitcoin.it/wiki/Running_Bitcoin)
* [Development, debug tips and tricks](https://github.com/bitcoin/bitcoin)ss
