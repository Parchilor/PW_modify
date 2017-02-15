#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>

#include "password.h"

typedef struct md5
{
	unsigned char *pw;
	int len;
	char md5[35];
}_MD5;

void _MD5_init(_MD5 *md5, unsigned char *pw, int pwlen)
{
	int len = strlen(pw);
	md5->pw = malloc(sizeof(unsigned char) * len);
	memcpy(md5->pw, pw, len);
	md5->len = pwlen;
}

void _MD5_clear(_MD5 *md5)
{
	free(md5->pw);
	memset(md5, 0, sizeof(_MD5) * 1);
}

void _MD5_convert_hex(unsigned char *in, char *out)
{
	int i;
	for(i = 0; i < 16; i++)
	{
		sprintf(out + (i*2), "%02x", in[i]);  // Convert to 32 bit(lowercase) 
	}
	out[32] = 0;
}

int _MD5_encrypt(_MD5 *md5)
{
	MD5_CTX ctx;

	unsigned char md5_tmp[16];
	MD5_Init(&ctx);
	MD5_Update(&ctx, md5->pw, md5->len);
	MD5_Final(md5_tmp, &ctx);
	
	char *out = malloc(sizeof(char) * 35);
	memset(out, 0x00, 35);
	_MD5_convert_hex(md5_tmp, out);
	memcpy(md5->md5, out, 35);
	free(out);
	out = NULL;
	return 0;
}

int PW_setup(unsigned char *pw)
{
	_MD5 *md5 = malloc(sizeof(_MD5) * 1);
	_MD5_init(md5, pw, strlen(pw) - 1);
		
	_MD5_encrypt(md5);
	_MD5_save(md5);
	return 0;
}

int _MD5_save(_MD5 *md5)
{
	FILE *fp = fopen(PW_PATH, "w");
	if(fp == NULL)
		return -1;
	fwrite(md5->md5, strlen(md5->md5), 1, fp);
	fclose(fp);
	return 0;

}

int _MD5_read(char *rbuf, int rlen)
{
	FILE *fp = fopen(PW_PATH, "r");
	if(fp == NULL)
		return -1;
	fread(rbuf, rlen, 1, fp);
	fclose(fp);
	return 0;
}

int PW_comfirm(char *pw_in)
{
	char *rbuf = malloc(sizeof(char) * 32);
	_MD5 *md5 = malloc(sizeof(_MD5) * 1);

	_MD5_init(md5, pw_in, strlen(pw_in) - 1);
	
	_MD5_encrypt(md5);
	_MD5_read(rbuf, 32);
	
	if(!memcmp(rbuf, md5->md5, 32))
	{
		free(rbuf);
		rbuf = NULL;
		_MD5_clear(md5);
		free(md5);
		md5 = NULL;
		return 0;
	}
	free(rbuf);
	rbuf = NULL;
	_MD5_clear(md5);
	free(md5);
	md5 = NULL;
	return -1;
}

int PW_check_empty(void)
{
	char *check = malloc(sizeof(char) * 32);
	_MD5_read(check, 32);
	if (!strncmp(check, "", 32))
	{
		free(check);
		check = NULL;
		return 1;
	}
	else
	{
		free(check);
		check = NULL;
		return 0;
	}
}
