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

    public int size() { return getArray().length; }
    public boolean isEmpty() { return size() == 0; }

    public void add(E e) {
        synchronized (lock) {
            Object[] es = getArray();
            int len = es.length;
            es = Arrays.copyOf(es, len + 1);
            es[len] = e;
            setArray(es);
        }
    }
    public void add(int index, E e) {
        synchronized (lock) {
            Object[] es = getArray();
            int len = es.length;
            assert index >= 0 && index <= es.length;
            int numMoved = len - index;
            Object[] newArray;
            if (numMoved == 0) {
                newArray = Arrays.copyOf(es, len + 1);
            } else {
                newArray = new Object[len + 1];
                System.arraycopy(es, 0, newArray, 0, index);
                System.arraycopy(es, index, newArray, index + 1, numMoved);
            }
            newArray[index] = e;
            setArray(newArray);
        }
    }
    public void remove() {
        synchronized (lock) {
            Object[] es = getArray();
            int len = es.length;
            es = Arrays.copyOf(es, len - 1);
            setArray(es);
        }
    }
    public void remove(int index) {
        synchronized (lock) {
            Object[] es = getArray();
            int len = es.length;
            int numMoved = len - index - 1;
            Object[] newArray;
            if (numMoved == 0) {
                newArray = Arrays.copyOf(es, len - 1);
            } else {
                newArray = new Object[len - 1];
                System.arraycopy(es, 0, newArray, 0, index);
                System.arraycopy(es, index + 1, newArray, index, numMoved);
            }
            setArray(newArray);
        }
    }
    @SuppressWarnings("unchecked")
    public E get(int index) {
        assert index >= 0 && index < getArray().length;
        return (E) getArray()[index];
    }

    private int indexOfHelper(E e, int start, int end) {
        if (e == null) {
            for (int i = start; i < end; i++) {
                if (getArray()[i] == null) return i;
            }
        } else {
            for (int i = start; i < end; i++) {
                if (e.equals(getArray()[i])) return i;
            }
        }
        return -1;
    }
    public int indexOf(E e) {
        return indexOfHelper(e, 0, getArray().length);
    }
    public int indexOf(E e, int index) {
        return indexOfHelper(e, index, getArray().length);
    }

    private int lastIndexOfHelper(E e, int start, int end) {
        if (e == null) {
            for (int i = end - 1; i >= start; i--) {
                if (getArray()[i] == null) return i;
            }
        } else {
            for (int i = end - 1; i >= start; i--) {
                if (e.equals(getArray()[i])) return i;
            }
        }
        return -1;
    }
    public int lastIndexOf(E e) {
        return lastIndexOfHelper(e, 0, getArray().length);
    }
    public int lastIndexOf(E e, int index) {
        return lastIndexOfHelper(e, 0, index + 1);
    }
}
