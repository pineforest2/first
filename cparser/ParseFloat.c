#include <stdio.h>
#include <assert.h>

extern unsigned int fast_pow(unsigned int a, unsigned int n);
extern int parse_int(const char *str, unsigned int len);

float fast_pow2(int a, int n) {
	if (a == 0 && n == 0) assert(0);
	float ans = 1.f;
	int nn = (n >= 0) ? n : -n;
	while (nn) {
		if (nn % 2) ans *= a;
		a *= a;
		nn /= 2;
	}
	return (n >= 0) ? ans : 1 / ans;
}

float parse_float(const char *str, unsigned int len) {
	int n1 = 0;
	int n2 = 0;
	int n3 = 0;
	float value = 0.f;

	unsigned int idx = 0;
	unsigned int dot_idx = 0xffffffff;
	unsigned int e_idx = 0xffffffff;
	while (idx < len) {
		if (*(str + idx) == '.') {
			dot_idx = idx;
			n1 = parse_int(str, dot_idx);
		}
		if (*(str + idx) == 'e' || *(str + idx) == 'E') {
			e_idx = idx;
			if (dot_idx == 0xffffffff) {
				n2 = parse_int(str, e_idx);
			} else {
				n2 = parse_int(str + dot_idx + 1, e_idx - dot_idx - 1);
			}
			n3 = parse_int(str + e_idx + 1, len - e_idx - 1);
			break;
		}
		idx++;
	}

	/* bug: n1, n2, n3 may be negtive */
	if (dot_idx != 0xffffffff && e_idx != 0xffffffff) {
		/*  str[0:len - 1] -> n1, n2, n3 -> value  */
		value = (n1 + fast_pow2(10, e_idx - dot_idx - 1) * n2) * fast_pow(10, n3);
	} else if (dot_idx == 0xffffffff && e_idx != 0xffffffff) {
		/*  str[0:len - 1] -> n2, n3 -> value  */
		value = (float) n2 * fast_pow(10, n3);
	} else if (dot_idx != 0xffffffff && e_idx == 0xffffffff) {
		/*  str[0:len - 1] -> n1, n2 -> value  */
		n2 = parse_int(str + dot_idx + 1, len - dot_idx - 1);
		value = n1 + fast_pow2(10, -(len - dot_idx - 1)) * n2;
	} else {
		/*  str[0:len - 1] -> n1 -> value  */
		n1 = parse_int(str, len);
		value = (float) n1;
	}
	return value;
}

#ifndef IS_LIB

int main() {
}
#endif