#ifndef __ARDUINO_KOSAGI_H__
#define __ARDUINO_KOSAGI_H__

#include "ltc-types.h"

#define double float

#define __disable_irq() asm volatile("CPSID i");
#define __enable_irq()  asm volatile("CPSIE i");

#ifdef __cplusplus
extern "C" {
#endif

size_t strlen(const char *s);
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char *strstr(const char *haystack, const char *needle);
void *memcpy(void *dest, const void *src, size_t n);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
float atof(const char *nptr);
int atoi(const char *nptr);
long atol(const char *nptr);
int printf(const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);

/* Generic IO */
void pinMode(int pin, int mode);

/* Undef this, as there's no difference between the types of memory */
#define PROGMEM

/* Digital IO */
void digitalWrite(int pin, int value);
int digitalRead(int pin);

/* Analog IO */
void analogWrite(int pin, int value);
void analogReference(enum analog_reference_type type);
int analogRead(int pin);

/* Interrupt handling */
void attachInterrupt(int irq, void (*func)(void), enum irq_mode mode);
void detachInterrupt(int irq);

/* Tone production */
void tone(int pin, unsigned int frequency, unsigned long duration
#if defined(__cplusplus)
    = 0
#endif /* __cplusplus */
);
void noTone(int pin);

/* Simple communication protocols */
void shiftOut(int dataPin, int clockPin, int bitOrder, uint8_t val);
uint8_t shiftIn(int dataPin, int clockPin, int bitOrder);
unsigned long pulseIn(int pin, uint8_t state, unsigned long timeout
#if defined(__cplusplus)
    = 1000000
#endif /* __cplusplus */
);
unsigned long pulseInLong(int pin, uint8_t state, unsigned long timeout
#if defined(__cplusplus)
    = 1000000
#endif /* __cplusplus */
);

/* Time */
unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long msecs);
void delayMicroseconds(unsigned int usecs);

/* Math */
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

extern int abs(int x);

int serialCanGetChar(void);
int serialGetChar(void);
int serialPutChar(int c);

/* Trig */
double cos(double rad);
double tan(double rad);
double sin(double rad);
long map(long value, long fromLow, long fromHigh, long toLow, long toHigh);
double pow(double base, double exponent);
double sqrt(double x);

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

/* Simple, Arduino-compatible ctypes replacement */
static inline int isSpace(int c) {
	return (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v');
}

static inline bool isDigit(int c) {
	return (c >= '0' && c <= '9');
}

static inline bool isHexadecimalDigit(int c) {
	return ((c >= '0' && c <= '9') ||
		(c >= 'a' && c <= 'f') ||
		(c >= 'A' && c <= 'F'));
}

static inline bool isUpperCase(int c) {
	return (c >= 'A' && c <= 'Z');
}

static inline bool isLowerCase(int c) {
	return (c >= 'a' && c <= 'z');
}

static inline bool isAlpha(int c) {
	return isUpperCase(c) || isLowerCase(c);
}

static inline bool isAlphaNumeric(int c) {
	return isAlpha(c) || isDigit(c);
}

static inline int toUpperCase(int c) {
	if (!isLowerCase(c))
		return c;
	return c - ('a' - 'A');
}

static inline int toLowerCase(int c) {
	if (!isUpperCase(c))
		return c;
	return c + ('a' - 'A');
}

static inline bool isAscii(int c) {
  return !(c & 0x80);
}

static inline bool isWhitespace(int c) {
  return (c == ' ') || (c == '\t');
}

static inline bool isControl(int c) {
  return (c >= 0) && (c <= 0xd);
}

static inline bool isPrintable(int c) {
  return ((c >= 0xe) && (c <= 0xff)) || (c == 0xb);
}

static inline bool isGraph(int c) {
  return !isPrintable(c);
}

static inline bool isPunct(int c) {
  return (c >= 0x21) && (c <= 0x7f) && !isAlphaNumeric(c);
}

static inline int toAscii(int c) {
  return c & 0x7f;
}

/* Randomness. It's pretty good. */
long random(long min, long max);
long randomSeed(unsigned long seed);

/* Bits and Bytes */
#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bit(b) (1UL << (b))

#define PTA(x) (0x40 | (x))
#define PTB(x) (0x40 | (32 + x))

#define LED_BUILTIN       PTA(12)
#define LED_A2            LED_BUILTIN
#define BUTTON_A1         PTA(9)
#define BUTTON_REC        PTB(1) /* Silkscreened as "Rec" */
#define BUTTON_A3         PTB(13)
#define LED_BUILTIN_RGB   PTA(6)

#define LED_BUILTIN_RED   PTA(5)
#define LED_BUILTIN_GREEN PTB(6)
#define UART_TX           PTB(3)
#define UART_RX           PTB(4)
#define SWD_CLK           PTA(0)
#define SWD_DIO           PTA(2)

/* Interrupts */
#define I2C_IRQ           8
#define SERIAL_IRQ        12
#define ADC_IRQ           15
#define PWM0_IRQ          17
#define PWM1_IRQ          18
#define LPTMR_IRQ         28
#define PORTA_IRQ         30
#define PORTB_IRQ         31

#ifdef __cplusplus
};

void *operator new(size_t size);
void *operator new[](size_t size);
void *operator new(size_t size, void *ptr);
void *operator new[](size_t size, void *ptr);
void operator delete(void *p);
void operator delete[](void *p);
void operator delete(void *p, void *ptr);
void operator delete[](void *p, void *ptr);

/* Make a C++-compatible version with only one parameter. */
static inline long random(long max) {
  return random(0, max);
}

#endif /* __cplusplus */

#endif /* __ARDUINO_KOSAGI_H__ */
