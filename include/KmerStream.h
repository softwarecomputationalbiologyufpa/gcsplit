#ifndef KMERSTREAM_H
#define KMERSTREAM_H

#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Arguments.h"
#include "Utils.h"
#include "TSV.h"

using namespace std;

class KmerStream {
    private:
        string forward;
        string reverse;
        string single;
        int threads;
        string outputDir;
        vector<int> testedKmers;
        string tsvFile;
        Utils utils;
        void calculateTestedKmers();
        void runCommand();
    public:
        KmerStream(Arguments &arguments);
        void getBestKmers(Arguments &arguments);
};

#endif // KMERSTREAM_H
