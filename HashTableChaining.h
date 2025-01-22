//Code written for an assingment in CS 341 at Butler University

#include "DoublyLinkedList.h"
#include "HashTable.h"

class HashTableChaining : public HashTable
{
	public:
		HashTableChaining(int size);
		virtual ~HashTableChaining();
		int getSize();
		
		//inherited
		void insert(int key, int value);
		int search(int key);
		void remove(int key);
		void print();
		
	private:
		DoublyLinkedList * entry_;
		int size_;
		
		int hashFunction(int key);
};