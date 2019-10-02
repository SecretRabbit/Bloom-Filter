#include "BloomFilter.h"

BloomFilter::BloomFilter(int k, int m, std::string strln, std::string intfn){
    this -> k = k;
    this -> m = m;

    //Judge which string hash function to use
    if(strln == "jenkins")
    {this -> strfn = new JenkinsHash();}
    else if(strln == "pearson")
    {this -> strfn = new PearsonHash();}


    //Judge which integer hash function to use
    this -> intfns = new IntegerHash*[k];
    if(intfn == "division"){
        for(int i = 0; i < this -> k; i++){
            intfns[i] = new DivisionHash(i, m);
        }
    }
    else if( intfn == "reciprocal"){
        for(int i = 0; i < this -> k; i++){
            intfns[i] = new ReciprocalHash(i, m);
        }
    }
    else if(intfn == "squareroot"){
        for(int i = 0; i < this -> k; i++){
            intfns[i] = new SquareRootHash(i, m);
        }
    }
    //number of numbers in bits
    int n = m/64+1;

    bits = new uint64_t[n];
    for(int i = 0; i < n; i++){
        bits[i] = uint64_t(0);
    }
}



BloomFilter::~BloomFilter(){
    delete strfn;
    for(int i = 0; i < k; i++){
        delete intfns[i];
    }
    delete [] intfns;
    delete [] bits;
}

void BloomFilter::insert(const std::string& value){
    /*uint64_t t = strfn -> hash(value);
    for(int i = 0; i < k; i++){
        uint64_t h = intfns[i] -> hash(t);
        //switch 0 on position i to 1
        //poisition is in bits[n]
        int n = h / 64;
        //position is at digit s in bits[n]
        int s = h % 64;
        uint64_t one = 1;
        bits[n] |= (one << s);
    }*/
    /*uint64_t stringHashValue = strfn -> hash(value);
    for(int i = 0; i < k; i++){
        uint64_t intHash = intfns[i]-> hash(stringHashValue);
        uint64_t index = (intHash / 64);
        int position = intHash % 64;
        bits[index] |= (uint64_t(1) << position);
    }*/
    uint64_t t = strfn -> hash(value);
    for(int i = 0; i < k; i++){
        uint64_t h = intfns[i] -> hash(t);
        int block = h / 64;
        int bit = h % 64;
        uint64_t one = 1;
        uint64_t ins = (one << bit);
        bits[block] |= ins;
    }

}


bool BloomFilter::lookup(const std::string& value) const{
    uint64_t t = strfn -> hash(value);
    for(int i = 0; i < k; i++){
        uint64_t h = intfns[i] -> hash(t);
        int block = h / 64;
        int bit = h % 64;
        uint64_t temp = bits[block];
        temp >>= bit;
        uint64_t j = 1;
        if((temp & j) == 0)
            return false;
    }
    return true;
}