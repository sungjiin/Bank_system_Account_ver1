#include <stdio.h>
#include <string.h>

typedef struct account {
	char id[10];
	char pass[10];
	int balance;
}Account;

Account acc[10];
int numOfAccount = 0;

void showMenu();
void join();
void login();
void showSubMenu();
int transaction(int x);

int main()
{
	int choice;

	FILE * fp;
	int i;

	if ((fp = fopen("bank.txt", "rt")) == NULL) {
		printf("not exist file!!\n");
		return 0;
	}
	else {
		fscanf(fp, "%d", &numOfAccount);
		for (i = 0; i < numOfAccount; i++) {
			fscanf(fp, "%s %s %d", &acc[i].id, &acc[i].pass, &acc[i].balance);
		}
		fclose(fp);
	}

	do
	{
		showMenu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			join(); break;
		case 2:
			login(); break;
		case 3:
			fopen_s(&fp, "bank.txt", "wt"); //����ּ� > ���� ���� �ȿ� �־���Ѵ�. fopen�� w�� ������ ������� �ڽ��� ������ �����.
			fprintf(fp, "%d\n", numOfAccount);
			for (i = 0; i < numOfAccount; i++)
				fprintf(fp, "%s %s %d\n", acc[i].id, acc[i].pass, acc[i].balance);
			return 0;
		default:
			printf("Wrong Input!");
		}
	} while (1);

}
//1�� ȸ������, 2�� �α���, 3�� ����

void showMenu() {
	printf("------------------------\n");
	printf("1. Join\n");
	printf("2. Login\n");
	printf("3. Exit\n");
	printf("choice : ");
}
void showSubMenu() {
	printf("------------------------\n");
	printf("1. Deposit\n");
	printf("2. Withdraw\n");
	printf("3. Query\n");
	printf("4. SendMoney\n");
	printf("5. Logout\n");
	printf("choice : ");


}

void join() {
	char id[10], pass[10];
	int i;
	printf("Enter id : ");
	scanf("%s", &id);
	for (i = 0; i < numOfAccount; i++)
	{
		// ���� �迭�ȿ� ���� �ۼ��� ���̵� �����Ѵٸ� already exist�� ����� ������ break
		if (strcmp(acc[i].id, id) == 0)
		{
			printf("already exist!\n");
			break;
		}
	}

	// ���� for���� ������ �����Ͽ����� �����ϴ� ���̵� ���°����� �����ϸ� passward�� �ۼ�
	if (i == numOfAccount) {
		strcpy(acc[numOfAccount].id, id);
		printf("Enter passward : ");
		scanf("%s", &pass);
		strcpy(acc[numOfAccount].pass, pass);
		acc[numOfAccount].balance = 0;
		numOfAccount++;
		printf("%d \n", numOfAccount);
	}
	else
		join();
}

int transaction(int x) {
	int choice;
	int query, deposit, withdraw;
	query = acc[x].balance;
	char yourid[10];
	int money;
	int i;

	do
	{
		showSubMenu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("Deposit!!\n");
			printf("Input Money : ");
			scanf("%d", &deposit);
			acc[x].balance += deposit;
			break;
		case 2:
			printf("Withdraw!!\n");
			printf("Input Money : ");
			scanf("%d", &withdraw);
			acc[x].balance = acc[x].balance - withdraw;
			break;
		case 3:
			printf("Query\n");
			printf("%dWon\n", acc[x].balance);;
			break;
		case 4:
			printf("Who? ");
			scanf("%s", &yourid);
			for (i = 0; i < numOfAccount; i++) {
				if (strcmp(acc[i].id, yourid) == 0) {
					printf("%s ���̵� �۱�!\n", acc[i].id);
					break;
				}
				else {
					printf("This ID is not exist\n");
					return 0;
				}
			}
			printf("How much?");
			scanf("%d", &money);
			if (acc[x].balance - money > -1) {
				acc[i].balance = acc[i].balance + money;
				acc[x].balance = acc[x].balance - money;
				printf("%s�� %d won �۱�!! //�ܾ� : %d won", acc[i].id, money, acc[x].balance);
			}
			else
				printf("No Money!\n");
			break;
		case 5:
			printf("LogOut!\n");
			return 0;
		default:
			printf("Wrong Input!\n");
		}
	} while (1);
}


void login() {
	int i;
	char id[10], pass[10];

	printf("Input id : ");
	scanf("%s", &id);
	for (i = 0; i < numOfAccount; i++)
	{
		if (strcmp(acc[i].id, id) == 0)
		{
			printf("right ID\n");
			break;
		}
	}
	if (i == numOfAccount) {
		while (1)
		{
			printf("Not exist ID!\n");
			printf("ReInput ID : ");
			scanf("%s", &id);
			for (i = 0; i < numOfAccount; i++) {
				if (strcmp(acc[i].id, id) == 0)
					break;
			}
			if (i == numOfAccount)
				continue;
			else
				break;
		}
	}


	printf("Input passward : ");
	scanf("%s", &pass);

	for (i = 0; i < numOfAccount; i++)
	{
		if (strcmp(acc[i].id, id) == 0 && strcmp(acc[i].pass, pass) == 0)
		{
			printf("LOGIN Success!!\n");
			transaction(i);
			break;
		}

		else if (strcmp(acc[i].id, id) == 0)
		{
			while (1)
			{
				printf("Wrong Password!\n");
				printf("ReInput passward : ");
				scanf_s("%s", &pass);
				if (strcmp(acc[i].id, id) == 0 && strcmp(acc[i].pass, pass) == 0)
				{
					printf("LOGIN Success!!\n");
					transaction(i);
					break;
				}
			}
		}
	}
}