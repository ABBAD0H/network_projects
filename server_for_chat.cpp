﻿
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#pragma warning(disable: 4996)

SOCKET Connections[100];
int Counter = 0;

void ClientHandler(int index) {
	char msg[256];
	while(true) {
		recv(Connections[index], msg, sizeof(msg), NULL);
		for(int i = 0; i < Counter; i++) {
			if(i == index) {
				continue;
			}

			send(Connections[i], msg, sizeof(msg), NULL);
		}
	}
}

int main() {
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if(WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("192.168.0.1");
	//addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(7500);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	int count = 0;
	for(int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if(newConnection == 0) {
			std::cout << "Error #2\n";
		} else {
			char msg2[256];
			/*
			recv(Connections[i], msg2, sizeof(msg2), NULL);
			std::cout << msg2 << std::endl;
			for (int i = 0; i < 4; i++)
			{
				if (msg2[i] != '1')
				{
					closesocket(Connections[i]);
					i--;
					continue;
				}
			}
			*/
			std::cout << "Client Connected!\n";
			//char msg[256] = "Hello. It`s my first network program!";
			//send(newConnection, msg, sizeof(msg), NULL);

			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}


	system("pause");
	return 0;
}
