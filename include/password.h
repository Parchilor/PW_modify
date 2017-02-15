#pragma once
#define _M_DEBUG

#define PW_PATH "files/pw"
#define PWMAXLEN 1024

int PW_setup(unsigned char *pw);
int PW_comfirm(char *pw_in);
int PW_check_empty(void);
