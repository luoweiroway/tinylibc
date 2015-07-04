/*************************************************************************
	> File Name: string.c
	> Author: luowei
 ************************************************************************/
#include "tinylibc.h"

/* 整数转化为指定进制的字符串 */
char *itoa(long n, char *str, long radix){
	char digit[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *p = str;
	char *head = str;
	/* 转换进制在2-36之间 */
	if (! p || radix < 2 || radix > 36){
		return p;
	}
	/* 只支持非十进制的正整数转换 */
	if (radix != 10 && n < 0){
		return p;
	}
	if (n == 0){
		*p ++ = '0';
		*p = 0;
		return p;
	}
	if (radix == 10 && n < 0){
		*p ++ = '-';
		n = -n;
	}
	while (n){
		*p ++ = digit[n % radix];
		n /= radix;
	}
	*p = 0;
	
	/* 逆序 */
	for (--p; head < p; ++head, --p){
		char temp = *head;
		*head = *p;
		*p = temp;
	}
	return str;
}

/* 比较字符串，按字典顺序前者大于后者返回1，相等返回0，小于返回-1 */
long strcmp(const char *src, const char *dst){
	long ret = 0;
	unsigned char *p1 = (unsigned char *)src;
	unsigned char *p2 = (unsigned char *)dst;
	while (! (ret = *p1 - *p2) && *p2){
		++p1, ++p2;
	}
	if (ret < 0){
		ret = -1;
	}
	else if (ret > 0){
		return 1;
	}
	else{
		ret = 1;
	}
	return ret;
}

/* 字符串拷贝 */
char *strcpy(char *dest, const char *src){
	char *ret = dest;
	while (*src){
		*dest ++ = *src; 
	}
	*dest = '\0';
	return ret;
}

/* 求字符串长度 */
unsigned long strlen(const char *str){
	long cnt = 0;
	if(!str){
		return 0;
	}
	while (*str != '\0'){
		cnt ++;
		str ++;
	}
	return cnt;
}
