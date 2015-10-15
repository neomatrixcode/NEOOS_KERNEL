
#include <NEO_Ports.h>
#include <NEO_Types.h>

/**
 *  _port = direccion del puerto
 * */
uint8_t NEO::Ports::InputB(uint16_t _port)
{
	unsigned char rp;
	asm volatile("inb %1, %0"        //lees un byte desde un numero de puerto definido en 2 bytes (inb port, rp) gas
					: "=a"(rp)      //SALIDA DEFINIDA COMO %0 EN GAS (rp es lo leido del puerto contenido en 1 byte )
					: "dN"(_port)); //ENTRADA DEFINIDA COMO %1 EN GAS (numero de puerto)
	return rp;
}
uint16_t NEO::Ports::InputW(uint16_t port)
{
	uint16_t rp;
	asm volatile("inw %1, %0" 	   //lees un byte desde un numero de puerto definido en 2 bytes (inw port, rp) gas
					: "=a"(rp) 	   //SALIDA DEFINIDA COMO %0 EN GAS (rp es lo leido del puerto contenido en 2 byte )
					: "dN"(port)); //ENTRADA DEFINIDA COMO %1 EN GAS (numero de puerto)
	return rp;
}
/**
 * valor = dato de 8 bits a colocar
 * */
void NEO::Ports::OutputB(uint16_t port, uint8_t value)
{
	asm volatile("outb %1, %0" 
					: 
					: "dN"(port), "a"(value));
}
