package org.pineforest.jcds;

import java.util.Arrays;

public class ArrayList6COW<E> {
    final Object lock = new Object();

    private volatile Object[] array;
    final Object[] getArray() { return array; }
    final void setArray(Object[] a) { this.array = a; }

    public ArrayList6COW() {
        setArray(new Object[0]);
    }
    public ArrayList6COW(E[] source) {
        setArray(Arrays.copyOf(source, source.length, Object[].class));
    }

    public void add(E e) {
        synchronized (lock) {
            Object[] es = getArray();
            int len = es.length;
            es = Arrays.copyOf(es, len + 1);
            es[len] = e;
            setArray(es);
        }
    }
    public void remove() {
        synchronized (lock) {
            Object[] es = getArray();
            int len = es.length;
            es = Arrays.copyOf(es, len - 1);
        }
    }
    @SuppressWarnings("unchecked")
    public E get(int index) {
        return (E) getArray()[index];
    }
}




