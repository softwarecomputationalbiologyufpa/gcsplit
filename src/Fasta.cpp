#include "Fasta.h"

Fasta::Fasta() {
    //ctor
}

void Fasta::setId(string id) {
    this->id = id;
}

string Fasta::getId() {
    return id;
}

void Fasta::setSequence(string sequence) {
    this->sequence = sequence;
}

string Fasta::getSequence() {
    return sequence;
}

bool Fasta::operator < (const Fasta &fasta) const {
    return sequence.length() > fasta.sequence.length();
}
