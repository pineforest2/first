#include <stdio.h>
#include <assert.h>

#include "common.h"

#define IS_DEC_DIGIT(ch) ((ch)>='0' && (ch)<='9')

static inline int
__ch2num(char ch) {
	if (IS_DEC_DIGIT(ch)) return ch - '0';
	else assert(0);
	/* suppressing warning */
	return -1;
}

static inline unsigned long
__parse_dec_ulong(const char *str, unsigned int len) {
	unsigned int idx = 0;
	unsigned int ridx = len - 1;
	int value = 0;
	/* processing leading zero */
	while (idx < len) {
		if (*(str + idx) == '0') {
			idx++;
			continue;
		} else break;
	}
	/* counting value */
	while (ridx >= idx) {
		value += __ch2num(*(str + ridx)) * fast_pow1(10, len - ridx - 1);
		/* The ridx is unsigned. */
		if (ridx > 0) ridx--;
		else break;
	}
	return value;
}

static inline void
__find_dot_eE_plus_minus(
	const char *str, unsigned int len,
	char *isneg1, char *isneg2,
	unsigned int *dot_idx, unsigned int *e_idx) {
	unsigned int idx;
	while (idx < len) {
		if (*(str + idx) == '.') {
			assert(*dot_idx == 0xffffffff);
			*dot_idx = idx;
		}
		if (*(str + idx) == 'e') {
			assert(*e_idx == 0xffffffff);
			*e_idx = idx;
		}
		if (*(str + idx) == 'E') {
			assert(*e_idx == 0xffffffff);
			*e_idx = idx;
		}
		if (*(str + idx) == '+') {
			assert(*isneg1 == 0 || *isneg2 == 0);
			assert(idx == 0 || (*e_idx != 0xffffffff && *e_idx+1 == idx));
			if (*isneg1 == 0) *isneg1 = 2;
			else *isneg2 = 2;
		}
		if (*(str + idx) == '-') {
			assert(*isneg1 == 0 || *isneg2 == 0);
			assert(idx == 0 || (*e_idx != 0xffffffff && *e_idx+1 == idx));
			if (*isneg1 == 0) *isneg1 = 1;
			else *isneg2 = 1;
		}
		idx++;
	}
}

float parse_float(const char *str, unsigned int len) {
	long n1 = 0;
	long n2 = 0;
	long n3 = 0;
	float value = 0.f;

	char isneg1 = 0;
	char isneg2 = 0;
	unsigned int dot_idx = 0xffffffff;
	unsigned int e_idx = 0xffffffff;
	__find_dot_eE_plus_minus(str, len, &isneg1, &isneg2, &dot_idx, &e_idx);

	if (dot_idx != 0xffffffff && e_idx != 0xffffffff) {
		/*  str[0:len - 1] -> n1, n2, n3 -> value  */
		if (isneg1 == 0)
			n1 = __parse_dec_ulong(str, dot_idx);
		else if (isneg1 == 1)
			n1 = -__parse_dec_ulong(str + 1, dot_idx - 1);
		else if (isneg1 == 2)
			n1 = __parse_dec_ulong(str + 1, dot_idx - 1);
		else
			assert(0);
		n2 = __parse_dec_ulong(str + dot_idx + 1, e_idx - dot_idx - 1);
		n2 = (isneg1 == 1) ? -n2 : n2;
		if (isneg2 == 0)
			n3 = __parse_dec_ulong(str + e_idx + 1, len - e_idx - 1);
		else if (isneg2 == 1)
			n3 = -__parse_dec_ulong(str + e_idx + 2, len - e_idx - 2);
		else if (isneg2 == 2)
			n3 = __parse_dec_ulong(str + e_idx + 2, len - e_idx - 2);
		else
			assert(0);
		n3 = (isneg2 == 1) ? -n3 : n3;
		value = (n1 + fast_pow2(10, e_idx - dot_idx - 1) * n2) * fast_pow1(10, n3);
	} else if (dot_idx == 0xffffffff && e_idx != 0xffffffff) {
		/*  str[0:len - 1] -> n1, n2 -> value  */
		if (isneg1 == 0)
			n1 = __parse_dec_ulong(str, e_idx);
		else if (isneg1 == 1)
			n1 = -__parse_dec_ulong(str + 1, e_idx - 1);
		else if (isneg1 == 2)
			n1 = __parse_dec_ulong(str + 1, e_idx - 1);
		else
			assert(0);
		n2 = __parse_dec_ulong(str + e_idx + 1, len - e_idx - 1);
		n2 = (isneg1 == 1) ? -n2 : n2;
		value = (float) n1 * fast_pow1(10, n2);
	} else if (dot_idx != 0xffffffff && e_idx == 0xffffffff) {
		/*  str[0:len - 1] -> n1, n2 -> value  */
		if (isneg1 == 0)
			n1 = __parse_dec_ulong(str, dot_idx);
		else if (isneg1 == 1)
			n1 = -__parse_dec_ulong(str + 1, dot_idx - 1);
		else if (isneg1 == 2)
			n1 = __parse_dec_ulong(str + 1, dot_idx - 1);
		else
			assert(0);
		n2 = __parse_dec_ulong(str + dot_idx + 1, len - dot_idx - 1);
		n2 = (isneg1 == 1) ? -n2 : n2;
		value = n1 + fast_pow2(10, -(len - dot_idx - 1)) * n2;
	} else {
		assert(isneg2 == 0);
		/*  str[0:len - 1] -> n1 -> value  */
		if (isneg1 == 0)
			n1 = __parse_dec_ulong(str, len);
		else if (isneg1 == 1)
			n1 = -__parse_dec_ulong(str + 1, len - 1);
		else if (isneg1 == 2)
			n1 = __parse_dec_ulong(str + 1, len - 1);
		else
			assert(0);
		value = (float) n1;
	}
	return value;
}

#ifndef IS_LIB

#define FLOAT_EQ(x, y) ((x) - (y) < 1e-6 || (y) - (x) < 1e-6)
#define TEST_FLOAT_EQ(x, y) \
	do { \
		if (x - y < 1e-6 || y - x < 1e-6) printf("passed\n"); \
		else printf("error\n"); \
	} while (0)

int main() {
	TEST_FLOAT_EQ(1.1, parse_float("1.1", 3));
	TEST_FLOAT_EQ(+1.1, parse_float("+1.1", 4));
	TEST_FLOAT_EQ(-1.1, parse_float("-1.1", 4));
	TEST_FLOAT_EQ(001.1, parse_float("001.1", 5));
	TEST_FLOAT_EQ(-001.1, parse_float("-001.1", 6));
}
#endif