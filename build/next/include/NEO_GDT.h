
#include <NEO_Types.h>
#ifndef NEO_GDT_H
#define NEO_GDT_H

namespace NEO{
		namespace GDT{
				void SetGate(int num, uint32_t base, uint32_t limit, uint8_t access,uint8_t gran);
				void Install();
				/* Define una entrada en la GDT. Decimos "empacada" porque
 *  eso evita que el compilador haga lo que cree que es mejor:
 *  evitar la "optimización" del compilador, al empacar */
				struct Entry{
    			unsigned short limit_low;
    			unsigned short base_low;
    			unsigned char base_middle;
    			unsigned char access;

		//bits de campo de acceso
		//7: P - ¿Segmento Presente? (1=Sí) 6-5: Cuál Ring (0 a 3) 4: DT - Tipo de Descriptor 3-0: ¿Qué Tipo?

    			unsigned char granularity;

    	//bits de campo de granularidad
		//7: G - Granularidad (0=1 byte, 1=4 KB) 6: D - Tamaño de Operador (0=16 bits, 1=32 bits) 5: 0 - Siempre 0
		// 4: A - Disponible para el Sistema (Siempre 0)

    			unsigned char base_high;
				} __attribute__((packed));


				/* Puntero especial que incluye el límite: La cantidad máxima
 				*  de bytes ocupados por la GDT, menos 1, Una vez más, esto
 				*  NECESITA estar empacado */
				struct Ptr{
    			unsigned short limit;
    			unsigned int base;
				} __attribute__((packed));
		}
	
}


#endif
