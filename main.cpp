#include <iostream>
#include <vector>
#include <string>
#include "Arguments.h"
#include "KmerStream.h"
#include "GCSplit.h"
#include "MetaSpades.h"
#include "Spades.h"

using namespace std;

int main(int argc, char *argv[]) {
    Arguments arguments(argc, argv);

    if(arguments.areReady()) {
		if(!arguments.skipKmerStream()) {
			KmerStream kmerStream(arguments);
			kmerStream.getBestKmers(arguments);
		}
        GCSplit gcsplit(arguments);
        gcsplit.split();
        if(arguments.isMeta()) {
			cout << "run metaspades" << endl;
			MetaSpades metaspades(arguments);
			metaspades.run();
		} else {
			Spades spades(arguments);
			spades.run();
		}
    }

    return 0;
}
