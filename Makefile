output.exe: bst_generic.o queue.o linked_list.o 	
	gcc -g bst_generic.o queue.o linked_list.o -o output.exe -std=c99

bst_generic.o: bst_generic.c
	gcc -g -c bst_generic.c -o bst_generic.o -std=c99

queue.o: queue.c 
	gcc -g -c queue.c -o queue.o -std=c99

linked_list.o: linked_list.c
	gcc -g -c linked_list.c -o linked_list.o -std=c99

clean:
	rm  *.o
