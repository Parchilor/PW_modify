#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/md5.h>
#include "password.h"

int main (int argc, char *argv[])
{
	unsigned char pw[PWMAXLEN];
	printf("Checking...\n");
	usleep(1000 * 111);
	if(PW_check_empty())
	{
		printf("PassWord is empty!\n");
		printf("Setting New PassWord\nNew PassWord: ");
		fgets(pw, PWMAXLEN, stdin);
		PW_setup(pw);
		printf("Set done!\n");
		return 0;
	}
	printf("PassWord is not empty!\n");
	while (1)
	{
		printf("Enter PassWord: ");
		fgets(pw, PWMAXLEN, stdin);
		if (!PW_comfirm(pw))
		{
			memset(pw, 0, PWMAXLEN);
			printf("Enter New PassWord: ");
			fgets(pw, PWMAXLEN, stdin);
			PW_setup(pw);
			printf("Modify done!\n");
			return 0;
		}
		printf("PassWord invalid!\n");
	}
	return 0;
}

