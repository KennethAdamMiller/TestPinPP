#include "PrintRegs.h"
#include "pin++/Pintool.h"
#include "pin++/Image_Instrument.h"

class Image : public OASIS::Pin::
  Image_Instrument<Image> {
  PrintRegs reg_printer;
public:
  void handle_instrument(const OASIS::Pin::Image &img) {
    if (!img.is_main_executable())
      return;
    IMG image = (IMG)img;
    for (SEC sec = IMG_SecHead(image); SEC_Valid(sec); sec = SEC_Next(sec))
      for (RTN rtn = SEC_RtnHead(sec); RTN_Valid(rtn); rtn = RTN_Next(rtn)) {
	OASIS::Pin::Routine routine(rtn);
	OASIS::Pin::Routine_Guard rg(routine);
	if (RTN_Name(rtn)=="_init") {
	  reg_printer.insert(IPOINT_BEFORE, routine);
	}
      }
  }
};

class Tool : OASIS::Pin::Tool<Tool> {
  Image img;
public:
  Tool() {
    this->init_symbols();
  }
};

DECLARE_PINTOOL(Tool);
