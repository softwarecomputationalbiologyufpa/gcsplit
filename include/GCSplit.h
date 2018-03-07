#ifndef GCSPLIT_H
#define GCSPLIT_H

#include <fstream>
#include <string>
#include <vector>
#include <parallel/algorithm>
#include <omp.h>
#include <sstream>
#include "Arguments.h"
#include "Utils.h"
#include "Fastq.h"

using namespace std;

class GCSplit {
    private:
        string forward;
        string reverse;
        string single;
        int threads;
        string outputDir;
        string basename;
        vector<Fastq> left;
        vector<Fastq> right;
        vector<Fastq> sing;
        int partitions;
        Utils utils;
        void load(string file, vector<Fastq> &sequences);
        void loadFiles();
        void computeGCContent();
        void sortSequences();
        void savePairedFiles(int beginning, int ending, string prefix, string suffix);
        void savePairedResults();
        void saveSingleFile(int beginning, int ending, string prefix, string suffix);
        void saveSingleResults();
    public:
        GCSplit(Arguments &arguments);
        void split();
};

#endif // GCSPLIT_H
