/**
 * @file unit_tests.c
 * @brief
 *
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "memory.h"

/* MEMORY TESTS */
/* MEM MOVE */
static void memMvTstInvldPtr(void **state)
{
  uint8_t tmpSrc;
  uint8_t tmpDst;

  uint8_t * srcPtr;
  uint8_t * dstPtr;
  size_t length = 10;

  srcPtr = NULL; /* NULL ptr src */
  dstPtr = &tmpDst;
  assert_true(my_memmove(srcPtr,dstPtr,length) == NULL);

  srcPtr = &tmpSrc;
  dstPtr = NULL; /* NULL ptr dst */
  assert_true(my_memmove(srcPtr,dstPtr,length) == NULL);

  return;
}

static void memMvTstNoOvrlp(void **state) {
    uint8_t memBuff[20];

    uint8_t * srcPtr;
    uint8_t * dstPtr;
    size_t length = 10;

    int i;
    for(i = 0; i < (int)length; i++)
    {
      memBuff[i] = i; /* buff contains values 0 - 9 */
    }

    srcPtr = &memBuff[0];
    dstPtr = &memBuff[10];

    assert_true(my_memmove(srcPtr,dstPtr,length) == dstPtr); /* assert pointer to dst returned */
    assert_memory_equal(srcPtr,dstPtr,length*sizeof(uint8_t)); /* assert memory moved properly */

    return;
}

static void memMvTstSrcOvrlpDst(void **state)
{
  uint8_t memBuff[20];
  uint8_t correctMem[10] = {0,1,2,3,4,5,6,7,8,9};

  uint8_t * srcPtr;
  uint8_t * dstPtr;
  size_t length = 10;

  int i;
  for(i = 0; i < (int)length; i++)
  {
    memBuff[i] = i; /* buff contains values 0 - 9 */
  }

  srcPtr = &memBuff[0];
  dstPtr = &memBuff[5];

  assert_true(my_memmove(srcPtr,dstPtr,length) == dstPtr); /* assert pointer to dst returned */
  assert_memory_equal(dstPtr,correctMem,length*sizeof(uint8_t)); /* asssert memory moved properly */

  return;
}

static void memMvTstDstOvrlpSrc(void **state)
{
  uint8_t memBuff[20];
  uint8_t correctMem[10] = {0,1,2,3,4,5,6,7,8,9};

  uint8_t * srcPtr;
  uint8_t * dstPtr;
  size_t length = 10;

  int i;
  for(i = 5; i < 5 + (int)length; i++)
  {
    memBuff[i] = i - 5; /* buff contains values 0 - 9 */
  }

  dstPtr = &memBuff[0];
  srcPtr = &memBuff[5];

  assert_true(my_memmove(srcPtr,dstPtr,length) == dstPtr); /* assert pointer to dst returned */
  assert_memory_equal(dstPtr,correctMem,length*sizeof(uint8_t)); /* asssert memory moved properly */

  return;
}

static void memMvTstDstEqSrc(void **state)
{
  uint8_t memBuff[20];

  uint8_t * srcPtr;
  uint8_t * dstPtr;
  size_t length = 10;

  int i;
  for(i = 0; i < (int)length; i++)
  {
    memBuff[i] = i; /* buff contains values 0 - 9 */
  }

  dstPtr = &memBuff[0]; /* same location for dst and src */
  srcPtr = &memBuff[0];

  assert_true(my_memmove(srcPtr,dstPtr,length) == dstPtr); /* assert pointer to dst returned */
  assert_memory_equal(dstPtr,srcPtr,length*sizeof(uint8_t)); /* asssert memory moved properly */

  return;
}

/* MEM SET */
static void memSetTstInvldPtr(void **state)
{
  uint8_t * srcPtr = NULL; /* NULL ptr src */
  size_t length = 10;
  uint8_t val = 0x01;

  assert_true(my_memmove(srcPtr,length,val) == NULL); /* NULL pointer access */

  return;
}

static void memSetTstSetVal(void **state)
{
  uint8_t * srcPtr = NULL; /* NULL ptr src */
  size_t length = 10;
  uint8_t val = 0x01;
  uint8_t correctMem[10] = {1,1,1,1,1,1,1,1,1,1};

  assert_true(my_memmove(srcPtr,length,val) == srcPtr); /* Good pointer access */
  assert_memory_equal(srcPtr,correctMem,length*sizeof(uint8_t)); /* check value set */

  return;
}

