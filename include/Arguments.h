#ifndef _ARGUMENTS_
#define _ARGUMENTS_

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

void displayHelp(char *argv[]);
void printVersion(char *argv[]);

class Arguments {
	private:
        bool ready;
		bool help;
		bool version;
		string forward;
		string reverse;
        string single;
		int partitions;
		int numberOfKmers;
        vector<int> bestKmers;
        bool wholeDataset;
        bool ionTorrent;
        int threads;
        string outputDir;
	public:
		Arguments(int argc, char *argv[]);
		bool  getHelp();
		bool  getVersion();
        bool areReady();
		string getForward();
		string getReverse();
        string getSingle();
		int getPartitions();
		int getNumberOfKmers();
        void setBestKmers(vector<int> bestKmers);
        vector<int> getBestKmers();
        int getThreads();
        bool useWholeDataset();
        bool isIonTorrent();
        string getOutputDir();
};

#endif
/* EOF */
