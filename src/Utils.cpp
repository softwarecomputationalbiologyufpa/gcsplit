#include "Utils.h"

Utils::Utils() {
    //ctor
}

void Utils::createDir(string path) {
    if(stat(path.c_str(), &info) != 0) {
        // create new dir
        if(mkdir(path.c_str(), 0777) == -1) {
            cerr << "Error creating output dir " << path << endl;
        }
    } else if(info.st_mode & S_IFDIR) {
        // dir already exists
//        cerr << path << " is a directory" << endl;
    } else {
        // it is a file
//        cerr << path << " is no directory" << endl;
    }
}
