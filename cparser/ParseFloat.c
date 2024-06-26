#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "common.h"

#define IS_DEC_DIGIT(ch) ((ch)>='0' && (ch)<='9')
#define ABS(x) (((x) > 0) ? (x) : -(x))

static inline int
__ch2num(char ch) {
	if (IS_DEC_DIGIT(ch)) return ch - '0';
	else assert(0);
	/* suppressing warning */
	return -1;
}

static inline long
__parse_dec_long(const char *str, unsigned int len) {
	unsigned int idx = 0;
	unsigned int ridx = len - 1;
	int value = 0;
	char isneg = 0;
	if (len == 0) return 0;
	if (*str == '+') idx++;
	if (*str == '-') {
		idx++;
		isneg = 1;
	}
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
	return (isneg == 1) ? -value : value;
}

static inline void
__find_dot_eE_plus_minus(
	const char *str, unsigned int len,
	char *isneg1, char *isneg2,
	unsigned int *dot_idx, unsigned int *e_idx) {
	unsigned int idx = 0;
	if (*str == '-') *isneg1 = 1;
	if (*str == '+') *isneg1 = 2;
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
		if (*(str + idx) == '+' && idx != 0) {
			assert(*isneg2 == 0);
			assert(*e_idx != 0xffffffff && *e_idx+1 == idx);
			*isneg2 = 2;
		}
		if (*(str + idx) == '-' && idx != 0) {
			assert(*isneg2 == 0);
			assert(*e_idx != 0xffffffff && *e_idx+1 == idx);
			*isneg2 = 1;
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
		n1 = ABS(__parse_dec_long(str, dot_idx));
		n2 = __parse_dec_long(str + dot_idx + 1, e_idx - dot_idx - 1);
		n3 = __parse_dec_long(str + e_idx + 1, len - e_idx - 1);
		value = (n1 + fast_pow2(10, -(e_idx - dot_idx - 1)) * n2) * fast_pow2(10, n3);
		value = (isneg1 == 1) ? -value : value;
	} else if (dot_idx == 0xffffffff && e_idx != 0xffffffff) {
		/*  str[0:len - 1] -> n1, n2 -> value  */
		n1 = __parse_dec_long(str, e_idx);
		n2 = __parse_dec_long(str + e_idx + 1, len - e_idx - 1);
		value = (float) n1 * fast_pow2(10, n2);
	} else if (dot_idx != 0xffffffff && e_idx == 0xffffffff) {
		/*  str[0:len - 1] -> n1, n2 -> value  */
		n1 = ABS(__parse_dec_long(str, dot_idx));
		n2 = __parse_dec_long(str + dot_idx + 1, len - dot_idx - 1);
		value = n1 + fast_pow2(10, -(len - dot_idx - 1)) * n2;
		value = (isneg1 == 1) ? -value : value;
	} else {
		assert(isneg2 == 0);
		/*  str[0:len - 1] -> n1 -> value  */
		n1 = __parse_dec_long(str, len);
		value = (float) n1;
	}
	return value;
}

#ifndef IS_LIB

#define TEST_FLOAT_EQ(x, y) \
	do { \
		if (ABS((x) - (y)) < 1e-6) printf("passed\n"); \
		else printf("error\n"); \
	} while (0)

int main() {
	TEST_FLOAT_EQ(1.1, parse_float("1.1", 3));
	TEST_FLOAT_EQ(+1.1, parse_float("+1.1", 4));
	TEST_FLOAT_EQ(-1.1, parse_float("-1.1", 4));
	TEST_FLOAT_EQ(001.1, parse_float("001.1", 5));
	TEST_FLOAT_EQ(-001.1, parse_float("-001.1", 6));
	TEST_FLOAT_EQ(1., parse_float("1.", 2));
	TEST_FLOAT_EQ(.1, parse_float(".1", 2));
	TEST_FLOAT_EQ(11e-1, parse_float("11e-1", 5));
	TEST_FLOAT_EQ(11E-1, parse_float("11E-1", 5));
	TEST_FLOAT_EQ(+11e-1, parse_float("+11e-1", 6));
	TEST_FLOAT_EQ(-11e-1, parse_float("-11e-1", 6));
	TEST_FLOAT_EQ(-00011e-01, parse_float("-00011e-01", 10));
	TEST_FLOAT_EQ(0.11e1, parse_float("0.11e1", 6));
}
#endif