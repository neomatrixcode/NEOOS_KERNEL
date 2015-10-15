
 #ifndef NEO_KEYBOARD_H
 #define NEO_KEYBOARD_H
 
 #define NEO_CLAVE_DE_LIBERACION_TECLA  0x80
//AL ACTIVAR EL BIT 7 (0x80),  el teclado nos dice que una tecla acaba de soltarse
 
 namespace NEO{
		namespace Keyboard{
				void Install();
				void Espera();
				unsigned char ObtenerChar();
				char* ObtenerString();
			}
	 }
extern "C"
void NEO_Keyboard_Handler(struct regs* r);
 #endif
