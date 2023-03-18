#include<stdio.h>
#include<windows.h>
#include<easyx.h>
#include<string.h>
#include"login.h"
#include"weblink.h"
#include"map.h"
#define MAX 20

void senddata(SOCKET client) {
	//����ע�����Ϣ���ط����
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

	//�ͷŽӿ�
	closesocket(client);
	WSACleanup();
}

int main()
{
	//���ӷ���������Ϊ��ͷ��β����Ҫclient�������������ûд�ں��������main��
	WSADATA wsdata;
	if (WSAStartup(MAKEWORD(2, 2), &wsdata))
	{
		std::cout << "init socket failed!" << std::endl;
		WSACleanup();
		return FALSE;
	}
	//���汾��
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
	//���������Ϣ
	SOCKADDR_IN server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(25565);
	//������������ �������ӷ�����
	if (connect(client, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		std::cout << "Error: connect server failed !" << std::endl;
		WSACleanup();
		exit(-1);
	}
	std::cout << "�ɹ����ӵ�������" << std::endl;
	//��������
	char temp[1024] = { 0 };
	std::cout << "��ʼ��������....." << std::endl;
	snprintf(temp, sizeof(temp), "%s", "�������ҵ�����ͻ��� ");
	int sendLen = send(client, (char*)temp, sizeof(temp), 0);
	if (sendLen < 0) {
		std::cout << "Error: send info to server failed !" << std::endl;
		exit(-1);
	}
	std::cout << "�������ݳɹ����ȴ���������Ӧ....." << std::endl;

	//�����û���Ϣ
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
	std::cout << "�����û���Ϣ�ɹ�" << std::endl;



	//��¼��Ϸ
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
	case 1:begingame(); break;//��Ϸ����
	case 2: begingame(); break;
	case 3: senddata(client); break;
	}
	senddata(client);
	return 0;
}