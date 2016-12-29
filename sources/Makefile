
article: Article.o main.o
	g++ -o Article main.o Article.o 

Article.o: Article.cpp Article.h
	g++ -o Article.o -c Article.cpp

main.o: main.cpp Article.h
	g++ -o main.o -c main.cpp
 
clean: 
	rm *.o
	rm Article