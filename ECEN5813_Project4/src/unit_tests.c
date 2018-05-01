/**
 * @file unit_tests.c
 * @brief a set of unit tests for memory, conversion, and circbuf functions
 *
 * @author Girish Narayanswamy & Karros Huang
 * @date 4 March 2018
 * @version 1.0
 *
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "memory.h"
#include "conversion.h"
#include "circbuf.h"

/* MEMORY TESTS: MEM MOVE */

/**
 * @brief Tests mem move for invalid pointer input
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
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

/**
 * @brief Tests mem move for non overlapping memory segments
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
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

/**
 * @brief Tests mem move for overlapping memory segments (SRC over DST)
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
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

/**
 * @brief Tests mem move for overlapping memory segments (DST over SRC)
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
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

/**
 * @brief Tests mem move for SRC equal to DST
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
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

/* MEMORY TESTS: MEM SET */

/**
 * @brief Tests mem set for invalid input pointer
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void memSetTstInvldPtr(void **state)
{
  uint8_t * srcPtr = NULL; /* NULL ptr src */
  size_t length = 10;
  uint8_t val = 0x01;

  assert_true(my_memset(srcPtr,length,val) == NULL); /* NULL pointer access */

  return;
}

/**
 * @brief Tests mem set for valid memory segment
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void memSetTstSetVal(void **state)
{
  uint8_t memBuff[10];
  uint8_t * srcPtr = memBuff; /* valid ptr */
  size_t length = 10;
  uint8_t val = 0x01;
  uint8_t correctMem[10] = {1,1,1,1,1,1,1,1,1,1};

  assert_true(my_memset(srcPtr,length,val) == srcPtr); /* Good pointer access */
  assert_memory_equal(srcPtr,correctMem,length*sizeof(uint8_t)); /* check value set */

  return;
}

/* MEMORY TESTS: MEM ZERO */

/**
 * @brief Tests mem zero for invalid input pointer
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void memZeroTstInvldPtr(void **state)
{
  uint8_t * srcPtr = NULL; /* NULL ptr src */
  size_t length = 10;

  assert_true(my_memzero(srcPtr,length) == NULL); /* NULL pointer access */

  return;
}

/**
 * @brief Tests mem zero for valid input pointer
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void memZeroTstSetVal(void **state)
{
  uint8_t memBuff[10];
  uint8_t * srcPtr = memBuff; /* valid buffer */
  size_t length = 10;
  uint8_t correctMem[10] = {0,0,0,0,0,0,0,0,0,0};

  assert_true(my_memzero(srcPtr,length) == srcPtr); /* Good pointer access */
  assert_memory_equal(srcPtr,correctMem,length*sizeof(uint8_t)); /* check value set */

  return;
}

/* MEMORY TESTS: MEM REVERSE */

/**
 * @brief Tests mem reverse for invalid input pointer
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void memRvrsTstInvldPtr(void **state)
{
  uint8_t * srcPtr = NULL; /* NULL ptr src */
  size_t length = 10;

  assert_true(my_reverse(srcPtr,length) == NULL); /* NULL pointer access */

  return;
}

/**
 * @brief Tests mem reverse for valid input pointer and odd count of vals
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
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

/**
 * @brief Tests mem reverse for valid input pointer and even count of vals
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
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

/**
 * @brief Tests mem reverse for valid input pointer and all 256 ASCII char values
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
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
    correctMem[i] = (char)(255 - i); /* buff contains values 255 - 0 char values */
  }

  srcPtr = (uint8_t* )&memBuff[0]; /* set pointer to source */

  assert_true(my_reverse(srcPtr,length) == srcPtr); /* assert pointer to src returned */
  assert_memory_equal(srcPtr,(uint8_t *)correctMem,length*sizeof(uint8_t)); /* asssert memory reversed properly */

  return;
}

/* CONVERSION TESTS: ATOI */

/**
 * @brief Tests atoi for invalid input pointer
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void cnvrsnAtoiTstInvldPtr(void **state)
{
  uint8_t * ptr = NULL;
  uint8_t digits = 5;
  uint32_t base = 10;

  assert_true(my_atoi(ptr,digits,base) == 0); /* assert pointer returned null */

  return;
}

/**
 * @brief Tests atoi for zero input chatacter
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void cnvrsnAtoiTstZeroInt(void **state)
{
  char * ptr = "0";
  uint8_t digits = 1;
  uint32_t base = 10;

  assert_true(my_atoi((uint8_t *)ptr,digits,base) == 0); /* assert pointer returned zero */

  return;
}

