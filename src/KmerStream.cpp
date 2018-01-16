#include "KmerStream.h"

KmerStream::KmerStream(string r1, string r2, int threads, string outputdir) {
    this->r1 = r1;
    this->r2 = r2;
    this->threads = threads;
    this->outputdir = outputdir;
    utils.createDir(outputdir);
    utils.createDir(outputdir + "/kmerstream");
    calculateTestedKmers();
    tsvFile = outputdir + "/kmerstream/bestkmers.tsv";
}

void KmerStream::calculateTestedKmers() {
    for(unsigned int i = 15; i <= 127; i += 2) {
        testedKmers.push_back(i);
    }
}

void KmerStream::runCommand() {
    stringstream command;
    cout << "Running KmerStream..." << endl;
    int returnValue;
    command << "KmerStream \\" << endl;
    command << "-k ";
    for(unsigned int i = 0; i < testedKmers.size() - 1; i++) {
        command << testedKmers[i] << ",";
    }
    command << testedKmers[testedKmers.size() - 1] << " \\" << endl;
    command << "-o " << tsvFile << " \\" << endl;
    command << "-t " << threads << " \\" << endl;
    command << "--tsv \\" << endl;
    command << r1 << " \\" << endl;
    command << r2 << endl;
    cout << command.str() << endl;
    returnValue = system(command.str().c_str());
    cout << "Kmerstream returned code " << returnValue << endl << endl;
}

vector<int> KmerStream::getBestK(int kmers) {
    runCommand();
    ifstream fin(tsvFile.c_str());
    vector<int> bestK;
    vector<TSV> kmerstreamOutput;
    string aux;
    int Q, k;
    unsigned long long int F0, f1, F1;
    if(fin.is_open()) {
        for(int i = 0; i < 5; i++) {
            fin >> aux;
        }
        while(fin >> Q) {
            fin >> k; fin >> F0; fin >> f1; fin >> F1;
            TSV tsv;
            tsv.set_k(k); tsv.set_F0(F0);
            kmerstreamOutput.push_back(tsv);
        }
        sort(kmerstreamOutput.begin(), kmerstreamOutput.end());
        for(int i = 0; i < kmers; i++) {
            bestK.push_back(kmerstreamOutput[i].get_k());
        }
    } else {
        cerr << "Error opening file " << tsvFile << endl;
    }
    return bestK;
}
