//Definimos nombres para los pines y prototipos 
#ifndef __LCD_H_
#define	__LCD_H_
#include <xc.h>  
#include <stdint.h>

#ifndef Reset
#define Reset RE0
#endif
#ifndef Enable
#define Enable RE1
#endif
#ifndef D0
#define D0 RD0
#endif
#ifndef D1
#define D1 RD1
#endif
#ifndef D2
#define D2 RD2
#endif
#ifndef D3
#define D3 RD3
#endif
#ifndef D4
#define D4 RD4
#endif
#ifndef D5
#define D5 RD5
#endif
#ifndef D6
#define D6 RD6
#endif
#ifndef D7
#define D7 RD7
#endif

void LCD_Init(void);
void LCD_Caracter(char a);
void LCD_Comandos(uint8_t x);
void Pines(uint8_t x);
void LCD_clear(void);
void LCD_Cursor(uint8_t x,uint8_t y);
void LCD_Texto(char *a);
#endif
