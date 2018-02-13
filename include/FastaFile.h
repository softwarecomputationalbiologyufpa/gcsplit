#ifndef FASTAFILE_H
#define FASTAFILE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <parallel/algorithm>
#include "Fasta.h"

using namespace std;

class FastaFile {
    private:
        vector<Fasta> sequences;
        unsigned long long int basePairs;
        unsigned long long int n50;
    public:
        FastaFile();
        void load(string file);
        void sortSequences();
        void computeN50();
        unsigned long long int getN50();
};

#endif // FASTAFILE_H
