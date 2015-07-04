/*************************************************************************
	> File Name: tinylibc.h
	> Author: luowei
 ************************************************************************/
#ifndef _TINYLIBC_H_
#define _TINYLIBC_H_

/* start.c */
/* 入口函数 */
void tinylibc_start(void);
/* 退出函数 */
void exit(long exitCode);

/* stdio.h */ 
typedef long FILE;
#define EOF (-1)

#define stdin	((FILE *)0)
#define stdout	((FILE *)1)
#define stderr	((FILE *)2)

long fputc(char c, FILE *stream);
long fputs(const char *str, FILE *stream);
long fwrite(const void *buffer, long size, long count, FILE *stream);

/* string.c */
/* 整数转化为指定进制的字符串 */
char *itoa(long n, char *str, long radix);
/* 比较字符串，按字典顺序前者大于后者返回1，相等返回0，小于返回-1 */
long strcmp(const char *src, const char *dst);
char *strcpy(char *dest, const char *src);
unsigned long strlen(const char *str);

/* printf.c */ 
#define va_list char *
#define va_start(ap, arg) (ap = (va_list)&arg + sizeof(arg))
#define va_arg(ap, t) (*(t *)((ap + sizeof(t)) - sizeof(t)))
#define va_end(ap) (ap = (va_list)0)

long vfprintf(FILE *stream, const char *format, va_list arglist);
long printf(const char *format, ...);
long fprintf(FILE *stream, const char *format);
 
#endif
