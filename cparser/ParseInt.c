#include <stdio.h>
#include <assert.h>

#include "common.h"

#define IS_1_9_DIGIT(ch) ((ch)>='1' && (ch)<='9')
#define IS_A_F_DIGIT(ch) ((ch)>='A' && (ch)<='F')
#define IS_DEC_DIGIT(ch) ((ch)>='0' && (ch)<='9')
#define IS_OCT_DIGIT(ch) ((ch)>='0' && (ch)<='7')
#define IS_HEX_DIGIT(ch) (IS_DEC_DIGIT(ch) || IS_A_F_DIGIT(ch) || ((ch)>='a' && (ch)<='f'))

static inline int
__ch2num(char ch, int radix) {
	if (radix == 10 && IS_DEC_DIGIT(ch)) return ch - '0';
	if (radix == 10 && !IS_DEC_DIGIT(ch)) assert(0);
	if (radix == 8 && IS_OCT_DIGIT(ch)) return ch - '0';
	if (radix == 8 && !IS_OCT_DIGIT(ch)) assert(0);
	if (radix == 16 && IS_HEX_DIGIT(ch)) {
		if (IS_DEC_DIGIT(ch)) return ch - '0';
		else return (IS_A_F_DIGIT(ch)) ? ch - 'A' + 10 : ch - 'a' + 10;
	}
	if (radix == 16 && !IS_HEX_DIGIT(ch)) assert(0);
	/* suppressing warning */
	return -1;
}

static inline int
__proc_prefix(char c0, char c1, char c2,
              unsigned int *idx, char *isneg, char *radix) {
	if (!IS_DEC_DIGIT(c0) && c0 != '+' && c0 != '-') {
		return -1;
	}

	if (c0 == '+' && IS_1_9_DIGIT(c1)) {
		(*idx)++;
		*radix = 10;
	}
	if (c0 == '-' && IS_1_9_DIGIT(c1)) {
		(*idx)++;
		*isneg = 1;
		*radix = 10;
	}
	if (c0 == '+' && c1 == '0' && (c2 == 'x' || c2 == 'X')) {
		(*idx) += 3;
		*radix = 16;
	}
	if (c0 == '-' && c1 == '0' && (c2 == 'x' || c2 == 'X')) {
		(*idx) += 3;
		*isneg = 1;
		*radix = 16;
	}
	if (c0 == '+' && c1 == '0' && IS_OCT_DIGIT(c2)) {
		(*idx) += 3;
		*isneg = 1;
		*radix = 8;
	}
	if (c0 == '-' && c1 == '0' && IS_OCT_DIGIT(c2)) {
		(*idx) += 3;
		*radix = 8;
	}

	if (IS_1_9_DIGIT(c0)) {
		*radix = 10;
	}
	if (c0 == '0' && (c1 == 'x' || c1 == 'X')) {
		(*idx) += 2;
		*radix = 16;
	}
	if (c0 == '0' && IS_OCT_DIGIT(c1)) {
		(*idx)++;
		*radix = 8;
	}
	return 0;
}


int parse_int(const char *str, unsigned int len) {
	unsigned int idx = 0;
	unsigned int ridx = len - 1;
	char isneg = 0;
	char radix = 0;
	int value = 0;
	int tmp = __proc_prefix(*(str), *(str + 1),
	                        *(str + 2), &idx, &isneg, &radix);
	if (tmp == -1) assert(0);
	/* processing leading zero */
	while (idx < len) {
		if (*(str + idx) == '0') {
			idx++;
			continue;
		} else break;
	}
	/* counting value */
	while (ridx >= idx) {
		value += __ch2num(*(str + ridx), radix) * fast_pow1(radix, len - ridx - 1);
		/* The ridx is unsigned. */
		if (ridx > 0) ridx--;
		else break;
	}
	return (isneg) ? -value : value;
}


#ifndef IS_LIB

#define TEST_EQ(x, y) \
	do { \
		if (x == y) printf("passed\n"); \
		else printf("error\n"); \
	} while (0)

int main() {
	TEST_EQ(11, parse_int("11", 2));
	TEST_EQ(+11, parse_int("+11", 3));
	TEST_EQ(-11, parse_int("-11", 3));
	TEST_EQ(0x1f, parse_int("0x1f", 4));
	TEST_EQ(+0x1f, parse_int("+0x1f", 5));
	TEST_EQ(-0x1f, parse_int("-0x1f", 5));
	TEST_EQ(0x00abcdef, parse_int("0x00abcdef", 10));
	TEST_EQ(0X1F, parse_int("0X1F", 4));
	TEST_EQ(+0x1F, parse_int("+0x1F", 5));
	TEST_EQ(0X1f, parse_int("0X1f", 4));
	TEST_EQ(0, parse_int("0", 1));
	TEST_EQ(000, parse_int("000", 3));
	TEST_EQ(011, parse_int("011", 3));
	TEST_EQ(0011, parse_int("0011", 4));
}
#endif