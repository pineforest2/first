# cparser

## `ParseInt.c`

针对符合解析成int（32bit）要求的字符串，能成功解析并返回正确的结果。否则，直接使用`assert(0)`中止程序。
下面是几种典型的符合解析成int要求：
- 十进制整数：`11`、`+11`、`-11`。
- 十六进制整数：`0x1f`、`+0x1f`、`-0x1f`、`0x00abcdef`。
- 八进制整数：`0`、`000`、`011`、`00011`。

对于符合以上要求，但是造成int溢出的属于未定义行为。为了代码简洁，无需给出int溢出的警告信息。

### 分析

字符串被解析的状态由最前面的三个符号，可有下面几种情况：
- 第一个字符是`1-9`，应解析为正的十进制数。
- 第一个字符是`0`，去看第二个字符。若第二个字符是`x`，则应解析为正的十六进制数；若第二个字符是`0-7`，则应解析为正的八进制数。
- 第一个字符是`+`，无需改变任何状态，继续看后面两个字符。
- 第一个字符是`-`，只需将负号标志位置位，继续看后面两个字符。

## `ParseFloat.c`