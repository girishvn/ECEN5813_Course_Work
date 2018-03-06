#include "project1.h"
#include "project2.h"
//#define PROJECT2

int main(void) {
#ifdef PROJECT1
  project1();
#endif

#ifdef PROJECT2
  project2();
#endif
}
