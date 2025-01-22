//Code written for an assingment in CS 341 at Butler University


#include "HashTableCuckoo.h"

HashTableCuckoo::HashTableCuckoo(int size) : size_(size), numOccupied_(0)
{
	entry1_ = new HashEntry[size_];
	entry2_ = new HashEntry[size_];
}
HashTableCuckoo::~HashTableCuckoo()
{
	delete [] entry1_;
	delete [] entry2_;
}

void HashTableCuckoo::insert(int key, int value)
{
	//insert into entry1_, if it was occupied, put its old data in entry2_
	
	bool inTable1 = true;
	bool done = false;
	HashEntry pop;
	HashEntry insert = HashEntry(key, value);
	
	pop = insert;
	
	while(!done)
	{
		//always insert pop
		if(inTable1)
		{
			pop = insertTable1(pop);
		}
		if (!inTable1)
		{
			pop = insertTable2(pop);
		}
		if(pop.getStatus().getString() != "OCCUPIED")
		{
			done = true;
		}
		if(pop.getStatus().getString() == "OCCUPIED" && pop.getKey() == insert.getKey())
		{
			//cycle detected
			std::cout << "Cycle found, key displaced: " << pop.getKey() << std::endl;
			reHash(pop);
			done = true;
			break;
		}
		inTable1 = !inTable1;
	}
	numOccupied_++; //used in rehash
}
int HashTableCuckoo::search(int key)
{
	if(entry1_[hashFunction1(key)].getKey() == key)
	{
		return entry1_[hashFunction1(key)].getValue();
	}
	else if(entry2_[hashFunction2(key)].getKey() == key)
	{
		return entry2_[hashFunction2(key)].getValue();
	}
	else
	{
		return -1;
	}
	
}
void HashTableCuckoo::remove(int key)
{
	if(entry1_[hashFunction1(key)].getKey() == key)
	{
		entry1_[hashFunction1(key)].setStatus("EMPTY");
		numOccupied_--;
	}
	else if(entry2_[hashFunction2(key)].getKey() == key)
	{
		entry2_[hashFunction2(key)].setStatus("EMPTY");
		numOccupied_--;
	}
}

void HashTableCuckoo::print()
{
	std::cout << "***********************************" << std::endl;
	for(int i = 0; i < size_; i++)
	{
		(entry1_[i].getStatus().getInt() == 1) ? std::cout << "[" << i << "](" << entry1_[i].getStatus().getString().substr(0,1) << "): " << entry1_[i].getKey() /*<< " Key: " << entry1_[i].getKey()*/ << std::endl : std::cout << "[" << i << "](" << entry1_[i].getStatus().getString().substr(0,1) << "): " << std::endl;
	}
	std::cout << "***********************************" << std::endl;
	std::cout << "***********************************" << std::endl;
	for(int i = 0; i < size_; i++)
	{
		(entry2_[i].getStatus().getInt() == 1) ? std::cout << "[" << i << "](" << entry2_[i].getStatus().getString().substr(0,1) << "): " << entry2_[i].getKey() /*<< " Key: " << entry2_[i].getKey()*/ << std::endl : std::cout << "[" << i << "](" << entry2_[i].getStatus().getString().substr(0,1) << "): " << std::endl;
	}
	std::cout << "***********************************" << std::endl;
}

void HashTableCuckoo::reHash(HashEntry pop)
{
	//make two arrays, one for each table
	HashEntry oldEntry1[size_];
	HashEntry oldEntry2[size_];
	int oldEntry1Length = 0;
	int oldEntry2Length = 0;
	
	
	//now fill both
	for(int i = 0; i < size_; i++)
	{
		if(entry1_[i].getStatus().getString() == "OCCUPIED")
		{
			oldEntry1[oldEntry1Length] = entry1_[i];
			oldEntry1Length++;
		}
	}
	for(int i = 0; i < size_; i++)
	{
		if(entry2_[i].getStatus().getString() == "OCCUPIED")
		{
			oldEntry2[oldEntry2Length] = entry2_[i];
			oldEntry2Length++;
		}
	}
	
	//clear out both array
	delete [] entry1_;
	delete [] entry2_;
	entry1_ = new HashEntry[size_*2];
	entry2_ = new HashEntry[size_*2];
	
	size_ *= 2;
	
	//now insert what was in both arrays, as well as pop
	for(int i = 0; i < oldEntry1Length ; i++)
	{
		insert(oldEntry1[i].getKey(), oldEntry1[i].getValue());
	}
	for(int i = 0; i < oldEntry2Length ; i++)
	{
		insert(oldEntry2[i].getKey(), oldEntry2[i].getValue());
	}
	
	insert(pop.getKey(), pop.getValue());
}


HashEntry HashTableCuckoo::insertTable1(HashEntry insert)
{
	HashEntry pop = entry1_[hashFunction1(insert.getKey())];
	
	//now override what is there
	entry1_[hashFunction1(insert.getKey())] = insert;
	
	return pop;
}
HashEntry HashTableCuckoo::insertTable2(HashEntry insert)
{
	HashEntry pop = entry2_[hashFunction2(insert.getKey())];
	
	//now override what is there
	entry2_[hashFunction2(insert.getKey())] = insert;
	
	return pop;
}

int HashTableCuckoo::hashFunction1(int key)
{
	return key % size_;
}
int HashTableCuckoo::hashFunction2(int key)
{
	return (key/size_) % size_;
}