/**
 * @brief Tests atoi for maximum input values
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void cnvrsnAtoiTstMaxInt(void **state)
{
  char * ptrMaxPos = "2147438647";
  char * ptrMaxNeg = "-2147438648";
  uint8_t digits = 10;
  uint32_t base = 10;

  assert_true(my_atoi((uint8_t *)ptrMaxPos,digits,base) == 2147438647); /* assert pointer returned max pos */
  assert_true(my_atoi((uint8_t *)ptrMaxNeg,digits,base) == -2147438648); /* assert pointer returned max neg */

  return;
}

/* CONVERSION TETS: ITOA */

/**
 * @brief Tests itoa for invalid input pointer
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void cnvrsnItoaTstInvldPtr(void **state)
{
  uint8_t * ptr = NULL;
  uint8_t data = 0;
  uint32_t base = 10;

  assert_true(my_itoa(data,ptr,base) == 0); /* assert pointer returned null */

  return;
}

/**
 * @brief Tests itoa for zero input value
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void cnvrsnItoaTstZeroInt(void **state)
{
  uint8_t memBuff[32];
  uint8_t * ptr = memBuff;

  char * correctMem = "0";

  uint8_t data = 0;
  uint32_t base = 10;

  assert_true(my_itoa(data,ptr,base) == 1); /* assert pointer returned zero */
  assert_memory_equal(ptr,(uint8_t *)correctMem,2*sizeof(uint8_t));

  return;
}

/**
 * @brief Tests atoi for maximum input values
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void cnvrsnItoaTstMaxInt(void **state)
{
  uint8_t memBuffMaxPos[32];
  uint8_t * ptrMaxPos = memBuffMaxPos;
  char * correctMemMaxPos = "2147438647";

  uint8_t memBuffMaxNeg[32];
  uint8_t * ptrMaxNeg = memBuffMaxNeg;
  char * correctMemMaxNeg = "-2147438648";

  uint32_t base = 10;

  assert_true(my_itoa(2147438647,ptrMaxPos,base) == 10); /* assert pointer returned max pos */
  assert_memory_equal(ptrMaxPos,(uint8_t *)correctMemMaxPos,11*sizeof(uint8_t));

  assert_true(my_itoa(-2147438648,ptrMaxNeg,base) == 10); /* assert pointer returned max neg */
  assert_memory_equal(ptrMaxNeg,(uint8_t *)correctMemMaxNeg,12*sizeof(uint8_t));

  return;
}

/* CIRCBUF TEST: INIT AND DESTROY*/

/**
 * @brief Tests CB for successful init and destroy of CB on heap
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void CBTstAllocFree(void **state)
{
  size_t CB_size = 10;
  CB_t CB;

  assert_true(CB_init(&CB, CB_size) == CB_success); /* assert CB and CB struct allocted */
  assert_true(CB_destroy(&CB) == CB_success); /* assert CB destroyed */

  return;
}

/**
 * @brief Tests CB for unsuccessful init given null pointer to CB
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void CBTstInvldPtr(void **state)
{
  size_t CB_size = 10;

  assert_true(CB_init(NULL, CB_size) == CB_null_ptr_err); /* assert CB and CB struct allocted */

  return;
}

