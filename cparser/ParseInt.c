#include <stdio.h>
#include <assert.h>

#define IS_DEC_DIGIT(ch) (((ch)>='0' && (ch)<='9')?1:0)
#define IS_OCT_DIGIT(ch) (((ch)>='0' && (ch)<='7')?1:0)
#define IS_HEX_DIGIT(ch) (IS_DEC_DIGIT(ch) || (((ch)>='a' && (ch)<='f')?1:0))

static inline unsigned int
string_length(const char *string) {
	unsigned int len = 0;
	while (*(string + len) != '\0') len++;
	return len;
}

/* rs: return status */
int parse_int(const char *str, char* rs) {
	int idx = 0;
	char isneg = 0;
	while (1) {
		if (*(str + idx) == '-' && idx == 0) {
		}
	}
}


#ifndef IS_LIB
int main() {
}
#endif