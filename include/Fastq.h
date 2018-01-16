#ifndef FASTQ_H
#define FASTQ_H

#include <iostream>
#include <string>

using namespace std;

class Fastq {
    private:
        string id;
        string sequence;
        string placeholder;
        string quality;
        double gc;
        Fastq *pair;
    public:
        Fastq();
        void setId(string id);
        string getId();
        void setSequence(string sequence);
        string getSequence();
        void setPlaceholder(string placeholder);
        string getPlaceholder();
        void setQuality(string quality);
        string getQuality();
        void computeGCContent();
        double getGCContent();
        void setPair(Fastq &pair);
        Fastq* getPair();
        bool operator < (const Fastq &fastq) const;
        friend ostream &operator << (ostream &stream, const Fastq &fastq);
};

#endif // FASTQ_H
