/* client.cpp Console_chat */

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MESSAGE_LENGTH 1024 // ������������ ������ ������ ��� ������
#define PORT 7777 // ����� ������������ ���� ����� �����

int socket_file_descriptor, connection;
struct sockaddr_in serveraddress, client;
char message[MESSAGE_LENGTH];
int main() {
    // �������� �����
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        std::cout << "Creation of Socket failed!" << '\n';
        exit(1);
    }
    // ��������� ����� �������
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // ������� ����� �����
    serveraddress.sin_port = htons(PORT);
    // ���������� IPv4
    serveraddress.sin_family = AF_INET;
    // ��������� ���������� � ��������
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (connection == -1) {
        std::cout << "Connection with the server failed!" << '\n';
        exit(1);
    }
    // �������������� � ��������
    while (true) 
    {
        // ���� ��������� �� �������
        read(socket_file_descriptor, message, sizeof(message));
        std::cout << message << '\n';
        if ((strncmp(message, "Goodbye!", 8)) == 0) {
            break;
        }
        bzero(message, sizeof(message));
        std::cin.getline(message, 1024);
        write(socket_file_descriptor, message, sizeof(message));
    }
    // ��������� �����, ��������� ����������
    close(socket_file_descriptor);
    return 0;
}
