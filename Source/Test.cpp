#include "Test.h"

void TLMP::test0_pre STDARG
{
  log("[TEST 0 PRE] %p %#x %#x %#x %#x", e->_this, Pz[0], Pz[1], Pz[2], Pz[3]);

  if (NetworkState::getSingleton().GetState() == CLIENT && !ClientAllowSpawn) {
    log("[CLIENT] Stopping spawn");
    e->calloriginal = false;
    e->retval = 0;
  }
}

void TLMP::test0_post STDARG
{
  log("[TEST 0 POST]");
}

void TLMP::test1_pre STDARG
{
  wstring &s1 = *(wstring*)&Pz[0];
  wstring &s2 = *(wstring*)&Pz[1];

  log("[TEST 1 PRE]: %p %ls %ls %i %i", e->_this, s1.c_str(), s2.c_str(), Pz[2], Pz[3]);
}

void TLMP::test1_post STDARG
{
  log("[TEST 0 POST]");
}