/**
 * @brief Tests CB for add and remove from the buffer
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void CBTstAddRmv(void **state)
{
  size_t CB_size = 10;
  CB_t CB;
  uint8_t storedData;
  CB_init(&CB, CB_size);

  int i;
  for(i = 0; i < CB.CB_size; i++)
  {
    assert_true(CB_buffer_add_item(&CB, (uint8_t) i) == CB_success);
    assert_true(CB.CB_count == (i + 1));
  }

  for(i = 0; i < CB.CB_size; i++)
  {
    assert_true(CB_buffer_remove_item(&CB, &storedData) == CB_success);
    assert_true(storedData == i);
  }

  return;
}

/**
 * @brief Tests CB for buffer full error once add is performed on full buffer
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void CBTstFullBuff(void **state)
{
  size_t CB_size = 10;
  CB_t CB;
  CB_init(&CB, CB_size);
  CB_e status;

  int i;
  for(i = 0; i < CB.CB_size + 1; i++)
  {
    status = CB_buffer_add_item(&CB, (uint8_t) i);
  }

  assert_true(status == CB_buff_full_err);

  return;
}

/**
 * @brief Tests CB for buffer empty error once remove is performed on empty buffer
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void CBTstEmptBuff(void **state)
{
  size_t CB_size = 10;
  CB_t CB;
  uint8_t storedData;
  CB_init(&CB, CB_size);
  CB_e status;

  int i;
  for(i = 0; i < CB.CB_size; i++)
  {
    CB_buffer_add_item(&CB, (uint8_t) i);
  }

  for(i = 0; i < CB.CB_size + 1; i++)
  {
    status = CB_buffer_remove_item(&CB, &storedData);
  }

  assert_true(status == CB_buff_empty_err);

  return;
}

/**
 * @brief Tests CB for succesfull add around edge of circulr buffer
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void CBTstWrpAdd(void **state)
{
  size_t CB_size = 10;
  CB_t CB;
  CB_init(&CB, CB_size);
  uint8_t storedData;
  int i;

  CB.CB_head = CB.CB_buff + CB.CB_size/2;
  CB.CB_tail = CB.CB_head + 1;

  for(i = 0; i < CB.CB_size; i++)
  {
    assert_true(CB_buffer_add_item(&CB, (uint8_t) i) == CB_success);
  }

  for(i = 0; i < CB.CB_size; i++)
  {
    assert_true(CB_peek(&CB,i,&storedData) == CB_success);
    assert_true(storedData == 9 - i);
  }

  return;
}

/**
 * @brief Tests CB for succesfull remove around edge of circulr buffer
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void CBTstWrpRmv(void **state)
{
  size_t CB_size = 10;
  CB_t CB;
  CB_init(&CB, CB_size);
  uint8_t storedData;
  int i;

  CB.CB_head = CB.CB_buff + CB.CB_size/2;
  CB.CB_tail = CB.CB_head + 1;

  for(i = 0; i < CB.CB_size; i++)
  {
    assert_true(CB_buffer_add_item(&CB, (uint8_t) i) == CB_success);
  }

  for(i = 0; i < CB.CB_size; i++)
  {
    assert_true(CB_peek(&CB,i,&storedData) == CB_success);
    assert_true(storedData == 9 - i);
  }

  for(i = 0; i < CB.CB_size; i++)
  {
    assert_true(CB_buffer_remove_item(&CB, &storedData) == CB_success);
    assert_true(storedData == i);
  }

  return;
}

/**
 * @brief Tests CB for buffer empty error once remove is performed on empty buffer
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void CBTstOverEmpt(void **state)
{
  size_t CB_size = 10;
  CB_t CB;
  uint8_t storedData;
  CB_init(&CB, CB_size);
  CB_e status;

  int i;

  for(i = 0; i < CB.CB_size + 1; i++)
  {
    status = CB_buffer_remove_item(&CB, &storedData);
    assert_true(status == CB_buff_empty_err);
  }

  return;
}

/**
 * @brief Tests CB for buffer full error once add is performed on full buffer
 *
 * @param void ** state (used by cmocka unit test framework)
 *
 * @return void
 */
static void CBTstOverFull(void **state)
{
  size_t CB_size = 10;
  CB_t CB;
  CB_init(&CB, CB_size);
  CB_e status;

  int i;
  for(i = 0; i < CB.CB_size; i++)
  {
    CB_buffer_add_item(&CB, (uint8_t) i);
  }

  status = CB_buffer_add_item(&CB,10);
  assert_true(status == CB_buff_full_err);

  return;
}

/* MAIN */
int main(void)
{
	const struct CMUnitTest my_memmove_tests[] = /* framework to hold all tests */
	{
    /* Memory function tests */
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

    /* Conversion function tests */
    cmocka_unit_test(cnvrsnAtoiTstInvldPtr),
    cmocka_unit_test(cnvrsnAtoiTstZeroInt),
    cmocka_unit_test(cnvrsnAtoiTstMaxInt),

    cmocka_unit_test(cnvrsnItoaTstInvldPtr),
    cmocka_unit_test(cnvrsnItoaTstZeroInt),
    cmocka_unit_test(cnvrsnItoaTstMaxInt),

    /* Circbuf function tests */
    cmocka_unit_test(CBTstAllocFree),
    cmocka_unit_test(CBTstInvldPtr),
    cmocka_unit_test(CBTstAddRmv),
    cmocka_unit_test(CBTstFullBuff),
    cmocka_unit_test(CBTstEmptBuff),
    cmocka_unit_test(CBTstWrpAdd),
    cmocka_unit_test(CBTstWrpRmv),
    cmocka_unit_test(CBTstOverFull),
    cmocka_unit_test(CBTstOverEmpt),
	};

  /* run all tests */
  cmocka_run_group_tests_name("my_memmove tests",my_memmove_tests, NULL, NULL);

  return 0;
}
