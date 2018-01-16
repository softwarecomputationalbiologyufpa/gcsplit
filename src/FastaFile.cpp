#include "FastaFile.h"

FastaFile::FastaFile() {
    basePairs = 0;
}

void FastaFile::load(string file) {
    ifstream fin(file.c_str());
    if(fin.is_open()) {
        string line, id, tempid, sequence;
        while(getline(fin, line) && line[0] == '#') {
            // skip
        }
        while(line.length() > 0) {
            if(line[0] == '>') {
                if(sequence.length() > 0) {
                    Fasta seq;
                    seq.setId(id.substr(1, id.length() - 1));
                    seq.setSequence(sequence);
                    sequences.push_back(seq);
                    basePairs += sequence.length();
                    sequence = "";
                }
                id = line;
            } else {
                sequence += line;
            }
            getline(fin, line);
        }
        Fasta seq;
        seq.setId(id.substr(1, id.length() - 1));
        seq.setSequence(sequence);
        sequences.push_back(seq);
        basePairs += sequence.length();
    } else {
        cerr << "Error opening file " << file << endl;
    }
}

void FastaFile::sortSequences() {
    __gnu_parallel::sort(sequences.begin(), sequences.end());
}

void FastaFile::computeN50() {
    unsigned long long int sum = 0;
    unsigned long long int half = basePairs / 2;
    for(unsigned int i = 0; i < sequences.size(); i++) {
        sum += sequences[i].getSequence().length();
        n50 = sequences[i].getSequence().length();
        if(sum >= half) {
            break;
        }
    }
}

unsigned long long int FastaFile::getN50() {
    return n50;
}
