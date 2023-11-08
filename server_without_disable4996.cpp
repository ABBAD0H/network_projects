// server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <Ws2tcpip.H>
//#pragma warning(disable : 4996)
using namespace std;
int main()
{
	
	WSADATA data;
	WORD DLLversion = MAKEWORD(2, 1);
	if (WSAStartup(DLLversion, &data) != 0)
	{
		cout << "Library error" << endl;
		return 0;
	}
	sockaddr_in addr;
	//addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	InetPton(AF_INET, TEXT("127.0.0.1"), &addr.sin_addr.s_addr);
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;



	SOCKET slisten = socket(AF_INET, SOCK_STREAM, NULL);

	bind(slisten, (SOCKADDR*)&addr, sizeof(addr));
	listen(slisten, SOMAXCONN);

	SOCKET newConnect;
	int size_addr = sizeof(addr);
	newConnect = accept(slisten, (SOCKADDR*)&addr, &size_addr);
	if (newConnect == 0)
	{
		cout << "Error connection" << endl;
	}
	else
	{
		cout << "connet complete" << endl;
		char msg[256] = "HELLO WORLD!!!!";
		send(newConnect, msg, sizeof(msg),NULL);
	}
	system("pause");
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
