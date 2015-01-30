#ifndef MEMORYDUMPER_H
#define MEMORYDUMPER_H

#include <iostream>
#include "pin++/Context.h"
#include "pin++/Callback.h"

class PrintRegs : public OASIS::Pin::
  Callback<PrintRegs(OASIS::Pin::ARG_CONTEXT)> {
public:

  void handle_analyze(const OASIS::Pin::Context &ctx) {
    std::cout << "REG:" << "RAX" << ": " << 
      ctx.get_reg(REG_RAX) <<
      std::endl;
    exit(EXIT_SUCCESS);
  }
};

#endif  //MEMORYDUMPER_H
