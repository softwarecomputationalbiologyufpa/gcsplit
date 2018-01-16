# GCSplit

Data partitioning algorithm for reduction of complexity and improvement of metagenomic assemblies.

## Installation

To clone the repository, type `cd` and `git clone https://github.com/mirand863/gcsplit.git`

To compile just type `cd gcsplit` and `make`

GCSplit can be added to the environment variable $PATH through the command `echo 'export PATH=~/gcsplit/bin/Debug:$PATH' >> ~/.bashrc` and `source ~/.bashrc`

## Dependencies

GCSplit depends on KmerStream and SPAdes in order to automatically perform assemblies.

To download SPAdes to your home directory, type `cd` and `wget http://cab.spbu.ru/files/release3.11.1/SPAdes-3.11.1-Linux.tar.gz`

To extract spades type `tar -xvzf SPAdes-3.11.1-Linux.tar.gz`

SPAdes needs to be in the $PATH environment variable to be automatically executed. In order to do this, we issue the following commands: `echo 'export PATH=~/SPAdes-3.11.1-Linux/bin:$PATH' >> ~/.bashrc` and `source ~/.bashrc`

To test that SPAdes is running correctly, just type `spades.py`

To clone KmerStream to your home directory, type `cd` and `git clone https://github.com/pmelsted/KmerStream.git`

To compile KmerStream, type `cd KmerStream` and `make`

To add KmerStream to the $PATH environment variable, type `echo 'export PATH=~/KmerStream:$PATH' >> ~/.bashrc` and `source ~/.bashrc`

To test that KmerStream is running correctly, type `KmerStream`

## Running

To see the usage just type `gcsplit`

~~~
GCSplit 1.0

Partitions paired fastq files, runs the assembly and saves results

Usage: gcsplit r1 r2 threads outputdir

r1          File with forward reads
r2          File with reverse reads
threads     Number of threads
outputdir   Specify the output directory
~~~