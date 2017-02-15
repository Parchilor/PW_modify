# PW_modify
Personal use.  
All source
# How to use
Set password path in <TOPDIR>/include/password.h(PW_PATH)
Set password string max length in <TOPDIR>/include/password.h(PWMAXLEN)

API:
* int PW_setup(unsigned char *pw); // Set password and save in PW_PATH. always return 0
* int PW_comfirm(char *pw_in); // Comfirm pw_in to password which save in PW_PATH. If pass return 0,else return 1;
* int PW_check_empty(void); // Check PW_PATH.If no password save in,return 1.Else return 0
