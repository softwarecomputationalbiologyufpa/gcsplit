#ifndef FASTA_H
#define FASTA_H

#include <string>

using namespace std;

class Fasta {
    private:
        string id;
        string sequence;
    public:
        Fasta();
        void setId(string id);
        string getId();
        void setSequence(string sequence);
        string getSequence();
        bool operator < (const Fasta &fasta) const;
};

#endif // FASTA_H
