#include <kernel/string.h>

ust strlen(const char* str) 
{
	ust len = 0;
	while (str[len])
		len++;
	return len;
}

s32 strcmp(const char* str1, const char* str2)
{
	while(*str1 == *str2 )
	{
		if(!*str1)
			return 0;
		str1++;
		str2++;
	}
	if(*str1<*str2)
	{
		return -1;
	}else{
		return 1;
	}
}
