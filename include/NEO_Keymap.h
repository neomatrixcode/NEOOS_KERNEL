
#ifndef NEO_KEYMAP_H
#define NEO_KEYMAP_H

unsigned char mapateclas[128] =
{
   0,  27, '1', '2', '3', '4', '5', '6', '7', '8','9', '0', '\'', '?', '\b',	/* Retroceso */
  '\t','q', 'w', 'e', 'r','t', 'y', 'u', 'i', 'o', 'p', '0', '+', '\n',	/* Tecla Enter */
    0,/* 29   - mayus*/'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'N','{', '|',  
  0,/* Shift izquierdo */'}', 'z', 'x', 'c', 'v', 'b', 'n','m', ',', '.', '-',  0,/* Shift derecho */
  '*',
    0,	/* Alt */
  ' ',	/* Barra espaciadora */
    0,	/* Bloq. Mayús/Caps lock */
    0,	/* 59 - tecla F1 ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Bloq. Num/Num lock*/
    0,	/* Bloq. Despl/Scroll Lock */
    0,	/* Tecla Inicio/Home */
    0,	/* Flecha Arriba */
    0,	/* Re Pág/Page Up */
  '/',
    '\b',	/* Flecha Izquierda */
    0,
    ' ',	/* Flecha Derecha */
  '+',
    0,	/* 79 - Tecla Fin/End*/
    0,	/* Tecla Abajo */
    0,	/* Av Pág/Page Down */
    0,	/* Tecla Insert */
    0,	/* Tecla Supr/Delete */
    0,   0,   0,
    0,	/* Tecla F11 */
    0,	/* Tecla F12 */
    0,	/* Todas las demás teclas son indefinidas */
};



#endif
