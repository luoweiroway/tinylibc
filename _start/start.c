/*************************************************************************
	> File Name: start.c
	> Author: luowei
 ************************************************************************/
#include "tinylibc.h"

extern int main(long argc, char *argv[]);
void exit(long);

/* 入口函数 */
void tinylibc_start(void)
{
	long ret;
	
 	long argc;
 	char **argv;
 	
 	char *rbp_reg = 0;
 	/* ebp_reg = %rbp,将寄存器rbp的值存入rbp_reg中*/
 	asm("movq %%rbp, %0 \n":"=r"(rbp_reg));
 	
 	argc = *(long *)(rbp_reg + 4);
 	argv = (char **)(rbp_reg + 8);
	
	ret = main(argc, argv); //enter user's main function 
	exit(ret);
}

void exit(long exitCode)
{
	asm(
	"movq %0, %%rbx \n\t"
	"movq $1, %%rax \n\t"
	"int $0x80 \n\t"
	"hlt \n\t"::"m"(exitCode));
}

