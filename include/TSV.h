#ifndef TSV_H
#define TSV_H


class TSV {
    private:
        int k;
        unsigned long long int F0;
    public:
        TSV();
        void set_k(int k);
        int get_k();
        void set_F0(unsigned long long int F0);
        unsigned long long int get_F0();
        bool operator < (const TSV &tsv) const;
};

#endif // TSV_H
