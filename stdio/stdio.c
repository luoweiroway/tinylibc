/*************************************************************************
	> File Name: stdio.c
	> Author: luowei
 ************************************************************************/
#include "tinylibc.h"
#include "bits/syscall.h"

long fputc(char c, FILE *stream){
	if (fwrite(&c, 1, 1, stream) != 1){
		return EOF;
	}
	else{
		return c;
	}
}

long fputs(const char *str, FILE *stream) {
	long len = strlen(str);
	if (fwrite(str, 1, len, stream) != len){
		return EOF;
	}
	else{
		return len;
	}
}

static inline long __syscall3(long n, long a1, long a2, long a3){
	unsigned long ret;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3) : "rcx", "r11", "memory");
	return ret;
}

#define __syscall_write(fd, buf, len)    __syscall3(__NR_write, (fd), (long)(buf), (len))

static long write(long fd, const void *buffer, unsigned long size){
	long ret = 0;
	ret = __syscall_write(fd, buffer, size);
	return ret;
}

long fwrite(const void *buffer, long size, long count, FILE *stream){
	return write((long)stream, buffer, size * count);
}
