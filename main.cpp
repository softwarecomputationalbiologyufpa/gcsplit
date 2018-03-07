#include <iostream>
#include <vector>
#include <string>
#include "Arguments.h"
#include "KmerStream.h"
#include "GCSplit.h"
#include "MetaSpades.h"

using namespace std;

int main(int argc, char *argv[]) {
    Arguments arguments(argc, argv);

    if(arguments.areReady()) {
        KmerStream kmerStream(arguments);
        kmerStream.getBestKmers(arguments);
        GCSplit gcsplit(arguments);
        gcsplit.split();
        MetaSpades metaspades(arguments);
        metaspades.run();
    }

    return 0;
}
