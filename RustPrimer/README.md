# Rust Primer

学习Rust。
本项目是基于Cargo构建。

**`bit.rs`**

这里主要是用来管理bit的数据结构，在C++和Java的标准库中都提供了所谓bitset的东西，而Rust的标准库貌似没有。
其中主要有两个结构体`BitVec`和`BitWord`。其中`BitVec`就可视为bitset，它实际就是对`Vec<u32>`的封装。而`BitWord`是定长的，它是一个泛型结构体，其类型参数可接受Rust中的五种无符号整型，即`u8`、`u16`、`u32`、`u64`、`u128`。
针对这两个结构体中的bit的操作都是通过索引`idx`的，同计算机中惯例一样，该索引也是从0开始。值得说明的是，对于`BitWord`，第0位是其成员`data`的最低位。而`BitVec`可能有多个`u32`。因此，第0位应该是其成员`data[0]`的最低位，而第32位应该是其成员`data[1]`的最低位。
你可以在文件`bit.rs`中的模块`bit_tests`观察一下具体的使用。

**`HuffmanBinary.rs`**

这是一个基于Huffman二叉树的Huffman编码，可对文件进行Huffman编解码。
