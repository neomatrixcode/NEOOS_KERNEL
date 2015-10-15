
#ifndef NEOOS
#endif
#include <NEO_Color.h>
#include <NEO_Screen.h>
#include <NEO_Types.h>
#include <NEO_Error.h>
#include <NEO_GDT.h>
#include <NEO_IDT.h>
#include <NEO_IRQ.h>
#include <NEO_Timer.h>
#include <NEO_Keyboard.h>
#include <NEO_String.h>
#include "PrimShell.h"

#if defined(__cplusplus)
extern "C" 
#endif

int NeoosKernel_Main()
{

NEO::Screen::Limpiar(NEO_COLOR_BLANCO);
NEO::Screen::ColocarColor(NEO_SIDE_BACKGROUND, NEO_COLOR_BLANCO);
NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND, NEO_COLOR_VERDE);
NEO::Screen::ColocarString("\t NEOOS   V 0.1.0\n");
NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND, NEO_COLOR_ROJO);
NEO::Screen::ColocarString("\t DESARROLLADO POR NEOMATRIX\n");

//NEO::Error::Mostrar("CODIGO DE EROOR 5");
NEO::GDT::Install();
NEO::IDT::Install();
NEO::IRQ::Install();
NEO::Timer::Install();
NEO::Keyboard::Install();

asm volatile("sti"); //activa las interrucciones

NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND, NEO_COLOR_VERDE);
NEO::Screen::ColocarString("\t\n\n\n Bienvenido\n\n\n\n$ ");

NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND, NEO_COLOR_ROJO);
char* cmd=NEO::Keyboard::ObtenerString();
NEO::Screen::ColocarString(cmd);
//if(NEO::String::Comp("primitive\n",cmd)==0)
PrimShell::PRIMITIVE::main();

//NEO::Screen::ColocarString("$");

//int ej= 10/0;

return 0;

}
