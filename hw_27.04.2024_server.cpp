//#include <iostream>
//#include <string>
//#include <WinSock2.h>
//#include <ws2tcpip.h>
//#pragma comment(lib, "Ws2_32.lib")
//#include <vector>
//#include <stdio.h>
//using namespace std;
//
//int main()
//{
//    WSADATA wsaData;
//    SOCKET ServSock, newConnection;
//    struct sockaddr_in serverAddr, clientAddr;
//    int addrLen = sizeof(struct sockaddr_in);
//    const int BUFF_SIZE = 1024;
//    char clientMessage[BUFF_SIZE];
//    vector <SOCKET> clientSockets;
//    fd_set readfds;
//    // Инициализация WinSock
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        cout << "Failed. Error Code: " << WSAGetLastError() << endl;
//        return 1;
//    }
//    // Создание серверного сокета
//    if ((ServSock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
//        cout << "Could not create socket: " << WSAGetLastError() << endl;
//        WSACleanup();
//        return 1;
//    }
//    // Подготовка структуры sockaddr_in
//    serverAddr.sin_family = AF_INET;
//    serverAddr.sin_addr.s_addr = INADDR_ANY;
//    serverAddr.sin_port = htons(20000);
//    // Привязка
//    if (bind(ServSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
//        cout << "Bind failed with error code: " << WSAGetLastError() << endl;
//        closesocket(ServSock);
//        WSACleanup();
//        return 1;
//    }
//    // Слушаем входящие подключения
//    listen(ServSock, 3);
//    cout << "Waiting for incoming connections..." << endl;
//    while (true) {
//        // Очистка сета и добавление мастер сокета
//        FD_ZERO(&readfds);
//        FD_SET(ServSock, &readfds);
//        for (size_t i = 0; i < clientSockets.size(); i++) {
//            FD_SET(clientSockets[i], &readfds);
//        }
//        // Ожидание активности на любом из сокетов
//        if (select(0, &readfds, nullptr, nullptr, nullptr) < 0) {
//            cout << "select error" << endl;
//            break;
//        }
//        // Если что-то произошло на мастер сокете, то это входящее подключение
//        if (FD_ISSET(ServSock, &readfds)) {
//            if ((newConnection = accept(ServSock, (struct sockaddr*)&clientAddr, &addrLen)) < 0) {
//                perror("accept");
//                continue;
//            }
//
//            cout << "New connection accepted" << endl;
//            clientSockets.push_back(newConnection);
//        }
//        // Иначе это данные от клиента
//        for (size_t i = 0; i < clientSockets.size(); i++) {
//            if (FD_ISSET(clientSockets[i], &readfds)) {
//                int readSize = recv(clientSockets[i], clientMessage, BUFF_SIZE, 0);
//
//                if (readSize == SOCKET_ERROR) {
//                    cout << "recv failed: " << WSAGetLastError() << endl;
//                    closesocket(clientSockets[i]);
//                    clientSockets.erase(clientSockets.begin() + i);
//                    continue;
//                }
//                if (readSize == 0) {
//                    cout << "Client disconnected" << endl;
//                    closesocket(clientSockets[i]);
//                    clientSockets.erase(clientSockets.begin() + i);
//                    continue;
//                }
//                // Рассылка сообщения от клиента всем остальным
//                for (size_t j = 0; j < clientSockets.size(); j++) {
//                    if (i != j) {
//                        send(clientSockets[j], clientMessage, readSize, 0);
//                    }
//                }
//            }
//        }
//    }
//    // Закрытие сокета
//    closesocket(ServSock);
//    WSACleanup();
//    return 0;
//}
//
////int main()
////{
////	const int BUFF_SIZE = 1024;
////
////	// инициализация сокетных интерфейсов Win32API
////	WSADATA wsaData;
////	int erStat = WSAStartup(MAKEWORD(2, 2), &wsaData);
////	if (erStat != 0) {
////		cout << "Error WinSock version initialization #";
////		cout << WSAGetLastError();
////		return 1;
////	}
////	else
////		cout << "WinSock initialization is OK" << endl;
////
////	// создание и инициализация сокета сервера
////	SOCKET ServSock = socket(AF_INET, SOCK_STREAM, 0);
////	if (ServSock == INVALID_SOCKET) {
////		cout << "Error initialization socket # " << WSAGetLastError() << endl;
////		closesocket(ServSock);
////		WSACleanup();
////		return 1;
////	}
////	else
////		cout << "Server socket initialization is OK" << endl;
////
////	// привязка сокета к паре IP-адрес/порт
////	in_addr ip_to_num;
////	erStat = inet_pton(AF_INET, "127.0.0.1", &ip_to_num);
////	if (erStat <= 0)
////		cout << "Error in IP translation to special numeric format" << endl;
////
////	sockaddr_in servInfo;
////	ZeroMemory(&servInfo, sizeof(servInfo));
////
////	servInfo.sin_family = AF_INET;
////	servInfo.sin_addr = ip_to_num;
////	servInfo.sin_port = htons(20000);
////
////	erStat = bind(ServSock, (sockaddr*)&servInfo, sizeof(servInfo));
////	if (erStat != 0) {
////		cout << "Error Socket binding to server info. Error # " << WSAGetLastError() << endl;
////		closesocket(ServSock);
////		WSACleanup();
////		return 1;
////	}
////	else
////		cout << "Binding socket to Server info is OK" << endl;
////
////	// прослушивание привязанного порта для идентификации подключений
////	erStat = listen(ServSock, SOMAXCONN);
////
////	if (erStat != 0) {
////		cout << "Can't start to listen to. Error # " << WSAGetLastError() << endl;
////		closesocket(ServSock);
////		WSACleanup();
////		return 1;
////	}
////	else
////		cout << "Listening..." << endl;
////
////	cout << "Server started\n";
////
////	// подтверждение подключения
////	
////	sockaddr_in clientInfo;
////
////	ZeroMemory(&clientInfo, sizeof(clientInfo));
////	int clientInfo_size = sizeof(clientInfo);
////	SOCKET ClientConn = accept(ServSock, (sockaddr*)&clientInfo, &clientInfo_size);
////
////	if (ClientConn == INVALID_SOCKET) {
////		cout << "Client detected, but can't connect to a client. Error # " << WSAGetLastError() << endl;
////		closesocket(ServSock);
////		closesocket(ClientConn);
////		WSACleanup();
////		return 1;
////	}
////	else
////		cout << "Connection to a client established successfully" << endl;
////
////	// передача данных между клиентом и сервером
////	vector <char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);
////	int packet_size = 0;
////
////	while (true) {
////		packet_size = recv(ClientConn, servBuff.data(), servBuff.size(), 0);
////		cout << "Client's message: " << servBuff.data() << endl;
////
////		cout << "Your (host) message: ";
////		fgets(clientBuff.data(), clientBuff.size(), stdin);
////
////		if (clientBuff[0] == 'x' && clientBuff[1] == 'x' && clientBuff[2] == 'x') {
////			shutdown(ClientConn, SD_BOTH);
////			closesocket(ServSock);
////			closesocket(ClientConn);
////			WSACleanup();
////			return 0;
////		}
////
////		packet_size = send(ClientConn, clientBuff.data(), clientBuff.size(), 0);
////
////		if (packet_size == SOCKET_ERROR) {
////			cout << "Can't send message to Client. Error # " << WSAGetLastError() << endl;
////			closesocket(ServSock);
////			closesocket(ClientConn);
////			WSACleanup();
////			return 1;
////		}
////	}
////}

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include <vector>
#include <stdio.h>
using namespace std;

