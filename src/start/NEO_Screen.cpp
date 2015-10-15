#include <NEO_Types.h>
#include <NEO_Color.h>
#include <NEO_Screen.h>
#include <NEO_Ports.h>

uint16_t *memvid= (uint16_t *)0xB8000;    //0xB8000 ES LA DIRECCION EN A MEMORIA FISICA DEL BUFER DE VIDEO 
										  //DE AQUI EN ADELANTE COMAZAREMOS A ESCRIBIR (0-7BIT)COLORCARACTER
										  //(8-11)COLORFRENTE, (12-15)COLORFONDO 
NEO_Color colordefondo = NEO_COLOR_NEGRO;
NEO_Color colordetexto = NEO_COLOR_BLANCO;
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

static void UpdateCursor()
{
   //EL CONTROLADOR VGA NOS MUESTRA UNA MATRIX DE 80x25
   uint16_t posisioncursor = cursor_y * 80 + cursor_x;
   NEO::Ports::OutputB(0x3D4, 0x0E); //0x3D4 puerto vga a CTR CONTROLLER , el 14 es el registro a modificar             
   NEO::Ports::OutputB(0x3D5, posisioncursor >> 8); //posisioncursor >> 8 es el dato a escribir en el registro 14 del puerto 0x3D4
   													//por convencion cundo se pasan los datos se hacen la numpuerto+1
   	//3d4h index 0Ch (W):  CRTC: Start Address High Register
	//bit 0-7  Upper 8 bits of the start address of the display buffer

	//3d4h index 0Dh (W):  CRTC: Start Address Low Register
	//bit 0-7  Lower 8 bits of the start address of the display buffer

   	//3d4h index 0Eh (W):  CRTC: Cursor Location High Register
	//bit 0-7  Upper 8 bits of the address of the cursor

	//3d4h index 0Fh (W):  CRTC: Cursor Location Low Register
	//bit 0-7  Lower 8 bits of the address of the cursor

   NEO::Ports::OutputB(0x3D4, 0x0F);                  
   NEO::Ports::OutputB(0x3D5, posisioncursor);      

//-Attribute Controller (puerto 0x3c0): 
 //es el controlador de atributos, relacionado con todos los temas de colores, atributos, etc, accediéndose por el puerto 3c0h.

//-VGA Sequencer (puerto 0x3c4):
//es el secuenciador de la VGA y gestiona sus funciones más críticas e importantes (reseteo de la tarjeta, generador de carácteres, etc).

//Graphics Controller (puerto 0x3c3):
//es el controlador gráfico de la VGA, dando acceso a la lectura de planos, reseteo de registros, etc.

//- Cathode Ray Tube Controller (puerto 0x3d4): 
//maneja todos los datos referentes al tubo de rayos catódicos que refresca o redibuja la pantalla, en un sistema asociado al monitor.

//-El SVGA Controller (puerto 0x???):
//podemos considerar que estará presente en las tarjetas SuperVGA, conteniendo los registros extendidos para este tipo de tarjetas.
//Su puerto de acceso varía según el fabricante de la tarjeta, de ahí los problemas de compatibilidad en la programación de estas tarjetas.


}


NEO_Color NEO::Screen::ObtenerColor(NEO_SIDE side)
{
	if(side==NEO_SIDE_BACKGROUND){
		return colordefondo;
	}else{
		return colordetexto;
	}
}

void NEO::Screen::ColocarColor(NEO_SIDE side, NEO_Color colour)
{
	if(side==NEO_SIDE_BACKGROUND)
	{
		colordefondo=colour;
	}else{
		colordetexto=colour;
	}
}

void NEO::Screen::ColocarChar(char c)
{
	uint8_t  attributeByte = (colordefondo << 4) | (colordetexto & 0x0F);
	uint16_t attribute = attributeByte << 8;
	uint16_t *localizacion;
	if (c == 0x08 && cursor_x)
	{
		cursor_x--;
	}else if(c == '\r')
	{
		cursor_x=0;
	}else if(c == '\n')
	{
		cursor_x=0;
		cursor_y++;
	}
	if(c >= ' ') 
	{
		localizacion = memvid + (cursor_y*80 + cursor_x);
		*localizacion = c | attribute;
		cursor_x++;
	}
	if(cursor_x >= 80) 
	{
		cursor_x = 0;
		cursor_y++;
	}

	
	//funcion de scroll

	uint8_t attributeByte2 = (0 /*negro*/ << 4) | (15 /*blanco*/ & 0x0F);
	uint16_t blank = 0x20 /* espacio */ | (attributeByte2 << 8);
	if(cursor_y >= 25)
	{
       int i;
       for (i = 0*80; i < 24*80; i++)
       {
           memvid[i] = memvid[i+80];
       }

      
       for (i = 24*80; i < 25*80; i++)
       {
           memvid[i] = blank;
       }
       
       cursor_y = 24;
   }
	
	UpdateCursor();
}

void NEO::Screen::ColocarString(const char* str)
{
	int i=0;
	while(str[i]) 
	{
		NEO::Screen::ColocarChar(str[i++]);
	}
}

 void NEO::Screen::Limpiar(NEO_Color colour)
{
   
   uint8_t attributeByte = (colour /*este es el fonfoo*/ << 4) | (15 /*letras*/ & 0x0F);
   uint16_t blank = 0x20 /* inroduce un espacio */ | (attributeByte << 8);

   int i;
   for (i = 0; i < 80*25; i++)
   {
       memvid[i] = blank;
   }

 
   cursor_x = 0;
   cursor_y = 0;
   
   UpdateCursor();
}

void NEO::Screen::ColocarCursor(uint8_t x, uint8_t y)
{
	cursor_x=x;
	cursor_y=y;
	
	UpdateCursor();
}

