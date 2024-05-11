package org.pineforest.jcds;

import junit.framework.TestCase;

public class ArrayList6COW_Test extends TestCase {

    // 单线程测试
    public void test0() {
        ArrayList6COW<Integer> a = new ArrayList6COW<>();
        a.add(9);
        a.add(1);
        assertEquals(a.get(0).intValue(), 9);
        assertEquals(a.get(1).intValue(), 1);
    }

    // 多线程测试1
    public void test1() {
    }
}