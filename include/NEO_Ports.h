
#ifndef NEO_PORTS_H
#define NEO_PORTS_H

#include "NEO_Types.h"

namespace NEO{
	namespace Ports{
			uint8_t InputB(uint16_t _port);
			uint16_t InputW(uint16_t port);
			void OutputB(uint16_t port, uint8_t value); 
		}
	}
#endif
