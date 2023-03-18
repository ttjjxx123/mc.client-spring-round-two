#include<stdio.h>
#include<windows.h>
#include<easyx.h>
#include<string.h>
#include"login.h"
#include"weblink.h"
#include"map.h"
#define MAX 20

void senddata(SOCKET client) {
	//将新注册的信息传回服务端
	char sendata[1024] = "";
	FILE* fp = fopen("userdata.txt", "r");
	if (!fp)
	{
		printf("failed when opening the file\n");
		exit(-1);
	}
	fread(sendata, sizeof(char), 1024, fp);
	send(client, sendata, 1024, 0);
	if (fclose(fp))
	{
		printf("Error in closing file\n");
		exit(-1);
	}

	//释放接口
	closesocket(client);
	WSACleanup();
}

int main()
{
	//连接服务器，因为从头到尾都需要client等网络变量，就没写在函数里，而在main中
	WSADATA wsdata;
	if (WSAStartup(MAKEWORD(2, 2), &wsdata))
	{
		std::cout << "init socket failed!" << std::endl;
		WSACleanup();
		return FALSE;
	}
	//检测版本号
	if (LOBYTE(wsdata.wVersion) != 2 || HIBYTE(wsdata.wHighVersion) != 2) {
		std::cout << "Error: wsadata.wVersion != 2 ." << std::endl;
		WSACleanup();
		return -1;
	}
	SOCKET client;
	client = socket(PF_INET, SOCK_STREAM, 0);
	if (client == INVALID_SOCKET)
	{
		std::cout << "create socket fail" << std::endl;
		WSACleanup();
		return FALSE;
	}
	//填充服务端信息
	SOCKADDR_IN server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(25565);
	//发送连接请求 请求连接服务器
	if (connect(client, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		std::cout << "Error: connect server failed !" << std::endl;
		WSACleanup();
		exit(-1);
	}
	std::cout << "成功连接到服务器" << std::endl;
	//发送数据
	char temp[1024] = { 0 };
	std::cout << "开始发送数据....." << std::endl;
	snprintf(temp, sizeof(temp), "%s", "已连接我的世界客户端 ");
	int sendLen = send(client, (char*)temp, sizeof(temp), 0);
	if (sendLen < 0) {
		std::cout << "Error: send info to server failed !" << std::endl;
		exit(-1);
	}
	std::cout << "发送数据成功、等待服务器响应....." << std::endl;

	//接收用户信息
	char recv_buf[1024] = { 0 };
	int recv_len = recv(client, recv_buf, sizeof(recv_buf), 0);
	FILE* fp = fopen("userdata.txt", "w");
	if (!fp)
	{
		printf("failed when opening the file\n");
		return -1;
	}
	if (recv_len < 0) {
		std::cout << "Error: receive info from server failed !" << std::endl;
		return -1;
	}
	fputs(recv_buf, fp);
	if (fclose(fp))
	{
		printf("Error in closing file\n");
		exit(-1);
	}
	std::cout << "接受用户信息成功" << std::endl;



	//登录游戏
	getuserinfor();
	int choice = -1;
	int id = -1, menu_choice = -1;
	while (id < 0)
	{
		choice = log_getchoice();
		switch (choice)
		{
		case 1:id = signin(); break;
		case 2:signup(); break;
		case 3:printf("Done\n"); senddata(client); return 0;
		default:printf("error when get choice\n"); return -1;
		}
	}
	if (id >= 0 && id < usernum)
	{
		menu_choice = menu();
	}
	else
	{
		senddata(client);
		return -1;
	}
	switch (menu_choice)
	{
	case 1:begingame(); break;//游戏主体
	case 2: begingame(); break;
	case 3: senddata(client); break;
	}
	senddata(client);
	return 0;
}