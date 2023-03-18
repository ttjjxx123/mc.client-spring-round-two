#include<stdio.h>

#include<easyx.h>
#include<string.h>
#define MAX 20
struct useriform {
	char username[MAX];
	char password[MAX];
}users[20];
int usernum = 0;
char* get_s(char* p, int n)
{
	fgets(p, n, stdin);
	char* pt = NULL;
	if (pt = strchr(p, '\n'))
	{
		*pt = '\0';
	}
	return p;
}
char* fget_s(char* p, int n, FILE* fp)
{
	fgets(p, n, fp);
	char* pt = NULL;
	if (pt = strchr(p, '\n'))
	{
		*pt = '\0';
	}
	return p;
}



int getuserinfor() {
	FILE* fp = fopen("userdata.txt", "r");
	if (!fp)
	{
		printf("failed when opening the file\n");
		return -1;
	}
	int num = 0;
	while (!feof(fp))
	{
		char ch = 'a';
		fscanf(fp, "%d%c", &num, &ch);
		fget_s(users[num].username, MAX, fp);
		fget_s(users[num].password, MAX, fp);
	}
	usernum = ++num;
	if (fclose(fp))
	{
		printf("Error in closing file\n");
		return -1;
	}
}

int log_getchoice()
{
	printf("1.sign in\t2.sign up\n3.exit\n");
	printf("input a number:\n");
	int choice = 0;
	while (scanf("%d", &choice) == 0 || choice < 1 || choice > 3)
	{
		printf("Please try again:\n");
		while (getchar() != '\n')
			continue;
	}
	while (getchar() != '\n')
		continue;
	return choice;
}
int signin()
{
	printf("Input your username:\n");
	char  username[MAX], password[MAX];
	get_s(username, MAX);
	int i;
	for (i = 0; i < usernum; i++)
	{
		if (strcmp(username, users[i].username) == 0)
		{
			break;
		}
	}
	if (i >= usernum)
	{
		printf("The username is unexisted\n\n");
		return -1;
	}
	else
	{
		int count = 0;
		printf("input your password:\n");
		get_s(password, MAX);
		while (strcmp(users[i].password, password) != 0 && count++ < 3)
		{
			printf("Try again,%d times left", 3 - count);
		}
		if (count < 3)
		{
			printf("Welcome,%s\n", users[i].username);
			return i;
		}
		else
			return -1;
	}
}
int menu()
{
	int choice;
	printf("*****1.new game*****\n"
		"*****2.continue*****\n"
		"*****3.  Exit  *****\n");
	printf("input your choice:\n");
	if (scanf("%d", &choice) == 0 || choice < 1 || choice>3)
	{
		printf("please try again:\n");
	}
	return choice;
}


void signup()
{
	printf("set your username:(<=16 characters)\n");
	get_s(users[usernum].username, MAX);
	for (int i = 0; i < usernum; i++)
	{
		if (strcmp(users[i].username, users[usernum].username) == 0)
		{
			printf("The username has already existed!!\n");
			return;
		}
	}
	printf("your username is %s\n", users[usernum].username);
	printf("Set your password:\n");
	get_s(users[usernum].password, MAX);
	printf("input again to confirm:\n");
	char confirmkey[MAX];
	get_s(confirmkey, MAX);
	while (strcmp(users[usernum].password, confirmkey) != 0)
	{
		get_s(confirmkey, MAX);
	}
	printf("succeed in signing up\n\n");
	FILE* fp = fopen("userdata.txt", "a");
	if (!fp)
	{
		printf("failed when opening the file\n");
		return;
	}
	int i = 0;
	for (i = 0; i < usernum; i++);
	fprintf(fp, "%d\n", i);
	fputs(users[i].username, fp);
	fprintf(fp, "\n");
	fputs(users[i].password, fp);
	fprintf(fp, "\n");
	usernum++;
	if (fclose(fp))
	{
		printf("Error in closing file\n");
		return;
	}
}
