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
  size_t length = 0x01;

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
  uint8_t correctMem[10] = {0,1,2,3,4,5,6,8,9};

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
  uint8_t correctMem[10] = {0,1,2,3,4,5,6,8,9};

  uint8_t * srcPtr;
  uint8_t * dstPtr;
  size_t length = 10;

  int i;
  for(i = 0; i < (int)length; i++)
  {
    memBuff[i] = i; /* buff contains values 0 - 9 */
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


int main(void)
{
	const struct CMUnitTest my_memmove_tests[] =
	{
		cmocka_unit_test(memMvTstInvldPtr),
		cmocka_unit_test(memMvTstNoOvrlp),
		cmocka_unit_test(memMvTstSrcOvrlpDst),
		cmocka_unit_test(memMvTstDstOvrlpSrc),
		cmocka_unit_test(memMvTstDstEqSrc),
	};

  cmocka_run_group_tests_name("my_memmove tests",my_memmove_tests, NULL, NULL);

  return 0;
}
