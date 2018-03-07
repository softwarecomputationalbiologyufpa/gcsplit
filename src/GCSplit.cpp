#include "GCSplit.h"

GCSplit::GCSplit(Arguments &arguments) {
    this->forward = arguments.getForward();
    this->reverse = arguments.getReverse();
    this->single = arguments.getSingle();
    this->partitions = arguments.getPartitions();
    this->threads = arguments.getThreads();
    this->outputDir = arguments.getOutputDir();
    omp_set_dynamic(0);
    omp_set_num_threads(threads);
    utils.createDir(outputDir + "/gcsplit");
    basename = outputDir + "/gcsplit/slice";
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
        cerr << "Error opening fastq file " << file <<  endl;
    }
}

void GCSplit::loadFiles() {
    if(forward.length() > 0 && reverse.length() > 0) {
        cerr << "Reading fastq files... ";
        load(forward, left);
        load(reverse, right);
        cerr << "OK" << endl;
        cerr << left.size() << " sequences loaded" << endl;
    }
    if(single.length() > 0) {
        cerr << "Reading fastq file... ";
        load(single, sing);
        cerr << "OK" << endl;
        cerr << sing.size() << " sequences loaded" << endl;
    }
}

void GCSplit::computeGCContent() {
    cerr << "Computing GC content... ";
    #pragma omp parallel for
    for(unsigned int i = 0; i < left.size(); i++) {
        left[i].computeGCContent();
        left[i].setPair(right[i]);
    }
    for(unsigned int i = 0; i < sing.size(); i++) {
        sing[i].computeGCContent();
    }
    cerr << "OK" << endl;
}

void GCSplit::sortSequences() {
    cerr << "Sorting sequences by their GC content... ";
    __gnu_parallel::sort(left.begin(), left.end());
    __gnu_parallel::sort(sing.begin(), sing.end());
    cerr << "OK" << endl;
}

void GCSplit::savePairedFiles(int beginning, int ending, string prefix, string suffix) {
    ofstream r1(string(prefix + "_r1" + suffix).c_str());
    ofstream r2(string(prefix + "_r2" + suffix).c_str());
    for(int i = beginning; i <= ending; i++) {
        r1 << left[i];
        r2 << *(left[i].getPair());
    }
    r1.close();
    r2.close();
}

void GCSplit::savePairedResults() {
    cerr << "Saving paired results... " << endl;
    int length = left.size() / partitions;
    int remaining = left.size() % partitions;
    int beginning = 0;
    int ending = 0;
    int partitionNumber = 1;
    for(int i = 0; i < min(partitions, (int)left.size()); ++i) {
        ending += (remaining > 0) ? (length + !!(remaining--)) : length;
        cerr << "partitioning from " << beginning << " to " << (ending - 1) << endl;
        stringstream pNumber;
        pNumber << partitionNumber;
        savePairedFiles(beginning, ending - 1, basename + string("_") + pNumber.str(), string(".fastq"));
        beginning = ending;
        partitionNumber++;
    }
    cerr << "Finished!" << endl;
}

void GCSplit::saveSingleFile(int beginning, int ending, string prefix, string suffix) {
    ofstream r1(string(prefix + suffix).c_str());
    for(int i = beginning; i <= ending; i++) {
        r1 << sing[i];
    }
    r1.close();
}

void GCSplit::saveSingleResults() {
    cerr << "Saving single results... " << endl;
    int length = sing.size() / partitions;
    int remaining = sing.size() % partitions;
    int beginning = 0;
    int ending = 0;
    int partitionNumber = 1;
    for(int i = 0; i < min(partitions, (int)sing.size()); ++i) {
        ending += (remaining > 0) ? (length + !!(remaining--)) : length;
        cerr << "partitioning from " << beginning << " to " << (ending - 1) << endl;
        stringstream pNumber;
        pNumber << partitionNumber;
        saveSingleFile(beginning, ending - 1, basename + string("_") + pNumber.str(), string(".fastq"));
        beginning = ending;
        partitionNumber++;
    }
    cerr << "Finished!" << endl;
}

void GCSplit::split() {
    loadFiles();
    computeGCContent();
    sortSequences();
    if(forward.length() > 0 && reverse.length() > 0) {
        savePairedResults();
    }
    if(single.length() > 0) {
        saveSingleResults();
    }
}
