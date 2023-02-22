/*
  HD44780 + 74HC595
*/

#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "stm32f0xx_hal.h"

#ifdef __cplusplus
	extern "C" {
#endif

#define DEC 10
#define HEX 16
#define OCT 8

#define pgm_read_byte(addr) (*(const int32_t *)(addr))

#define LCD_DISPLAYCONTROL 0x08
#define LCD_SETCGRAMADDR 0x40
#define LCD_CURSORON 0x02

//GPIOB->CRH &=  ~ ( 0b1111 << 16 ); // сбрасываем биты 16-19
//GPIOB->CRH |= 0b1000 << 16;  // устанавливаем биты

#define LCD_DATA_PIN_SET(state) (HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, state))
#define LCD_CLK_PIN_SET(state) (HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, state))
#define LCD_EN_PIN_SET(state) (HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, state))
#define STRUB_EN_PIN LCD_EN_PIN_SET(GPIO_PIN_SET); LCD_EN_PIN_SET(GPIO_PIN_RESET);
#define STRUB_CLK_PIN LCD_CLK_PIN_SET(GPIO_PIN_SET); LCD_CLK_PIN_SET(GPIO_PIN_RESET);

class LCD
{
  public:
    void init();
    void createChar(uint8_t location, uint8_t charmap[]);
    void print(const char *str);
    void print(char);
    void print(unsigned char, int);
    void print(int);
    void print(long, int);
    void print(unsigned long);
    void printNumber(unsigned long, int);
    void cursor();
    void noCursor();
    void setCursor(uint8_t col, uint8_t row);
    void clear();
    void blanks();
  private:
    void send (uint8_t value, uint8_t mode);
    void command (uint8_t value);
    void write (uint8_t value);

    uint8_t _displaycontrol = 0x0C;
};

#ifdef __cplusplus
  }
#endif

#endif
