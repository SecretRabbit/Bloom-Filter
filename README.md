# Bloom-Filter

In this program, I create a bloom filter and analyze performances of pairs of integer hash functions and string hash functions. There is a short report on their performances. 

Bloom filters are data structures that represent sets  and allow the user to query whether a given item is a member of the set or not. They use hash functions and a clever storage mechanism to  represent sets  using very little memory.  The cost of this is the occasional false positive - a Bloom filter may report that an item is in the set when it is not.[bf]

The integer hash functions I use are: Division Hash, Reciprocal Hash and Squreroot Hash.
The string hash functions I use are: Jenkins Hash and Pearson Hash. 

[bf]: https://en.wikipedia.org/wiki/Bloom_filter