int main() {
	WSADATA wsaData;
	SOCKET serverSocket, clientSocket1, clientSocket2;
	struct sockaddr_in server, client;
	char buffer[1024] = { 0 };
	std::vector<SOCKET> clients;

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//привязка сокета к паре IP-адрес/порт
	in_addr ip_to_num;
	int erStat = inet_pton(AF_INET, "127.0.0.1", &ip_to_num);
	if (erStat <= 0)
		cout << "Error in IP translation to special numeric format" << endl;

	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout << "Could not create socket: " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}

	sockaddr_in servInfo;
	ZeroMemory(&servInfo, sizeof(servInfo));

	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(20000);

	erStat = bind(serverSocket, (sockaddr*)&servInfo, sizeof(servInfo));
	if (erStat != 0) {
		cout << "Error Socket binding to server info. Error # " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
	else
		cout << "Binding socket to Server info is OK" << endl;

	listen(serverSocket, 2); // Максимум 2 ожидающих соединения

	int c = sizeof(struct sockaddr_in);
	std::cout << "Waiting for client connections...\n";

	// Принимаем первое соединение
	clientSocket1 = accept(serverSocket, (struct sockaddr*)&client, &c);
	if (clientSocket1 == INVALID_SOCKET) {
		std::cout << "Accept failed." << std::endl;
	}
	else {
		std::cout << "Client1 connected." << std::endl;
		clients.push_back(clientSocket1);
	}

	// Принимаем второе соединение
	clientSocket2 = accept(serverSocket, (struct sockaddr*)&client, &c);
	if (clientSocket2 == INVALID_SOCKET) {
		std::cout << "Accept failed." << std::endl;
	}
	else {
		std::cout << "Client2 connected." << std::endl;
		clients.push_back(clientSocket2);
	}


	while (true) {
		ZeroMemory(buffer, 1024);
		//int bytesReceived = recv(clientSocket1, buffer, 1024, 0); // Читаем сообщение от первого клиента
		for (SOCKET s : clients) {
			int bytesReceived = recv(s, buffer, 1024, 0);
			if (bytesReceived > 0) {
				// Отправляем сообщение всем клиентам
				for (SOCKET s : clients) {
					send(s, buffer, bytesReceived, 0);
				}
			}
		}
	}

	// Закрытие соединений
	closesocket(clientSocket1);
	closesocket(clientSocket2);
	closesocket(serverSocket);
	WSACleanup();

	return 0;
}