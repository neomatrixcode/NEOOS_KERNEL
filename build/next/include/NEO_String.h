//desde aqui se manipulan los strings
#ifndef NEO_STRING_H
#define NEO_STRING_H

#include <NEO_Types.h>

namespace NEO{
		namespace String{
				size_t Length(const char* src);
				int Cpy(char* dest, const char* src);
				int Comp(const char *p1, const char *p2);
				char* Cat(char *dest, const char *src);
				bool IsUpper(char c);
				bool IsLower(char c);
				bool IsDigit(char c);
			}
	
	}
#endif