/* MEM ZERO */
static void memZeroTstInvldPtr(void **state)
{
  uint8_t * srcPtr = NULL; /* NULL ptr src */
  size_t length = 10;

  assert_true(my_memmove(srcPtr,length) == NULL); /* NULL pointer access */

  return;
}

static void memZeroTstSetVal(void **state)
{
  uint8_t * srcPtr = NULL; /* NULL ptr src */
  size_t length = 10;
  uint8_t correctMem[10] = {0,0,0,0,0,0,0,0,0,0};

  assert_true(my_memmove(srcPtr,length) == srcPtr); /* Good pointer access */
  assert_memory_equal(srcPtr,correctMem,length*sizeof(uint8_t)); /* check value set */

  return;
}

/* MEM REVERSE */
static void memRvrsTstInvldPtr(void **state)
{
  uint8_t * srcPtr = NULL; /* NULL ptr src */
  size_t length = 10;

  assert_true(my_reverse(srcPtr,length) == NULL); /* NULL pointer access */

  return;
}

static void memRvrsTstOddLen(void **state)
{
  uint8_t memBuff[20];
  uint8_t correctMem[9] = {8,7,6,5,4,3,2,1,0};

  uint8_t * srcPtr;
  size_t length = 9;

  int i;
  for(i = 0; i < (int)length; i++)
  {
    memBuff[i] = i; /* buff contains values 0 - 8 */
  }

  srcPtr = &memBuff[0]; /* set pointer to source */

  assert_true(my_reverse(srcPtr,length) == srcPtr); /* assert pointer to src returned */
  assert_memory_equal(srcPtr,correctMem,length*sizeof(uint8_t)); /* asssert memory reversed properly */

  return;
}

static void memRvrsTstEvenLen(void **state)
{
  uint8_t memBuff[20];
  uint8_t correctMem[10] = {9,8,7,6,5,4,3,2,1,0};

  uint8_t * srcPtr;
  size_t length = 10;

  int i;
  for(i = 0; i < (int)length; i++)
  {
    memBuff[i] = i; /* buff contains values 0 - 9 */
  }

  srcPtr = &memBuff[0]; /* set pointer to source */

  assert_true(my_reverse(srcPtr,length) == srcPtr); /* assert pointer to src returned */
  assert_memory_equal(srcPtr,correctMem,length*sizeof(uint8_t)); /* asssert memory reversed properly */

  return;
}

static void memRvrsTstAllChars(void **state)
{
  char memBuff[256];
  char correctMem[256];

  uint8_t * srcPtr;
  size_t length = 256;

  int i;
  for(i = 0; i < (int)length; i++)
  {
    memBuff[i] = (char)i; /* buff contains values 0 - 255 char values */
    correctMem[i] = char(255 - i); /* buff contains values 255 - 0 char values */
  }

  srcPtr = (uint8_t* )&memBuff[0]; /* set pointer to source */

  assert_true(my_reverse(srcPtr,length) == srcPtr); /* assert pointer to src returned */
  assert_memory_equal(srcPtr,(uint8_t *)correctMem,length*sizeof(uint8_t)); /* asssert memory reversed properly */

  return;
}

/* MAIN */
int main(void)
{
	const struct CMUnitTest my_memmove_tests[] =
	{
		cmocka_unit_test(memMvTstInvldPtr),
		cmocka_unit_test(memMvTstNoOvrlp),
		cmocka_unit_test(memMvTstSrcOvrlpDst),
		cmocka_unit_test(memMvTstDstOvrlpSrc),
		cmocka_unit_test(memMvTstDstEqSrc),

    cmocka_unit_test(memSetTstInvldPtr),
    cmocka_unit_test(memSetTstSetVal),

    cmocka_unit_test(memZeroTstInvldPtr),
    cmocka_unit_test(memZeroTstSetVal),

    cmocka_unit_test(memRvrsTstInvldPtr),
    cmocka_unit_test(memRvrsTstOddLen),
    cmocka_unit_test(memRvrsTstEvenLen),
    cmocka_unit_test(memRvrsTstAllChars),
	};

  cmocka_run_group_tests_name("my_memmove tests",my_memmove_tests, NULL, NULL);

  return 0;
}
