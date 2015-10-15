
#include "NEO_Types.h"

#ifndef NEO_IDT_H
#define NEO_IDT_H

namespace NEO{
	namespace IDT{
			void Flush();
			void SetGate(uint8_t, uint32_t, uint16_t, uint8_t);
			void Install();
			struct Entry{
				uint16_t base_low;
				uint16_t sel;   // ¡Nuestro segmento del kernel va aquí! 0x08
				uint8_t always0;// ¡Esto siempre será establecido a 0! 
				uint8_t flags;  // banderas de acceso BITS: 7: ¿Segmento Presente? (1 = Sí), 
								// 6-5: DPL - Cuál Ring (0 a 3) 4-5:Siempre 01110 (0x14)

				uint16_t base_high;
			} __attribute__((packed));

			
			struct Ptr{
				uint16_t limit;
				uint32_t base;
			} __attribute__((packed));
		}
	}


#endif
