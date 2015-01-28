#include "ArgumentInterceptor.h"
#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"
#include <cxxabi.h>

bool compareFunction(const string mangled, const char * funcName) {
  int status;
  if (!strcmp(mangled.c_str(), funcName))
    return true;
  char *realname = abi::__cxa_demangle(mangled.c_str(), 0, 0, &status);
  if (!realname)
    return false;
  return strcmp(realname, funcName);
}

class Image : public OASIS::Pin::Image_Instrument<Image> {
  ArgumentInterceptor argInterceptor;
public:
  void handle_instrument(const OASIS::Pin::Image &img) {    
    for (OASIS::Pin::Section sec : img) {
      for (OASIS::Pin::Routine rtn : sec) {
	OASIS::Pin::Routine_Guard rg(rtn);
        if (compareFunction
	    (PIN_UndecorateSymbolName(rtn.name(), UNDECORATION_NAME_ONLY), "_init") or
	    compareFunction
	    (PIN_UndecorateSymbolName(rtn.name(), UNDECORATION_NAME_ONLY), "init")) {
	  this->argInterceptor.insert(IPOINT_BEFORE, rtn, REG_STACK_PTR);
          std::cout << rtn.name() << std::endl;
	}
      }
    }
  }
};

class Tool : public OASIS::Pin::Tool<Tool> {
  Image img;
public:
  Tool() {
    this->init_symbols();
  }
};


DECLARE_PINTOOL(Tool);
