
#include <NEO_GDT.h>
#include <NEO_Screen.h>

/* Nuestra GDT, con 3 entradas, y finalmente nuestro puntero especial para la GDT */
struct NEO::GDT::Entry gdt[3];
struct NEO::GDT::Ptr gp;

//extern void gdt_flush(); //busca la funcion flush en un archivo externo

static void gdt_flush()  //REGARGA LOS REGISTROS DE SEGMENTO PARA QUE APUNTEN A ESTAS DIRECCIONES
{
	asm volatile("lgdtl (gp)"); // Carga la GDT con nuestro '_gp' que es un puntero especial

	asm volatile(
		"movw $0x10, %ax \n" // 0x10 es el desplazamiento en la GDT a nuestro segmento de datos
		"movw %ax, %ds \n"
		"movw %ax, %es \n"
		"movw %ax, %fs \n"
		"movw %ax, %gs \n"
		"movw %ax, %ss \n"
		"ljmp $0x08, $next \n" //0x08 es el desplazamiento a nuestro segmento de código: ¡Salto lejano! (LJMP)
		"next:          \n"
	);
}

/* Configurar un descriptor en la Tabla de Descriptores Globales */
void NEO::GDT::SetGate(int num, uint32_t base, uint32_t limit, uint8_t access,uint8_t gran)
{
	 /* Configurar la dirección base del descriptor */
	gdt[num].base_low=(base & 0xFFFF);
	gdt[num].base_middle=(base >> 16) & 0xFF;
	gdt[num].base_high=(base >> 24) & 0xFF;
	

    /* Configurar los límites del decriptor */
	gdt[num].limit_low=(limit & 0xFFFF);
	gdt[num].granularity=(limit >> 16) & 0x0F;
	
	/* Finalmente, configura la granularidad y los bits de banderas de acceso */
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access=access;
}

/*configurará las 3 primeras entradas en la GDT, y luego,
 *  finalmente, llamará a gdt_flush() en nuestro archivo de ensamblador
 *  para decirle al procesador dónde está la nueva GDT y actualizar los
 *  nuevos registros de segmento */

void NEO::GDT::Install()
{
	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_NEGRO);
	NEO::Screen::ColocarString("Installing GDT...");

	/* Configurar el puntero y límite de la GDT */
	gp.limit=(sizeof(struct NEO::GDT::Entry)*3)-1;
	gp.base=(uint32_t)&gdt;
	
	NEO::GDT::SetGate(0,0,0,0,0);  /* Nuestro descriptor NULO como  mecanismo de protección del procesador */


	/* La segunda entrada es 
	  La dirección base es 0, límite es 4 GBytes,anillo 0 sistema , descriptor de Segmento de Código
	  y usa granularidad de 4 KBytes, TAMAÑO DE OPERADOR DE 32 BITS, disponible para el sistema
     */

	NEO::GDT::SetGate(1,0,0xFFFFFFFF,0x9A,0xCF);    //acceso 0x9A = 10011010   granularidad 0xCF = 11001111
	
	NEO::GDT::SetGate(2,0,0xFFFFFFFF,0x92,0xCF);    //acceso 0x92 = 10010010   granularidad 0xCF = 11001111
	
	gdt_flush();
	
	NEO::Screen::ColocarColor(NEO_SIDE_FOREGROUND,NEO_COLOR_VERDE);
	NEO::Screen::ColocarString("done");
}
