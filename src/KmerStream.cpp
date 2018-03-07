#include "KmerStream.h"

KmerStream::KmerStream(Arguments &arguments) {
    this->forward = arguments.getForward();
    this->reverse = arguments.getReverse();
    this->single = arguments.getSingle();
    this->threads = arguments.getThreads();
    this->outputDir = arguments.getOutputDir();
    utils.createDir(outputDir);
    utils.createDir(outputDir + "/kmerstream");
    calculateTestedKmers();
    tsvFile = outputDir + "/kmerstream/bestkmers.tsv";
}

void KmerStream::calculateTestedKmers() {
    for(unsigned int i = 15; i <= 127; i += 2) {
        testedKmers.push_back(i);
    }
}

void KmerStream::runCommand() {
    stringstream command;
    cerr << "Running KmerStream..." << endl;
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
    if(forward.length() > 0 && reverse.length() > 0) {
        command << forward << " \\" << endl;
        command << reverse << " \\" << endl;
    }
    if(single.length() > 0) {
        command << single << " \\" << endl;
    }
    cerr << command.str() << endl;
    returnValue = system(command.str().c_str());
    cerr << "Kmerstream returned code " << returnValue << endl << endl;
}

void KmerStream::getBestKmers(Arguments &arguments) {
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
        cerr << "Best kmers: ";
        for(int i = 0; i < arguments.getNumberOfKmers(); i++) {
            bestK.push_back(kmerstreamOutput[i].get_k());
            cerr << kmerstreamOutput[i].get_k() << ", ";
        }
        cerr << endl;
        arguments.setBestKmers(bestK);
    } else {
        cerr << "Error opening file " << tsvFile << endl;
    }
}
