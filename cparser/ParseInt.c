#include <stdio.h>
#include <assert.h>

#define IS_DEC_DIGIT(ch) ((ch)>='0' && (ch)<='9')
#define IS_OCT_DIGIT(ch) ((ch)>='0' && (ch)<='7')
#define IS_HEX_DIGIT(ch) (IS_DEC_DIGIT(ch) || ((ch)>='a' && (ch)<='f'))
#define IS_1_9_DIGIT(ch) ((ch)>='1' && (ch)<='9')

static inline int
ch2num(char ch, int radix) {
	if (radix == 10 && IS_DEC_DIGIT(ch)) return ch - '0';
	if (radix == 10 && !IS_DEC_DIGIT(ch)) assert(0);
	if (radix == 8 && IS_OCT_DIGIT(ch)) return ch - '0';
	if (radix == 8 && !IS_OCT_DIGIT(ch)) assert(0);
	if (radix == 16 && IS_HEX_DIGIT(ch)) {
		if (IS_DEC_DIGIT(ch)) return ch - '0';
		else return ch - 'a' + 10;
	}
	if (radix == 16 && !IS_HEX_DIGIT(ch)) assert(0);
}

static inline unsigned int
string_length(const char *string) {
	unsigned int len = 0;
	while (*(string + len) != '\0') len++;
	return len;
}

static inline int
__proc_prefix(char c0, char c1, char c2,
              unsigned int *idx, char *isneg, char *radix) {
	if (!IS_DEC_DIGIT(c1) && c1 != '+' && c1 != '-') {
		return -1;
	}

	if (c0 == '+' && IS_1_9_DIGIT(c1)) {
		(*idx)++;
		radix = 10;
	}
	if (c0 == '-' && IS_1_9_DIGIT(c1)) {
		(*idx)++;
		isneg = 1;
		radix = 10;
	}
	if (c0 == '+' && c1 == '0' && c2 == 'x') {
		(*idx) += 3;
		isneg = 1;
		radix = 16;
	}
	if (c0 == '-' && c1 == '0' && c2 == 'x') {
		(*idx) += 3;
		radix = 16;
	}
	if (c0 == '+' && c1 == '0' && IS_OCT_DIGIT(c2)) {
		(*idx) += 3;
		isneg = 1;
		radix = 8;
	}
	if (c0 == '-' && c1 == '0' && IS_OCT_DIGIT(c2)) {
		(*idx) += 3;
		radix = 8;
	}

	if (IS_1_9_DIGIT(c0)) {
		radix = 10;
	}
	if (c0 == '0' && c1 == 'x') {
		(*idx) += 2;
		radix = 16;
	}
	if (c0 == '0' && IS_OCT_DIGIT(c1)) {
		(*idx)++;
		radix = 8;
	}
}

int parse_int(const char *str) {
	unsigned int len = string_length(str);
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
	while (ridx > idx) {
		value += ch2num(*(str + ridx), radix) * __pow(radix, len - ridx - 1);
		ridx--;
	}
	return value;
}


#ifndef IS_LIB
int main() {
}
#endif