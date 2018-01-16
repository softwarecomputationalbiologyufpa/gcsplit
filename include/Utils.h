#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

using namespace std;

class Utils {
    private:
        struct stat info;
    public:
        Utils();
        void createDir(string path);
};

#endif // UTILS_H
