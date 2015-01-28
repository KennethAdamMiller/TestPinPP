#ifndef ARGUMENTINTERCEPTOR_H
#define ARGUMENTINTERCEPTOR_H

#include <cstring>
#include <iostream>

#include "pin++/Callback.h"
#include "pin.H"

class ArgumentInterceptor : public OASIS::Pin::
  Callback<ArgumentInterceptor(OASIS::Pin::ARG_REG_VALUE)> {
public:
  ArgumentInterceptor() {};
  void handle_analyze(ADDRINT stackptr);
};

#endif //ARGUMENTINTERCEPTOR_H
