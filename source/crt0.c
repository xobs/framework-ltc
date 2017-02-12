/*
The MIT License (MIT)

Copyright (c) 2017 Sean Cross

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/
#include <stdlib.h>
#include <stdint.h>
#include "app.h"

void abort(void) {
  while(1);
}

int abs(int x) {
  return (x > 0) ? x : -x;
}

void raise(void) {
  while(1);
}

/* handle for C++ destructors, which we don't use. */
uint32_t __dso_handle = 0;

/* Variables provided by the linker */
extern uint32_t _textdata;
extern uint32_t _data;
extern uint32_t _edata;
extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern uint32_t __init_array_start;
extern uint32_t __init_array_end;
extern uint32_t __heap_base__;
extern uint32_t __heap_end__;

/* Our main function, to be declared elsewhere */
extern int main(int argc, const char **argv);

__attribute((noreturn, naked))
void _start(void) {
  static const char *args[] = {""};
  main(0, args);
  while (1);
}

__attribute__ ((used, section(".progheader")))
struct app_header app_header = {
  .data_load_start  = &_textdata,
  .data_start       = &_data,
  .data_end         = &_edata,
  .bss_start        = &_bss_start,
  .bss_end          = &_bss_end,
  .entry            = _start,
  .magic            = APP_MAGIC,
  .version          = APP_VERSION,
  .const_start      = &__init_array_start,
  .const_end        = &__init_array_end,
  .heap_start       = &__heap_base__,
  .heap_end         = &__heap_end__,
};
