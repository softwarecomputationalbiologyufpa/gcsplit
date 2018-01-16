#ifndef KMERSTREAM_H
#define KMERSTREAM_H

#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Utils.h"
#include "TSV.h"

using namespace std;

class KmerStream {
    private:
        string r1;
        string r2;
        int threads;
        string outputdir;
        vector<int> testedKmers;
        string tsvFile;
        Utils utils;
        void calculateTestedKmers();
        void runCommand();
    public:
        KmerStream(string r1, string r2, int threads, string outputdir);
        vector<int> getBestK(int kmers);
};

#endif // KMERSTREAM_H
