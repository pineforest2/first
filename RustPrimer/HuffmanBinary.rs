use std::env;
use std::fs;

pub struct Huffman {
  table: [usize; 256],
}

impl Huffman {
  pub fn new() -> Self {
    Self {
      table: [0; 256]
    }
  }
}

fn main() {
  let args: Vec<String> = env::args().collect();
  let filename = &args[1];
  let content = fs::read_to_string(filename).expect("file not found!");
  let bytes = content.as_bytes();
  let mut huffman = Huffman::new();
  for &byte in bytes {
    huffman.table[byte as usize] += 1;
  }
}