//Code written for an assingment in CS 341 at Butler University

#include "HashTable.h"
#include "HashEntry.h"

class HashTableCuckoo : public HashTable
{
	public:
		HashTableCuckoo(int size);
		~HashTableCuckoo();
		
		void insert(int key, int value);
		int search(int key);
		void remove(int key);
		void print();
		
		
	private:
		HashEntry * entry1_;
		HashEntry * entry2_;
		int size_;
		int numOccupied_;
		
		void reHash(HashEntry pop);
		
		HashEntry insertTable1(HashEntry);
		HashEntry insertTable2(HashEntry);
		int hashFunction1(int key);
		int hashFunction2(int key);
		
};