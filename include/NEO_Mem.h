
#ifndef NEO_MEM_H
#define NEO_MEM_H

#include <NEO_Types.h>

namespace NEO{
		namespace Mem{
				void* Set(void* buf, int c, size_t len);
				void* Cpy(void* dest,const void* src, size_t len);
				int Comp(const void* p1, const void* p2, size_t len);
			}
	}


#endif
