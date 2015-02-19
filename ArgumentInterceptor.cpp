#include "ArgumentInterceptor.h"

int32_t getArgCount(ADDRINT stackptr) {
  int32_t argc=0;
  PIN_SafeCopy(&argc, (const char *)((stackptr + platformOffset-diff)), sizeof(uint32_t));
  return argc;
}

void ArgumentInterceptor::handle_analyze(ADDRINT stackptr) {
    uintptr_t * ptr, *argv;
    auto argc=getArgCount(stackptr);
    cout << "stackptr: " << hex << stackptr << endl;
  
    cout << "retrieved argc val: " << dec << argc << hex << " " << argc << endl;
    //retrieve the pointer to &argv
    PIN_SafeCopy(&argv, (const char *)((stackptr + platformOffset)), sizeof(uintptr_t));
    for (unsigned int i=0;i<argc;i++) {
      //retrieve the pointer to argv[i] (word size offset to be clear)
      PIN_SafeCopy(&ptr, (VOID *)(argv + i) , sizeof(uintptr_t));
      int len =  (strchr((char *) (ptr), 0)) - (char *)ptr;
      char mainargs[len+1];
      //use this pointer to read the actual cmdline arg
      PIN_SafeCopy(mainargs, (VOID *) ptr, len);
      mainargs[len]=0;
      cout << "argv[" << i <<"]: " <<
      mainargs << " len: " << dec << len << " addr: " << hex << ptr << endl;
      cout.flush();
    }
  }
