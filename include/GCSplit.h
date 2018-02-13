#ifndef GCSPLIT_H
#define GCSPLIT_H

#include <fstream>
#include <string>
#include <vector>
#include <parallel/algorithm>
#include <omp.h>
#include <sstream>
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
        int partitions;
        Utils utils;
        void load(string file, vector<Fastq> &sequences);
        void loadFiles();
        void computeGCContent();
        void sortSequences();
        void saveFile(int beginning, int ending, string prefix, string suffix);
        void saveResults();
    public:
        GCSplit(string r1, string r2, int partitions, int threads, string outputdir);
        void split();
};

#endif // GCSPLIT_H
