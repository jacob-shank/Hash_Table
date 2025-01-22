//Code written for an assingment in CS 341 at Butler University

#include "HashTableArray.h"

HashTableArray::HashTableArray(char isLinear) : numOccupied_(0), size_(1)
{
	entry_ = new HashEntry[1]; //starts at one, and will get rehashed imediately
	if(isLinear == 'L')
	{
		isLinear_ = true;
	}
	if(isLinear == 'Q')
	{
		isLinear_ = false;
	}
}
HashTableArray::HashTableArray(int size, char isLinear) : size_(size), numOccupied_(0)
{
	entry_ = new HashEntry[size_];
	if(isLinear == 'L')
	{
		isLinear_ = true;
	}
	if(isLinear == 'Q')
	{
		isLinear_ = false;
	}
}
HashTableArray::~HashTableArray()
{
	delete [] entry_;
}

//virtual functions inherited from HashTable
void HashTableArray::insert(int key, int value)
{
	insertHelp(hashFunction(key), value, key, 1);
	numOccupied_++;
	if(loadFactor() >= 0.5)
	{
		reHash();
	}
}
int HashTableArray::search(int key)
{
	int value = 0;
	int startKey = hashFunction(key);
	if(searchHelp(startKey, key, value, startKey, 1))
	{
		return value;
	}
	else
	{
		return -1;
	}
}
void HashTableArray::remove(int key)
{
	int startKey = hashFunction(key);
	int value = 0;
	if(searchHelp(startKey, key, value, startKey, 1))
	{
		numOccupied_--;
	}
	removeHelp(startKey, key, startKey, 1);
}
void HashTableArray::print()
{
	std::cout << "***********************************" << std::endl;
	for(int i = 0; i < size_; i++)
	{
		(entry_[i].getStatus().getInt() == 1) ? std::cout << "[" << i << "](" << entry_[i].getStatus().getString().substr(0,1) << "): " << entry_[i].getKey() /*<< " Key: " << entry_[i].getKey()*/ << std::endl : std::cout << "[" << i << "](" << entry_[i].getStatus().getString().substr(0,1) << "): " << std::endl;
	}
	std::cout << "***********************************" << std::endl;
}


//getters
int HashTableArray::getSize()
{
	return size_;
}

//private functions
int HashTableArray::hashFunction(int key)
{
	return key % size_;
}
void HashTableArray::insertHelp(int reccursivekey, int value, int key, int count)
{
	//recursive key starts as the output of the hash funciton, and recurses accordingly
	
	
	//base case
	if((entry_[reccursivekey].getStatus().getString() == "EMPTY") || (entry_[reccursivekey].getStatus().getString() == "REMOVED"))
	{
		entry_[reccursivekey].setValue(value);
		entry_[reccursivekey].setKey(key);
		entry_[reccursivekey].setStatus("OCCUPIED");
	}
	else //entry_ is occupied
	{
		if(isLinear_)
		{	
			insertHelp(hashFunction(reccursivekey+1),value,key,0);
		}
		else
		{
			insertHelp(hashFunction(key + hashFunction(count*count)),value,key,count+1);
		}
	}
}
bool HashTableArray::searchHelp(int recursiveKey, int key, int & value, int startKey, int count)
{
	if(entry_[recursiveKey].getKey() == key)
	{
		value = entry_[recursiveKey].getValue();
		return true;
		//essentially just returning both a bool and an int
	}
	else if(entry_[recursiveKey].getStatus().getString() == "EMPTY")
	{
		return false;
	}
	else if(recursiveKey == ((startKey - 1) % size_)) //if we're visiting the entry before the starting one
	{
		//if none of the other base cases have been true, then we're done
		return false;
	}
	else
	{
		if(isLinear_)
		{
			//using hashFunction in here just so that the recusiveKey goes back to the beginning of the list
			return searchHelp(hashFunction(recursiveKey + 1), key, value, startKey, 0);
		}
		else
		{
			return searchHelp(hashFunction(key + hashFunction(count*count)), key, value, startKey, count+1);
		}
	}
}
void HashTableArray::removeHelp(int recursiveKey, int key, int startKey, int count)
{
	if(entry_[recursiveKey].getKey() == key)
	{
		entry_[recursiveKey].setStatus("REMOVED");
		//don't need to remove any of the data in entry_[] because by setting its status to removed, it gets ignored
	}
	else if(entry_[recursiveKey].getStatus().getString() == "EMPTY")
	{
		return;
	}
	else if(recursiveKey == ((startKey - 1) % size_)) //if we're visiting the entry before the starting one
	{
		//if none of the other base cases have been true, then we're done
		return;
	}
	else
	{
		if(isLinear_)
		{
			//using hashFunction in here just so that the recusiveKey goes back to the beginning of the list
			return removeHelp(hashFunction(recursiveKey + 1), key, startKey, 0);
		}
		else
		{
			removeHelp(hashFunction(key + hashFunction(count*count)), key, startKey, count+1);
		}
	}
}
void HashTableArray::reHash()
{
	//make bigger hash table, loop through the old one, and insert the nodes into the new one
	char pass = ' ';
	if(isLinear_)
	{
		pass = 'L';
	}
	else
	{
		pass = 'Q';
	}
	
	HashTableArray * newTable = new HashTableArray(size_*2, pass);
	for(int i = 0; i < size_; i++)
	{
		if(entry_[i].getStatus().getString() == "OCCUPIED")
		{
			newTable->insert(entry_[i].getKey(), entry_[i].getValue());
		}
	}
	
	//now delete the old array, and get the new one
	delete [] entry_;
	
	entry_ = newTable->getEntryArray();
	numOccupied_ = newTable->getNumOccupied();
	size_ = newTable->getSize();
	
	newTable->setEntry(nullptr);
	delete newTable;
	
}

double HashTableArray::loadFactor()
{
	return (numOccupied_*1.0)/(size_*1.0);
}

HashEntry * HashTableArray::getEntryArray()
{
	return entry_;
}

int HashTableArray::getNumOccupied()
{
	return numOccupied_;
}

void HashTableArray::setEntry(HashEntry * ptr)
{
	entry_ = ptr;
}