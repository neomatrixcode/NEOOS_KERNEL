#ifndef NEO_SCREEN_H
#define NEO_SCREEN_H
#include <NEO_Color.h>
#include <NEO_Types.h>


typedef enum NEO_SIDE{
		NEO_SIDE_BACKGROUND,
		NEO_SIDE_FOREGROUND
}NEO_SIDE;

namespace NEO{
	namespace Screen{
			NEO_Color ObtenerColor(NEO_SIDE side);
			void ColocarColor(NEO_SIDE side, NEO_Color color);			
			void ColocarCursor(uint8_t x, uint8_t y);
			void ColocarChar(char c);
			void ColocarString(const char* str);
			void Limpiar(NEO_Color color);
			void ObtenerCursor(uint8_t x, uint8_t y);
		}
	}
#endif
