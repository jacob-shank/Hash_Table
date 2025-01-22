//Code written for an assingment in CS 341 at Butler University

#include "HashTable.h"
#include "HashEntry.h"

class HashTableArray : public HashTable
{
	public:
		//constructors destructors
		HashTableArray(char isLinear);
		HashTableArray(int size, char isLinear);
		virtual ~HashTableArray();
		
		void insert(int key, int value);
		int search(int key);
		void remove(int key);
		void print();
		
		//getters
		int getSize();
		
	private:
		HashEntry * entry_; //points to the head of an array
		int size_;
		int numOccupied_;
		bool isLinear_;
		
		int hashFunction(int key);
		void insertHelp(int reccursivekey, int value, int key, int count);
		bool searchHelp(int recursiveKey, int key, int & value, int startKey, int count);
		void removeHelp(int recursiveKey, int key, int startKey, int count);
		
		void reHash();
		double loadFactor();
		
		HashEntry * getEntryArray();
		int getNumOccupied();
		
		void setEntry(HashEntry *);
		
		
};