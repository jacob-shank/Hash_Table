//Code written for an assingment in CS 341 at Butler University

#include "HashTableChaining.h"


//constructors and destructors
HashTableChaining::HashTableChaining(int size) : size_(size)
{
	entry_ = new DoublyLinkedList[size_];
}
HashTableChaining::~HashTableChaining()
{
	delete [] entry_;
}

//inherited functions
void HashTableChaining::insert(int key, int value)
{
	entry_[hashFunction(key)].insert(HashEntry(key,value));
}
int HashTableChaining::search(int key)
{
	HashEntry entry = HashEntry();
	if(entry_[hashFunction(key)].search(key, entry))
	{
		return entry.getValue();
	}
	else
	{
		//std::cout << "Not Valid Key" << std::endl;
		return -1;
	}
}
void HashTableChaining::remove(int key)
{
	entry_[hashFunction(key)].removeNode(key);
}
void HashTableChaining::print()
{
	std::cout << "***********************************" << std::endl;
	for(int i = 0; i < size_; i++)
	{
		std::cout << "[" << i << "]";
		entry_[i].printList();
	}
	std::cout << "***********************************" << std::endl;
}


//private functions
int HashTableChaining::hashFunction(int key)
{
	return key % size_;
}