#include <stdio.h>
#include <assert.h>


static inline unsigned int
__strlen(const char *string) {
	unsigned int len = 0;
	while (*(string + len) != '\0') len++;
	return len;
}


float parse_float(const char *str) {
	unsigned int len = __strlen(str);
}

#ifndef IS_LIB

int main() {
}
#endif