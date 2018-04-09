//#include "project1.h"
#include "project2.h"
#include "Homework_4.h"

//#define PROJECT1
//#define PROJECT2
#define PROJECT3
//#define HOMEWORK4

int main(void) {
#ifdef PROJECT1
	project();
#endif

#ifdef PROJECT2
  project2();
#endif

#ifdef PROJECT3
  project3();
#endif

#ifdef HOMEWORK4;
  homework4();
#endif
}
