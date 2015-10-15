
#include <NEO_Mem.h>

/**
 * regresa el nuevo bufer
 * POSIX : memset
 * */
void* NEO::Mem::Set(void* buf, int c, size_t lon)
{
	unsigned char* tmp=(unsigned char*)buf;
	while(lon--)
	{
		*tmp++=c;
	}
	return buf;
}
/**
 * regresa el bufer destino
 * @ POSIX : memcpy
 * */
void* NEO::Mem::Cpy(void* dest,const void* src, size_t len)
{
	const unsigned char* sp=(const unsigned char*)src;
	unsigned char* dp=(unsigned char*)dest;
	for(;len!=0;len--) *dp++=*sp++;
	return dest;
}
/**
 * regresa 0 si son iguales, -1 si b es mayor a a, 1 si a es mayor a b
 * @note POSIX name: memcmp
 * */
int NEO::Mem::Comp(const void* p1, const void* p2, size_t len)
{
	const char* a=(const char*)p1;
	const char* b=(const char*)p2;
	size_t i=0;
	for(;i<len;i++)
	{
		if(a[i] < b[i])
			return -1;
		else if(a[i] > b[i])
			return 1;
	}
	return 0;
}
