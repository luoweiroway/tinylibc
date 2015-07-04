/*************************************************************************
	> File Name: printf.c
	> Author: luowei
 ************************************************************************/
#include "tinylibc.h"

long vfprintf(FILE *stream, const char *format, va_list arglist){
	long translating = 0;
	long ret = 0;
	const char *p = 0;
	for (p = format; *p != '\0'; p ++){
		switch (*p){
		case '%':
			if (! translating){
				translating = 1;
			}
			else{
				if (fputc('%', stream) < 0){
					return EOF;
				}
				ret ++;
				translating = 0;
			}
			break;
		case 'd':
			if (translating){
				char buf[16];
				translating = 0;
				itoa(va_arg(arglist, long), buf, 10);
				if (fputs(buf, stream) < 0){
					return EOF;
				}
				ret += strlen(buf);
			}
			else if (fputc('d', stream) < 0){
				return EOF;
			}
			else{
				ret ++;
			}
			break;
		case 's':
			if (translating){
				const char *str = va_arg(arglist, const char *);
				translating = 0;
				if (fputs(str, stream) < 0){
					return EOF;
				}
				ret += strlen(str);
			}
			else if (fputc('s', stream) < 0){
				return EOF;
			}
			else{
				ret ++;
			}
			break;
		default:
			if (translating){
				translating = 0;
			}
			if (fputc(*p, stream) < 0){
				return EOF;
			}
			else{
				ret ++;
			}
			break;
		}
	}
	return ret;
}

long printf(const char *format, ...){
	va_list(arglist);
	va_start(arglist, format);
	return vfprintf(stdout, format, arglist);
}

long fprintf(FILE *stream, const char *format){
	va_list(arglist);
	va_start(arglist, format);
	return vfprintf(stream, format, arglist);
}
