//Code written for an assingment in CS 341 at Butler University

#include <fstream>
#include "HashTableArray.h"
#include "HashTableChaining.h"
#include "HashTableCuckoo.h"

void useFile(std::string fileName, HashTable * table);
void linear(int size);
void quadratic(int size);
void chaining(int size);
void cuckoo(int size);
void funcionalityLoop(HashTable * table);

int main()
{
	char probingType = ' ';
	
	do
	{
		do
		{
			//ask type of probing
			std::cout << "\nSelect Hash Table Type:\n\n1) Linear Probing\n2) Quadratic Probing\n3) Seperate Chaining\n4) Cuckoo Hashing\n5) Quit Program\n\nEnter Choice: ";
			std::cin >> probingType;
			
			
			if((probingType != '1') && (probingType != '2') && (probingType != '3') && (probingType != '4') && (probingType != '5'))
			{
				std::cout << "\nInvalid Input." << std::endl;
			}
		}
		while((probingType != '1') && (probingType != '2') && (probingType != '3') && (probingType != '4') && (probingType != '5'));
		
		int size = 0;
		if(probingType != '5')
		{
			do
			{
				std::cout << "\nEnter Hash Table Size: ";
				std::cin >> size;
				
				if(size <= 0)
				{
					std::cout << "\nEnter a positive integer." << std::endl;
				}
				
			}while (size <= 0);
		}
		
		//now probing type is valid
		switch(probingType)
		{
			case '1':
			{
				linear(size);
				break;
			}
			case '2':
			{
				quadratic(size);
				break;
			}
			case '3':
			{
				chaining(size);
				break;
			}
			case '4':
			{
				cuckoo(size);
				break;
			}
		}
		
		
	} while (probingType != '5');
	
	return 0;
}

void useFile(std::string fileName, HashTable * table)
{
	std::ifstream dataIn(fileName);
	int currentKey(0), currentValue(0);
	
	while(dataIn >> currentKey >> currentValue)
	{
		table->insert(currentKey, currentValue);
	}
}
void linear(int size)
{
	HashTableArray * table = new HashTableArray(size, 'L');
	
	useFile("data-3.txt", table);
	
	funcionalityLoop(table);
}
void quadratic(int size)
{
	HashTableArray * table = new HashTableArray(size, 'Q');
	
	useFile("data-3.txt", table);
	
	funcionalityLoop(table);
}
void chaining(int size)
{
	HashTableChaining * table = new HashTableChaining(size);
	
	useFile("data-3.txt", table);
	
	funcionalityLoop(table);
}
void cuckoo(int size)
{
	HashTableCuckoo * table = new HashTableCuckoo(size);
	
	useFile("data-3.txt", table);
	
	funcionalityLoop(table);
}
void funcionalityLoop(HashTable * table)
{
	char action = ' ';
	do
	{
		std::cout << "\n\n1) Search For Entry\n2) Remove Entry\n3) Print Hash Table\n4) Return to Main Menu\n\nEnter Choice: ";
		std::cin >> action;
		
		switch(action)
		{
			case '1':
			{
				int key = 0;
				int result = 0;
				std::cout << "\nEnter key for which to search: ";
				std::cin >> key;
				result = table->search(key);
				if(result >= 0)
				{
					std::cout << "\nKey: " << key << " Value: " << result << std::endl;

				}
				else
				{
					std::cout << "Invalide Key." << std::endl;
				}
				break;
			}
			case '2':
			{
				int key = 0;
				std::cout << "\nEnter key for removal: ";
				std::cin >> key;
				table->remove(key);
				std::cout << "Entry Removed" << std::endl;
				break;
			}
			case '3':
			{
				table->print();
				break;
			}
		}
		
		
	}while (action != '4');
	
	delete table;
}