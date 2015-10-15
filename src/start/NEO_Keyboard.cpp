
#include <NEO_Keyboard.h>
#include <NEO_Keymap.h>
#include <NEO_Ports.h>
#include <NEO_Screen.h>
#include <NEO_IRQ.h>

#define MAX_STRING_SIZE 1024

unsigned int tmp;
char stringBuffer[MAX_STRING_SIZE];
unsigned int stringPos=0;

void NEO::Keyboard::Install()
{
	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND, NEO_COLOR_NEGRO);
	NEO::Screen::ColocarString("\nInstalando Keyboard...");

	NEO_IRQ_InstallHandler(1,&NEO_Keyboard_Handler);

	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_VERDE);
	NEO::Screen::ColocarString("done");
	tmp = 1;
}
void NEO::Keyboard::Espera()
{

}

/*El teclado se conecta a la computadora a través de un chip microcontrolador especial en la tarjeta madre. 
Este chip controlador de teclado tiene 2 canales: Uno para el teclado, y otro para el ratón. 
También, través de este chip controlador de teclado se activa la línea de direcciones A20 en el procesador, 
para permitir el acceso a memoria más allá de la marca de 1 MB (GRUB la activa, así que no necesitas 
preocuparte de eso). El controlador del teclado, siendo un dispositivo accesible por el sistema,
 tiene una dirección en el bus de Entrada/Salida que podemos usar para acceso y control. 
 El controlador de teclado tiene 2 registros principales: Un registro de Datos en 0x60, 
 y un registro de Control en 0x64. 
 Cualquier cosa que el teclado desee enviarle a la computadora, se almacena en el registro de Datos. 
 El teclado generará el IRQ 1 siempre que tenga datos para que nosotros los leamos. */



unsigned char NEO::Keyboard::ObtenerChar()
{
	unsigned char codigo;
	codigo=(unsigned char)NEO::Ports::InputB(0x60);  //0x60 almacena la ultima tecla presionada
		
	// Si el bit de mayor peso del byte que leímos del teclado está
    //  activado, eso significa que se acaba de soltar una tecla 
	if(codigo & NEO_CLAVE_DE_LIBERACION_TECLA)  
	{
		//return 255;
		 /* se pude usar esto para ver si el usuario soltó las teclas
        *  Shift, Alt, o Control etc */

	}else{

		 // Aquí, una tecla acaba de apretarse. si se  mantiene una tecla apretada, 
		 //se obtendran interrupciones repetidas para la tecla  apretada.

        //se pasa el codigo obtenido del teclado a un valor del codigo ascii
        //se pueden usar banderas para reconocer si se preionaron teclas especilaes
        //o se pueden agregar otras 128 entradas que serai la de shift+otra_tecla


		return mapateclas[codigo];
	}
}
char* NEO::Keyboard::ObtenerString()
{
	
	if(stringBuffer[1]!='\0')
	{
		int c = 0;
	while (c<=MAX_STRING_SIZE)
	{
		stringBuffer[c]='\0';
		c++;
	}

	}	

	

	while(stringBuffer[stringPos-1]!='\n')
	{
		
	}
	

	stringPos=0;

	
	return stringBuffer;
}

extern "C"
void NEO_Keyboard_Handler(struct regs* r)
{
    unsigned char codigo = NEO::Keyboard::ObtenerChar();
    
	NEO::Screen::ColocarChar(codigo);
	stringBuffer[stringPos]=codigo;
	stringPos++;
	
}



//Para manipular las luces del teclado, debes enviarle un comando al controlador del teclado. 
/*Hay un procedimiento específico para enviarle un comando al teclado. 
Primero debes esperar que el controlador del teclado te indique que no está ocupado.
 Para hacer esto, lees del registro de Control (cuando lo lees, se le llama registro de Estado) 
 en un bucle, saliendo de este cuando el teclado no esté ocupado:

if ((inportb(0x64) & 2) == 0) break; 

Después de ese bucle, puedes escribir el byte del comando al registro de Datos. 
No escribas el registro de Control en cuestión, excepto en casos especiales. 
Para configurar las luces del teclado, primero envías el byte de comando 0xED usando el método descrito, 
luego envías el byte que dice qué luces deben estar encendidas o apagadas. 
Este byte tiene el siguiente formato:

Bit 0: Scroll Lock/Bloq Despl
Bit 1: Num Lock/Bloq Num
Bit 2: Caps Lock/Bloq Mayús

Ahora que tienes el soporte básico para el teclado, puedes desear expandir este código. 

se puede usar el controlador del teclado para activar y manejar el puerto del ratón PS/2. */
