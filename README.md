# GCSplit

Data partitioning algorithm for reduction of complexity and improvement of genomic and metagenomic assemblies.

## Installation

To clone the repository, type `git clone https://github.com/mirand863/gcsplit.git`

To install GCSplit and its dependencies, type `cd gcsplit`, `bash install.sh` and `source ~/.bashrc`

## Running

To see the usage just type `gcsplit`

~~~
GCSplit v1.3

A software to partition paired FASTQ files

Usage: ./bin/Debug/gcsplit [options] -o <output_dir> 

Basic options:
    -o/--output <output_dir>           Folder to store all the files generated during the assembly (required).
    -p/--partitions <int>              Number of partitions [default: 16]
    -w/--whole                         Use whole dataset to merge [default: off]
    --iontorrent                       This flag is required for IonTorrent data.
    --meta                             This flag is required for metagenomic datasets.
    -h/--help                          Prints this usage message.
    -v/--version                       Prints version info

Input data:
    -f/--forward <filename>            File with forward paired-end reads.
    -r/--reverse <filename>            File with reverse paired-end reads.
    -s/--single <filename>             File with unpaired reads.

Advanced options:
    -t/--threads <int>                 Number of threads [default: 4]
    --skip-kmerstream <int,int,...>    Skip KmerStream and run SPAdes or MetaSPAdes with specified k-mer(s)
                                       K-mer value(s) must be odd and less than 128
    -k/--kmers <int>                   Number of kmers to run the assembly [default: 3]

Please, report bugs to: miranda.fmm@gmail.com
Software homepage: <https://github.com/mirand863/gcsplit>
~~~

## Citation

If you use GCSplit, please cite:

>Miranda F., Batista C., Silva A., Morais J., Neto N., Ramos R. (2018) Improving Metagenomic Assemblies Through Data Partitioning: A GC Content Approach. In: Rojas I., Ortuño F. (eds) Bioinformatics and Biomedical Engineering. IWBBIO 2018. Lecture Notes in Computer Science, vol 10813. Springer, Cham.

```
@inproceedings{miranda2018gcsplit,
  author="Miranda, F{\'a}bio and Batista, Cassio and Silva, Artur and Morais, Jefferson and Neto, Nelson and Ramos, Rommel",
  editor="Rojas, Ignacio and Ortu{\~{n}}o, Francisco",
  title="Improving Metagenomic Assemblies Through Data Partitioning: A GC Content Approach",
  booktitle="Bioinformatics and Biomedical Engineering",
  year="2018",
  publisher="Springer International Publishing",
  address="Cham",
  pages="415--425",
  doi={10.1007/978-3-319-78723-7_36},
  url={https://doi.org/10.1007/978-3-319-78723-7_36},
  isbn="978-3-319-78723-7"
}
```
