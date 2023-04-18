#Makefile for Project of chat

chat: main.o Chat.o User.o Message.o
	g++ main.o Chat.o User.o Message.o -o chat

main.o: main.cpp
	g++ -c main.cpp

Chat.o: Chat.cpp
	g++ -c Chat.cpp

User.o: User.cpp
	g++ -c User.cpp

Message.o: Message.cpp
	g++ -c Message.cpp

clean:
	rm -rf *.o *.a chat

