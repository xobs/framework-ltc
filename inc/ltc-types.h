#ifndef __LTC_TYPES_H
#define __LTC_TYPES_H

typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

typedef uint32_t size_t;

#ifndef __cplusplus
typedef uint8_t bool;
#endif

#ifndef boolean
#define boolean bool
#endif

#ifndef byte
#define byte uint8_t
#endif

#ifndef NULL
#define NULL 0
#endif

/* Arduino-compiatible */
enum analog_reference_type {
  DEFAULT = 0,
  INTERNAL = 1,
  INTERNAL1V1 = 2,
  INTERNAL2V56 = 3,
  EXTERNAL = 4,
};

/* Arduino-compiatible */
enum irq_mode {
  LOW = 0,
  CHANGE = 1,
  RISING = 2,
  FALLING = 3,
  HIGH = 4,
};

/* Arduino-compiatible */
enum pin_mode {
  INPUT = 0,
  OUTPUT = 1,
  INPUT_PULLUP = 2,
  INPUT_PULLDOWN = 3,
  OUTPUT_LOW = 0x21,
};

/* On AVR, there is a special macro to put something in program space.
 * We don't have this distinction, so make an empty macro.
 */
#define PROGMEM

#endif /* __LTC_TYPES_H */
