#include "TSV.h"

TSV::TSV() {
    //ctor
}

void TSV::set_k(int k) {
    this->k = k;
}

int TSV::get_k() {
    return k;
}

void TSV::set_F0(unsigned long long int F0) {
    this->F0 = F0;
}

unsigned long long int TSV::get_F0() {
    return F0;
}

bool TSV::operator < (const TSV &tsv) const {
    return F0 > tsv.F0;
}
