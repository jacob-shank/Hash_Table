A6.exe: Status.o Node.o LinkedNode.o LinkedList.o DoublyLinkedList.o HashEntry.o HashTableArray.o HashTableCuckoo.o HashTableChaining.o driver.o
	g++ Status.o Node.o LinkedNode.o LinkedList.o DoublyLinkedList.o HashEntry.o HashTableArray.o HashTableCuckoo.o HashTableChaining.o driver.o -o A6.exe

Status.o: Status.cpp
	g++ -c Status.cpp -o Status.o

Node.o: Node.cpp
	g++ -c Node.cpp -o Node.o

LinkedNode.o: LinkedNode.cpp
	g++ -c LinkedNode.cpp -o LinkedNode.o

LinkedList.o: LinkedList.cpp
	g++ -c LinkedList.cpp -o LinkedList.o

DoublyLinkedList.o: DoublyLinkedList.cpp
	g++ -c DoublyLinkedList.cpp -o DoublyLinkedList.o

HashEntry.o: HashEntry.cpp
	g++ -c HashEntry.cpp -o HashEntry.o

HashTableArray.o: HashTableArray.cpp
	g++ -c HashTableArray.cpp -o HashTableArray.o

HashTableCuckoo.o: HashTableCuckoo.cpp
	g++ -c HashTableCuckoo.cpp -o HashTableCuckoo.o

HashTableChaining.o: HashTableChaining.cpp
	g++ -c HashTableChaining.cpp -o HashTableChaining.o

driver.o: driver.cpp
	g++ -c driver.cpp -o driver.o


clean:
	rm *.o *.exe

run:
	clear
	make
	A6.exe

runv:
	clear
	make
	valgrind --log-file="valgrind.txt" --leak-check=full -s A6.exe