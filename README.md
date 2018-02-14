# GCSplit

Data partitioning algorithm for reduction of complexity and improvement of metagenomic assemblies.

## Installation

To clone the repository, type `cd` and `git clone https://github.com/mirand863/gcsplit.git`

To compile just type `cd gcsplit` and `make`

GCSplit can be added to the environment variable $PATH through the command `echo 'export PATH=~/gcsplit/bin/Debug:$PATH' >> ~/.bashrc` and `source ~/.bashrc`

## Dependencies

GCSplit requires GCC version 4.4.7 or higher, the library OpenMP and the software KmerStream and metaSPAdes in order to automatically perform assemblies.

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
GCSplit v1.1

A software to partition paired FASTQ files

Usage: gcsplit r1 r2 partitions k-mers threads outputdir

r1		File with forward reads
r2		File with reverse reads
partitions	Number of partitions
k-mers		Number of k-mers to run the assembly
threads		Number of threads
outputdir	Specify the output directory
~~~

## Citation

If you use GCSplit, please cite:

>Miranda, F.M., Batista, C., Silva, A., Morais, J., Neto, N. and Ramos, R., 2018. Improving Metagenomic Assemblies Through Data Partitioning: a GC content approach. bioRxiv, p.261784.

```
@article{miranda2018improving,
  title={Improving Metagenomic Assemblies Through Data Partitioning: a GC content approach},
  author={Miranda, Fabio Malcher and Batista, Cassio and Silva, Artur and Morais, Jefferson and Neto, Nelson and Ramos, Rommel},
  journal={bioRxiv},
  pages={261784},
  year={2018},
  publisher={Cold Spring Harbor Laboratory}
}
```
