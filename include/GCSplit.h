#ifndef GCSPLIT_H
#define GCSPLIT_H

#include <fstream>
#include <string>
#include <vector>
#include <parallel/algorithm>
#include <omp.h>
#include "Utils.h"
#include "Fastq.h"

using namespace std;

class GCSplit {
    private:
        string r1;
        string r2;
        int threads;
        string outputdir;
        string basename;
        vector<Fastq> left;
        vector<Fastq> right;
        int firstQuartile;
        int median;
        int thirdQuartile;
        Utils utils;
        void load(string file, vector<Fastq> &sequences);
        void loadFiles();
        void computeGCContent();
        void sortSequences();
        int computeHalfIndex(int vectorSize);
        void computeQuartiles();
        void saveFile(int beginning, int ending, string prefix, string suffix);
        void saveResults();
    public:
        GCSplit(string r1, string r2, int threads, string outputdir);
        void split();
};

#endif // GCSPLIT_H
