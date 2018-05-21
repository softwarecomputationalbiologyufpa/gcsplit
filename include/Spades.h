#ifndef SPADES_H
#define SPADES_H

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "Arguments.h"
#include "Utils.h"

using namespace std;

#include "FastaFile.h"

class Spades {
    private:
        string forward;
        string reverse;
        string single;
        bool ionTorrent;
        bool wholeDataset;
        int threads;
        int partitions;
        vector<int> kmers;
        bool skipkmerstream;
        string selectedKmers;
        string gcsplitInput;
        string spadesInput;
        string outputdir;
        Utils utils;
        string outputFile;
        vector<FastaFile> slices;
        void assembleSlices();
        void mergeAssemblies();
        void mergeAssembliesWithWholeDataset();
    public:
        Spades(Arguments &arguments);
        void run();
};

#endif // SPADES_H
