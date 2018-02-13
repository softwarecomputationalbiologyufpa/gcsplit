#ifndef METASPADES_H
#define METASPADES_H

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "Utils.h"

using namespace std;

#include "FastaFile.h"

class MetaSpades {
    private:
        string r1;
        string r2;
        int threads;
        int partitions;
        vector<int> kmers;
        string gcsplitInput;
        string metaspadesInput;
        string outputdir;
        Utils utils;
        string outputFile;
        vector<FastaFile> slices;
        void assembleSlices();
        void mergeAssemblies();
    public:
        MetaSpades(int threads, int partitions, vector<int> kmers, string outputdir);
        void run();
};

#endif // METASPADES_H
