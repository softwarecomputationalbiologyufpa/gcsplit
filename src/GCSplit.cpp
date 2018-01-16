#include "GCSplit.h"

GCSplit::GCSplit(string r1, string r2, int threads, string outputdir) {
    this->r1 = r1;
    this->r2 = r2;
    this->threads = threads;
    omp_set_dynamic(0);
    omp_set_num_threads(threads);
    this->outputdir = outputdir;
    utils.createDir(outputdir + "/gcsplit");
    basename = outputdir + "/gcsplit/slice";
}

void GCSplit::load(string file, vector<Fastq> &sequences) {
    string id, sequence, placeholder, quality;
    ifstream fin(file.c_str());

    if(fin.is_open()) {
        while(getline(fin, id)) {
            getline(fin, sequence);
            getline(fin, placeholder);
            getline(fin, quality);
            Fastq fastq;
            fastq.setId(id);
            fastq.setSequence(sequence);
            fastq.setPlaceholder(placeholder);
            fastq.setQuality(quality);
            sequences.push_back(fastq);
        }
        fin.close();
    } else {
        cout << "Error opening fastq file " << file <<  endl;
    }
}

void GCSplit::loadFiles() {
    cout << "Reading fastq files... ";
    load(r1, left);
    load(r1, right);
    cout << "OK" << endl;
}

void GCSplit::computeGCContent() {
    cout << "Computing GC content... ";
    #pragma omp parallel for
    for(unsigned int i = 0; i < left.size(); i++) {
        left[i].computeGCContent();
        left[i].setPair(right[i]);
    }
    cout << "OK" << endl;
}

void GCSplit::sortSequences() {
    cout << "Sorting sequences by their GC content... ";
    __gnu_parallel::sort(left.begin(), left.end());
    cout << "OK" << endl;
}

int GCSplit::computeHalfIndex(int vectorSize) {
    int half;

    if(vectorSize % 2 == 0) {
        half = (int)((vectorSize - 1) / 2);
    } else {
        half = vectorSize / 2;
    }
    return half;
}

void GCSplit::computeQuartiles() {
    median = computeHalfIndex(left.size());
    firstQuartile = computeHalfIndex(median);
    thirdQuartile = median + firstQuartile + 1;
}

void GCSplit::saveFile(int beginning, int ending, string prefix, string suffix) {
    ofstream pair1(string(prefix + "_r1" + suffix).c_str());
    ofstream pair2(string(prefix + "_r2" + suffix).c_str());
    for(int i = beginning; i <= ending; i++) {
        pair1 << left[i];
        pair2 << *(left[i].getPair());
    }
    pair1.close();
    pair2.close();
}


void GCSplit::saveResults() {
    cout << "Saving results... ";
    saveFile(0, firstQuartile, basename + string("_1"), string(".fastq"));
    saveFile(firstQuartile + 1, median, basename + string("_2"), string(".fastq"));
    saveFile(median + 1, thirdQuartile, basename + string("_3"), string(".fastq"));
    saveFile(thirdQuartile + 1, left.size() - 1, basename + string("_4"), string(".fastq"));
    cout << "OK" << endl;
}

void GCSplit::split() {
    loadFiles();
    computeGCContent();
    sortSequences();
    computeQuartiles();
    saveResults();
}
