#include <iostream>
#include <vector>
#include <string>
#include "KmerStream.h"
#include "GCSplit.h"
#include "MetaSpades.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc == 7) {
        string r1 = argv[1];
        string r2 = argv[2];
        int partitions = atoi(argv[3]);
        int kmers = atoi(argv[4]);
        int threads = atoi(argv[5]);
        string outputdir = argv[6];

        KmerStream bestkmers(r1, r2, threads, outputdir);
        vector<int> bestk = bestkmers.getBestK(kmers);
        GCSplit gcsplit(r1, r2, partitions, threads, outputdir);
        gcsplit.split();
        MetaSpades metaspades(threads, partitions, bestk, outputdir);
        metaspades.run();
    } else {
        cout << endl << "GCSplit v1.1" << endl << endl;
        cout << "A software to partition paired FASTQ files" << endl << endl;
        cout << "Usage: " << argv[0] << " r1 r2 partitions k-mers threads outputdir" << endl << endl;
        cout << "r1\t\tFile with forward reads" << endl;
        cout << "r2\t\tFile with reverse reads" << endl;
        cout << "partitions\tNumber of partitions" << endl;
        cout << "k-mers\t\tNumber of k-mers to run the assembly" << endl;
        cout << "threads\t\tNumber of threads" << endl;
        cout << "outputdir\tSpecify the output directory" << endl << endl;
    }
    return 0;
}
