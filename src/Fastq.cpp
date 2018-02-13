#include "Fastq.h"

Fastq::Fastq() {
    id = "";
    sequence = "";
    placeholder = "";
    quality = "";
    gc = 0.0;
}

void Fastq::setId(string id) {
    this->id = id;
}

string Fastq::getId() {
    return id;
}

void Fastq::setSequence(string sequence) {
    this->sequence = sequence;
}

string Fastq::getSequence() {
    return sequence;
}

void Fastq::setPlaceholder(string placeholder) {
    this->placeholder = placeholder;
}

string Fastq::getPlaceholder() {
    return placeholder;
}

void Fastq::setQuality(string quality) {
    this->quality = quality;
}

string Fastq::getQuality() {
    return quality;
}

void Fastq::computeGCContent() {
    gc = 0.0;
    for(unsigned int i = 0; i < sequence.length(); i++) {
        if(sequence[i] == 'C' || sequence[i] == 'G') {
            gc++;
        }
    }
    gc = gc * 100.0 / sequence.length();
}

double Fastq::getGCContent() {
    return gc;
}

void Fastq::setPair(Fastq &pair) {
    this->pair = &pair;
}

Fastq* Fastq::getPair() {
    return pair;
}

bool Fastq::operator < (const Fastq &fastq) const {
    return gc < fastq.gc;
}

ostream &operator << (ostream &stream, const Fastq &fastq) {
    stream << fastq.id << "\n";
    stream << fastq.sequence << "\n";
    stream << "+" << fastq.gc << "\n";
    stream << fastq.quality << "\n";
    return stream;
}
