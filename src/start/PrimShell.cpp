
#include <NEO_Screen.h>
#include <NEO_Keyboard.h>
#include "PrimShell.h"
#include <NEO_String.h>

//char controlsalida="0";

void PrimShell::PRIMITIVE::Commandos::Version()
{
	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_VERDE);
	NEO::Screen::ColocarString("\nNeoOS 0.1.0 - PrimShell 0.1.0\n");
}
void PrimShell::PRIMITIVE::Commandos::NotFound()
{
	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_ROJO);
	NEO::Screen::ColocarString("\nCommando NO ENCONTRADO. INTENTELO OTRA VEZ\n");
}
void PrimShell::PRIMITIVE::Commandos::Drakaris()
{
	NEO::Screen::Limpiar(NEO_COLOR_ROJO);
	NEO::Screen::ColocarColor(NEO_SIDE_BACKGROUND,NEO_COLOR_ROJO);
	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_AZUL);
	NEO::Screen::ColocarString("PrimShell v0.1.0\n");
	
	PrimShell::PRIMITIVE::Esperacomando();
}
void PrimShell::PRIMITIVE::Commandos::Creador()
{
	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_VERDE);
	NEO::Screen::ColocarString("\nEL CREADOR ES\n NEOMATRIX\n");
}
int PrimShell::PRIMITIVE::EjecutaString(char* script)
{
	if((NEO::String::Comp("version\n",script))==0)
		PrimShell::PRIMITIVE::Commandos::Version();

	else if ((NEO::String::Comp("creador\n",script))==0)
		PrimShell::PRIMITIVE::Commandos::Creador();

	else if ((NEO::String::Comp("drakaris\n",script))==0)
		PrimShell::PRIMITIVE::Commandos::Drakaris();

	else if ((NEO::String::Comp("exit\n",script))==0)
		NEO::Screen::ColocarString("\nSALIDA\n");
		//controlsalida="1";
	else
		PrimShell::PRIMITIVE::Commandos::Creador();

	//if(NEO::String::Comp("0",controlsalida)==0)
		PrimShell::PRIMITIVE::Esperacomando();
}
int PrimShell::PRIMITIVE::Esperacomando()
{
	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_NEGRO);
	NEO::Screen::ColocarString("PrimShell$");
	char* cmd=NEO::Keyboard::ObtenerString();
	NEO::Screen::ColocarString(cmd);
	PrimShell::PRIMITIVE::EjecutaString(cmd);
	
	
}
int PrimShell::PRIMITIVE::main()
{
	NEO::Screen::Limpiar(NEO_COLOR_BLANCO);
	NEO::Screen::ColocarColor(NEO_SIDE_BACKGROUND,NEO_COLOR_BLANCO);
	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_AZUL);
	NEO::Screen::ColocarString("PrimShell v0.1.0\n");
	
	PrimShell::PRIMITIVE::Esperacomando();

	NEO::Screen::ColocarString("\nADIOS  ... \n");

}

