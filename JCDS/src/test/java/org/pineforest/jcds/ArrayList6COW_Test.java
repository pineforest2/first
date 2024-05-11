package org.pineforest.jcds;

import junit.framework.TestCase;

public class ArrayList6COW_Test extends TestCase {

    // 单线程测试
    public void test0() {
        ArrayList6COW<Integer> a = new ArrayList6COW<>();
        a.add(9);
        a.add(1);
        a.add(1);
        assertEquals(a.get(0).intValue(), 9);
        assertEquals(a.get(1).intValue(), 1);
        assertEquals(a.get(2).intValue(), 1);
        a.remove(0);
        assertEquals(a.get(0).intValue(), 1);
        a.add(0, 9);
        assertEquals(a.get(0).intValue(), 9);
        assertEquals(a.get(1).intValue(), 1);
        assertEquals(a.get(2).intValue(), 1);
        a.remove(1);
        assertEquals(a.get(0).intValue(), 9);
        assertEquals(a.get(1).intValue(), 1);
        a.add(1, 1);
        assertEquals(a.get(0).intValue(), 9);
        assertEquals(a.get(1).intValue(), 1);
        assertEquals(a.get(2).intValue(), 1);
        a.remove();
        assertEquals(a.get(0).intValue(), 9);
        assertEquals(a.get(1).intValue(), 1);
        a.remove();
        a.remove();
        assertTrue(a.isEmpty());

        Integer[] aa = new Integer[3];
        aa[0] = 9; aa[1] = 1; aa[2] = 1;
        ArrayList6COW<Integer> b = new ArrayList6COW<>(aa);
        assertEquals(b.indexOf(1), 1);
        assertEquals(b.indexOf(1, 2), 2);
        assertEquals(b.lastIndexOf(1), 2);
        assertEquals(b.lastIndexOf(1, 1), 1);
    }

    // 多线程测试1
    public void test1() {
    }
}