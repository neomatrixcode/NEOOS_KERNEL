
 
#include <NEO_Timer.h>
#include <NEO_Ports.h>
#include <NEO_Screen.h>
#include <NEO_IDT.h>
#include <NEO_ISR.h>
#include <NEO_IRQ.h>

/*el timer está configurado para generar un IRQ 0 18.222 veces por segundo. 
Es el BIOS IBM de la PC/AT la que lo configura así por defecto. 
esta tasa de tics de 18.222 Hz se utilizó para que la cuenta de ciclos estuviera 
en 0.055 segundos. Usando un contador de tics de 16 bits, el contador se desbordará 
y regresará a 0 una vez cada hora eso o es por efecto de andar fumando hierbas
Para llevar el control del tiempo preciso y fácil, recomiendo configurarlo a 100 Hz en un kernel real.*/

int TIMER_TICKS=0;

void NEO::Timer::Fase(int hz)
{
	/* debemos usar nuestra función outportB para escribir a los puertos de Entrada/Salida.
	  Hay un registro de Datos para cada uno de los canales en:
	  0x40 (interrumpe el CPU en tiempos predecibles y regulares.),
	  0x41 ( específico al sistema) 
	  y 0x42 (conectado a la bocina del sistema)
	  y un registro de Comandos en 0x43.*/

	int divisor=1193180/hz;                    /* Calcular nuestro divisor 1193180 hz es el valor dela frecuencia del temporidor */
	NEO::Ports::OutputB(0x43,0x36); //0x36=00110110 /* Establecer nuestro byte de comando 0x36 
													//contador0, lsb msb, mododeondacuadrada, contadorde16 bits*/
	NEO::Ports::OutputB(0x40, divisor & 0xFF); /* Establecer el byte bajo del divisor */
	NEO::Ports::OutputB(0x40, divisor >> 8);   /* Establecer el byte alto del divisor */
}

/*BYTE DE COMANDO
7-6: CNTR - No. Contador (0-2)
5-4: RW - Modo de Lectura/Escritura (1 = LSB, 2 = MSB, 3 = LSB luego MSB)
3-1: Modo - Ver la tabla de ABAJO
0: BCD - (0 = contador de 16-bit, 1 = contadores de década 4x BCD) 

Modo	Descripción
0	Interrupción en Cuenta Terminal
Interrupt on terminal count
1	Hardware Regatillable en Un Disparo
Hardware Retriggerable one shot
2	Generador de Tasa
Rate Generator
3	Modo de Onda Cuadrada
Square Wave Mode
4	Estroboscópica de Software
Software Strobe
5	Estroboscópica de Hardware
Hardware Strobe

*/

/* Esto estará continuamente en un bucle hasta que el tiempo
*  indicado haya sido alcanzado */
void NEO::Timer::Espera(int ticks)
{
	unsigned long eticks;
	eticks=TIMER_TICKS+ticks;
	while(TIMER_TICKS < eticks)
	{
		
	}
}


/* Configura el reloj de sistema al instalar el manejador del timer
*  en el IRQ 0 */
void NEO::Timer::Install()
{
	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND, NEO_COLOR_NEGRO);
	NEO::Screen::ColocarString("\nConfigurando timer...");
	
	NEO::Timer::Fase(100);   //recomendable
	NEO_IRQ_InstallHandler(0,&NEO_Timer_Handler);


	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_VERDE);
	NEO::Screen::ColocarString("done");
}


/* Maneja el timer. En este caso, es muy simple:
*  Incrementamos la variable 'timer_ticks' cada vez
*  que el timer se dispara. Por defecto, el timer
*  se dispara 18.222 veces por segundo. */


extern "C"
void NEO_Timer_Handler(struct regs* r)
{
	TIMER_TICKS++;

	/* Cada 18 ciclos de reloj (aproximadamente 1 segundo),
    *  mostraremos un mensaje en la pantalla */
	//if(TIMER_TICKS % 18 ==0) //a modo de ejemplo
	if(TIMER_TICKS % 100 == 0) //recomendable para un kernel real
	{
		//NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND, NEO_COLOR_CAFE);
		//NEO::Screen::ColocarString("\n TIC TAC..");
	}
}
