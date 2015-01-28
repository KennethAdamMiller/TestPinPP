#include "ArgumentInterceptor.h"

using namespace std;

#ifdef __x86_64__
static uintptr_t platformOffset = 0x48;
static uintptr_t diff = 0x4;
#endif
#ifdef __i386__
static uintptr_t platformOffset = 0x38;
static uintptr_t diff = 0x4;
#endif

uint32_t getArgCount(ADDRINT stackptr) {
  uint32_t argc;
  PIN_SafeCopy(&argc, (const char *)((stackptr + platformOffset-diff)), 1);
  return argc;
}

void ArgumentInterceptor::handle_analyze(ADDRINT stackptr) {
  uintptr_t * ptr, *argv;
  uint32_t argc=getArgCount(stackptr);
  cout << "stackptr: " << hex << stackptr << endl;

  cout << "retrieved argc val: " << argc << endl;
  //retrieve the pointer to &argv
  PIN_SafeCopy(&argv, (const char *)((stackptr + platformOffset)), sizeof(uintptr_t));
  for (unsigned int i=0;i<argc;i++) {
    //retrieve the pointer to argv[i] (word size offset to be clear)
    PIN_SafeCopy(&ptr, (VOID *)(argv + i) , sizeof(uintptr_t));
    int len =  (strchr((char *) (ptr), 0)) - (char *)ptr;
    char mainargs[len];
    //use this pointer to read the actual cmdline arg
    PIN_SafeCopy(mainargs, (VOID *) ptr, len);
    cout << "argv[" << i <<"]: " <<
mainargs << " len: " << dec << len << " addr: " << hex << ptr << endl;
    cout.flush();
  }
}
