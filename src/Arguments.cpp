#include "Arguments.h"

void displayHelp(char *argv[]) {
    cerr << endl << "GCSplit v1.2" << endl << endl;
    cerr << "A software to partition paired FASTQ files" << endl << endl;
	cerr << "Usage: " << argv[0] << " [options] -o <output_dir> " << endl << endl;
	cerr << "Basic options:" << endl;
	cerr << "    -o/--output <output_dir>    Folder to store all the files generated during the assembly (required)." << endl;
    cerr << "    -p/--partitions <int>       Number of partitions [default: 16]" << endl;
    cerr << "    -w/--whole                  Use whole dataset to merge [default: off]" << endl;
    cerr << "    --iontorrent                This flag is required for IonTorrent data." << endl;
    cerr << "    -h/--help                   Prints this usage message." << endl;
    cerr << "    -v/--version                Prints version info" << endl << endl;
	cerr << "Input data:" << endl;
	cerr << "    -f/--forward <filename>     File with forward paired-end reads." << endl;
	cerr << "    -r/--reverse <filename>     File with reverse paired-end reads." << endl;
    cerr << "    -s/--single <filename>      File with unpaired reads." << endl << endl;
    cerr << "Advanced options:" << endl;
    cerr << "    -t/--threads <int>          Number of threads [default: 4]" << endl;
    cerr << "    -k/--kmers <int>            Number of kmers to run the assembly [default: 3]" << endl;
    cerr << "    -m/--memory <int>           Set memory limit for SPAdes in Gb [default: 250]" << endl;
    cerr << "    --only-assembler            Runs SPAdes on assembly mode only" << endl << endl;
	cerr << "Please, report bugs to: miranda.fmm@gmail.com" << endl;
	cerr << "Software homepage: <https://github.com/mirand863/gcsplit>" << endl << endl;
}

void printVersion(char *argv[]) {
	cerr << endl << "GCSplit v1.2" << endl << endl;
	cerr << "Copyright (C) 2018 Federal University of Para." << endl;
	cerr << "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>." << endl;
	cerr << "This is free software: you are free to change and redistribute it." << endl;
	cerr << "There is NO WARRANTY, to the extent permitted by law." << endl << endl;
	cerr << "Written by Fabio Malcher Miranda." << endl << endl;
}

Arguments::Arguments(int argc, char *argv[]) {
	help = false;
	version = false;
    ready = true;
    single = "";
    forward = "";
    reverse = "";
    partitions = 16;
    numberOfKmers = 3;
    threads = 4;
    wholeDataset = false;
    ionTorrent = false;
    memoryLimit = 250;
    onlyAssembler = false;
    outputDir = "";

	for(int i = 1; i < argc; i++) {
		string argument(argv[i]);
		if(argument == "--help" || argument == "-h") {
			help = true;
			break;
		} else if(argument == "--version" || argument == "-v") {
			version = true;
			break;
		} else if(argument == "--forward" || argument == "-f") {
			forward = argv[i + 1];
			continue;
		} else if (argument == "--reverse" || argument == "-r") {
			reverse = argv[i + 1];
			continue;
		} else if (argument == "--single" || argument == "-s") {
			single = argv[i + 1];
			continue;
		} else if (argument == "--partitions" || argument == "-p") {
			partitions = atoi(argv[i + 1]);
			continue;
		} else if (argument == "--whole" || argument == "-w") {
			wholeDataset = true;
			continue;
		} else if (argument == "--kmers" || argument == "-k") {
			numberOfKmers = atoi(argv[i + 1]);
			continue;
		} else if (argument == "--threads" || argument == "-t") {
			threads = atoi(argv[i + 1]);
			continue;
		} else if (argument == "--output" || argument == "-o") {
			outputDir = argv[i + 1];
			continue;
		} else if (argument == "--iontorrent") {
			ionTorrent = true;
			continue;
        } else if (argument == "--memory" || argument == "-m") {
            memoryLimit = atoi(argv[i + 1]);
            continue;
		} else if (argument == "--only-assembler") {
            onlyAssembler = true;
            continue;
        }
	}
    if(help) {
        displayHelp(argv);
        ready = false;
    } else if(version) {
        printVersion(argv);
        ready = false;
    } else if(outputDir.length() == 0 || (single.length() == 0 && (forward.length() == 0 || reverse.length() == 0))) {
        displayHelp(argv);
        ready = false;
    }
}

bool Arguments::getHelp() {
	return help;
}

bool Arguments::getVersion() {
	return version;
}

bool Arguments::areReady() {
    return ready;
}

string Arguments::getForward() {
    return forward;
}

string Arguments::getReverse() {
    return reverse;
}
string Arguments::getSingle() {
    return single;
}

int Arguments::getPartitions() {
    return partitions;
}

int Arguments::getNumberOfKmers() {
    return numberOfKmers;
}

void Arguments::setBestKmers(vector<int> bestKmers) {
    this->bestKmers = bestKmers;
}

vector<int> Arguments::getBestKmers() {
    return bestKmers;
}

int Arguments::getThreads() {
    return threads;
}

bool Arguments::useWholeDataset() {
    return wholeDataset;
}

bool Arguments::isIonTorrent() {
    return ionTorrent;
}

int Arguments::getMemoryLimit() {
    return memoryLimit;
}

bool Arguments::isOnlyAssembler() {
    return onlyAssembler;
}

string Arguments::getOutputDir() {
    return outputDir;
}

/* EOF */
