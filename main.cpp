/* main.cpp Console_chat */

#include "Chat.h"

#define PORT 7777 // Будем использовать этот номер порта

struct sockaddr_in serveraddress, client;
socklen_t length;
int sockert_file_descriptor, bind_status, connection_status;

int main()
{
    Chat chat;
    // Создадим сокет
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockert_file_descriptor == -1) {
        std::cout << "Socket creation failed!" << '\n';
        exit(1);
    }
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим номер порта для связи
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress,
        sizeof(serveraddress));
    if (bind_status == -1) {
        std::cout << "Socket binding failed!" << '\n';
        exit(1);
    }
    // Поставим сервер на прием данных 
    connection_status = listen(sockert_file_descriptor, 5);
    if (connection_status == -1) {
        std::cout << "Socket is unable to listen for new connections!" << '\n';
        exit(1);
    }
    else {
        std::cout << "Server in progress" << '\n';
    }
    length = sizeof(client);
    chat.connection = accept(sockert_file_descriptor, (struct sockaddr*)&client, &length);
    if (chat.connection == -1) {
        std::cout << "Server is unable to accept the data from client!" << '\n';
        exit(1);
    }
    std::string str;
    while (true)
    {
        str += "\nEnter 1 to enter the chat \nEnter 2 to register in the chat \nEnter 3 to exit the program \n";
        chat.socketWrite(str.c_str());
        str.clear();
        char mode = chat.socketRead()[0];
        try
        {
            switch (mode)
            {
            case '1':   //Entering the chat
                chat.logIn();
                break;
            case '2':   //New User Registration
                chat.checkIn();
                break;
            case '3':   //Exiting the program
                chat.socketWrite("Goodbye!");
                // закрываем сокет, завершаем соединение
                close(sockert_file_descriptor);
                return 0;
            default:
                throw "Wrong enter, please re-enter!";
            }
        }
        catch (const char* exception)
        {
            str = "Error: ";
            str += exception;
            str += '\n';
        }
    }
}