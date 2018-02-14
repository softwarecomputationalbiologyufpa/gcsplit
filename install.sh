#!/bin/bash

set -x
WORKDIR=$(pwd)
make
echo 'export PATH='$WORKDIR'/bin/Debug:$PATH' >> ~/.bashrc
wget http://cab.spbu.ru/files/release3.11.1/SPAdes-3.11.1-Linux.tar.gz
tar -xvzf SPAdes-3.11.1-Linux.tar.gz
echo 'export PATH='$WORKDIR'/SPAdes-3.11.1-Linux/bin:$PATH' >> ~/.bashrc
git clone https://github.com/pmelsted/KmerStream.git
cd KmerStream
make
echo 'export PATH='$WORKDIR'/KmerStream:$PATH' >> ~/.bashrc
source ~/.bashrc
