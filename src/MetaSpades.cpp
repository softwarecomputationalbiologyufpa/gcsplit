#include "MetaSpades.h"

MetaSpades::MetaSpades(int threads, int partitions, vector<int> kmers, string outputdir) {
    this->threads = threads;
    this->partitions = partitions;
    this->kmers = kmers;
    this->outputdir = outputdir;
    gcsplitInput = outputdir + "/gcsplit/slice_";
    metaspadesInput = outputdir + "/metaspades/slice_";
    utils.createDir(outputdir + "/metaspades");
}

void MetaSpades::assembleSlices() {
    for(int i = 1; i <= partitions; i++) {
        stringstream command;
        cout << "Running MetaSpades..." << endl;
        int returnValue;
        command << "metaspades.py \\" << endl;
        command << "-1 " << gcsplitInput << i << "_r1.fastq \\" << endl;
        command << "-2 " << gcsplitInput << i << "_r2.fastq \\" << endl;
        command << "-t " << threads << " \\" << endl;
        command << "-k ";
        for(unsigned int j = 0; j < kmers.size() - 1; j++) {
            command << kmers[j] << ",";
        }
        command << kmers[kmers.size() - 1] << " \\" << endl;
        command << "-o " << outputdir << "/metaspades/slice_" << i << endl;
        cout << command.str() << endl;
        returnValue = system(command.str().c_str());
        cout << "MetaSpades return code " << returnValue << endl;
    }
}

void MetaSpades::mergeAssemblies() {
    for(int i = 0; i < partitions; i++) {
        FastaFile slice;
        stringstream input;
        input << outputdir << "/metaspades/slice_" << (i + 1) << "/contigs.fasta";
        slices.push_back(slice);
        slices[i].load(input.str());
        slices[i].sortSequences();
        slices[i].computeN50();
    }

    unsigned long long int maxN50 = slices[0].getN50();
    for(int i = 1; i < partitions; i++) {
        maxN50 = max(maxN50, slices[i].getN50());
    }

    vector<int> smallerN50;
    int largestN50 = 0;
    for(int i = 0; i < partitions; i++) {
        if(slices[i].getN50() == maxN50) {
            largestN50 = i + 1;
        } else {
            smallerN50.push_back(i + 1);
        }
    }

    stringstream command;
    cout << "Running Spades..." << endl;
    int returnValue;
    command << "spades.py \\" << endl;
    command << "-1 " << gcsplitInput << largestN50 << "_r1.fastq \\" << endl;
    command << "-2 " << gcsplitInput << largestN50 << "_r2.fastq \\" << endl;
    for(int i = 1; i < partitions; i++) {
        command << "--s1 " << metaspadesInput << smallerN50[i - 1] << "/contigs.fasta \\" << endl;
    }
    command << "--trusted-contigs " << metaspadesInput << largestN50 << "/contigs.fasta \\" << endl;
    command << "--only-assembler \\" << endl;
    command << "-t " << threads << " \\" << endl;
    command << "-k ";
    for(unsigned int j = 0; j < kmers.size() - 1; j++) {
        command << kmers[j] << ",";
    }
    command << kmers[kmers.size() - 1] << " \\" << endl;
    command << "-o " << outputdir << "/metaspades/merge" << endl;
    cout << command.str() << endl;
    returnValue = system(command.str().c_str());
    cout << "MetaSpades return code " << returnValue << endl;
}

void MetaSpades::run() {
    assembleSlices();
    mergeAssemblies();
}
