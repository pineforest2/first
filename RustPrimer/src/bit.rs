pub mod bit {
  pub struct BitVec {
    length: usize,
    data: Vec<u32>,
  }
  impl BitVec {
    pub fn new() -> Self {
      Self {
        length: 0,
        data: vec![],
      }
    }
    pub fn len(&self) -> usize {
      return self.length;
    }
    pub fn get(&self, idx: usize) -> bool {
      assert!(self.length != 0 && idx < self.length);
      let t1 = idx / 32;
      let t2 = idx - 32 * t1;
      let mask = 1_u32 << t2;
      return (self.data[t1] & mask) != 0;
    }
    pub fn set(&mut self, idx: usize) {
      assert!(self.length != 0 && idx < self.length);
      let t1 = idx / 32;
      let t2 = idx - 32 * t1;
      let mask = 1_u32 << t2;
      self.data[t1] |= mask;
    }
    pub fn reset(&mut self, idx: usize) {
      assert!(self.length != 0 && idx < self.length);
      let t1 = idx / 32;
      let t2 = idx - 32 * t1;
      let mask = !(1_u32 << t2);
      self.data[t1] &= mask;
    }
    pub fn pushback(&mut self, value: bool) {
      if self.data.len() * 32 > self.length {
        self.length += 1;
      } else {
        self.length += 1;
        self.data.push(0);
      }
      if value {
        self.set(self.length - 1);
      }
    }
    pub fn popback(&mut self) {
      self.length -= 1;
    }
  }

  pub struct BitWord<T> {
    data: T,
  }
  pub trait unsigned_integer<T> {
    fn zero() -> T;
    fn get(&self, idx: usize) -> bool;
    fn set(&mut self, idx: usize);
    fn reset(&mut self, idx: usize);
  }
  impl unsigned_integer<u8> for u8 {
    fn zero() -> u8 {
      return 0_u8;
    }
    fn get(&self, idx: usize) -> bool {
      assert!(idx < 8);
      let mask = 1_u8 << idx;
      return (self & mask) != 0;
    }
    fn set(&mut self, idx: usize) {
      assert!(idx < 8);
      let mask = 1_u8 << idx;
      (*self) |= mask;
    }
    fn reset(&mut self, idx: usize) {
      assert!(idx < 8);
      let mask = !(1_u8 << idx);
      (*self) &= mask;
    }
  }
  impl unsigned_integer<u16> for u16 {
    fn zero() -> u16 {
      return 0_u16;
    }
    fn get(&self, idx: usize) -> bool {
      assert!(idx < 16);
      let mask = 1_u16 << idx;
      return (self & mask) != 0;
    }
    fn set(&mut self, idx: usize) {
      assert!(idx < 16);
      let mask = 1_u16 << idx;
      (*self) |= mask;
    }
    fn reset(&mut self, idx: usize) {
      assert!(idx < 16);
      let mask = !(1_u16 << idx);
      (*self) &= mask;
    }
  }
  impl unsigned_integer<u32> for u32 {
    fn zero() -> u32 {
      return 0_u32;
    }
    fn get(&self, idx: usize) -> bool {
      assert!(idx < 32);
      let mask = 1_u32 << idx;
      return (self & mask) != 0;
    }
    fn set(&mut self, idx: usize) {
      assert!(idx < 32);
      let mask = 1_u32 << idx;
      (*self) |= mask;
    }
    fn reset(&mut self, idx: usize) {
      assert!(idx < 32);
      let mask = !(1_u32 << idx);
      (*self) &= mask;
    }
  }
  impl unsigned_integer<u64> for u64 {
    fn zero() -> u64 {
      return 0_u64;
    }
    fn get(&self, idx: usize) -> bool {
      assert!(idx < 64);
      let mask = 1_u64 << idx;
      return (self & mask) != 0;
    }
    fn set(&mut self, idx: usize) {
      assert!(idx < 64);
      let mask = 1_u64 << idx;
      (*self) |= mask;
    }
    fn reset(&mut self, idx: usize) {
      assert!(idx < 64);
      let mask = !(1_u64 << idx);
      (*self) &= mask;
    }
  }
  impl unsigned_integer<u128> for u128 {
    fn zero() -> u128 {
      return 0_u128;
    }
    fn get(&self, idx: usize) -> bool {
      assert!(idx < 128);
      let mask = 1_u128 << idx;
      return (self & mask) != 0;
    }
    fn set(&mut self, idx: usize) {
      assert!(idx < 128);
      let mask = 1_u128 << idx;
      (*self) |= mask;
    }
    fn reset(&mut self, idx: usize) {
      assert!(idx < 128);
      let mask = !(1_u128 << idx);
      (*self) &= mask;
    }
  }
  impl<T> BitWord<T> {
    pub fn new() -> Self
    where
      T: unsigned_integer<T>,
    {
      Self { data: T::zero() }
    }
    pub fn get(&self, idx: usize) -> bool
    where
      T: unsigned_integer<T>,
    {
      T::get(&(self.data), idx)
    }
    pub fn set(&mut self, idx: usize)
    where
      T: unsigned_integer<T>,
    {
      T::set(&mut (self.data), idx);
    }
    pub fn reset(&mut self, idx: usize)
    where
      T: unsigned_integer<T>,
    {
      T::reset(&mut (self.data), idx);
    }
  }
}

#[cfg(test)]
mod bit_tests {
  use super::*;

  #[test]
  fn test_bitvec() {
    let mut bv = bit::BitVec::new();
    bv.pushback(true);
    bv.pushback(false);
    assert_eq!(bv.get(0), true);
    assert_eq!(bv.get(1), false);
    bv.reset(0);
    bv.set(1);
    assert_eq!(bv.get(0), false);
    assert_eq!(bv.get(1), true);
    bv.popback();
    assert_eq!(bv.len(), 1);
  }

  #[test]
  fn test_bitword() {
    let mut bw: bit::BitWord<u8> = bit::BitWord::new();
    assert_eq!(bw.get(0), false);
    bw.set(2);
    assert_eq!(bw.get(2), true);
    bw.reset(2);
    assert_eq!(bw.get(2), false);
  }
}
