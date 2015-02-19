#ifndef ARGUMENTINTERCEPTOR_H
#define ARGUMENTINTERCEPTOR_H

#include <cstring>
#include <iostream>

#include "pin++/Callback.h"
#include "pin.H"

#ifdef __x86_64__
static uintptr_t platformOffset = 0x48;
static uintptr_t diff = 0x4;
#endif
#ifdef __i386__
static uintptr_t platformOffset = 0x38;
static uintptr_t diff = 0x4;
#endif

int32_t getArgCount(ADDRINT stackptr);

class ArgumentInterceptor : public OASIS::Pin::
  Callback<ArgumentInterceptor(OASIS::Pin::ARG_REG_VALUE)> {
public:
  ArgumentInterceptor() {};
  void handle_analyze(ADDRINT stackptr);
};

#endif //ARGUMENTINTERCEPTOR_H
