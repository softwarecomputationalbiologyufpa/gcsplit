#include <iostream>
#include <vector>
#include <string>
#include "KmerStream.h"
#include "GCSplit.h"
#include "MetaSpades.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc == 5) {
        string r1 = argv[1];
        string r2 = argv[2];
        int threads = atoi(argv[3]);
        string outputdir = argv[4];

        KmerStream bestkmers(r1, r2, threads, outputdir);
        vector<int> bestk = bestkmers.getBestK(10);
        GCSplit gcsplit(r1, r2, threads, outputdir);
        gcsplit.split();
        MetaSpades metaspades(threads, bestk, outputdir);
        metaspades.run();
    } else {
        cout << "Usage: " << argv[0] << " r1 r2 threads outputdir" << endl;
    }
    return 0;
}
