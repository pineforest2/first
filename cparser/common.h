#ifndef __cparser_common_h__
#define __cparser_common_h__

static inline unsigned int
fast_pow1(unsigned int a, unsigned int n) {
	unsigned int ans = 1;
	while (n) {
		if (n & 1) ans *= a;
		a *= a;
		n >>= 1;
	}
	return ans;
}

static inline float
fast_pow2(int a, int n) {
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

#endif  /* __cparser_common_h__ */