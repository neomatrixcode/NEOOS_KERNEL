
#include <NEO_Error.h>
#include <NEO_Screen.h>


void NEO::Error::Mostrar(const char* error)
{
	NEO::Screen::Limpiar(NEO_COLOR_BLANCO);
	NEO::Screen::ColocarColor(NEO_SIDE_BACKGROUND, NEO_COLOR_BLANCO);
	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_ROJO);
	NEO::Screen::ColocarCursor(10,10); //toma en cuenta que el ancho maximo de la pantalla es de 80
	NEO::Screen::ColocarString("\t\t ERORR \n\t\t fATAL EN EL KERNEL \n\t\t Error numero:");
	NEO::Screen::ColocarString(error);
}
