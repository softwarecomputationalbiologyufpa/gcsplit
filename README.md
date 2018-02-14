# GCSplit

Data partitioning algorithm for reduction of complexity and improvement of metagenomic assemblies.

## Installation

To clone the repository, type `git clone https://github.com/mirand863/gcsplit.git`

To install GCSplit and its dependencies, type `cd gcsplit`, `bash install.sh` and `source ~/.bashrc`

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
@article{gcsplit2018,
  title={Improving Metagenomic Assemblies Through Data Partitioning: a GC content approach},
  author={Miranda, Fabio Malcher and Batista, Cassio and Silva, Artur and Morais, Jefferson and Neto, Nelson and Ramos, Rommel},
  journal={bioRxiv},
  pages={261784},
  year={2018},
  publisher={Cold Spring Harbor Laboratory},
  doi={10.1101/261784},
  url={https://doi.org/10.1101/261784}
}
```
