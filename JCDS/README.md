# JCDS

Java Concurrent Data Structure, just for fun!

本项目基于Apache Maven 3.6.x构建。在文件`pom.xml`中，你可以看到关于该项目的相关配置信息。
本项目使用了JUnit 3.8.1进行测试，测试代码位于目录`src/test`下。

## ArrayList6COW

基于写时复制（copy on write）的array-list，代码中的实现很大程度参考自Java中的类`java.util.concurrent.CopyOnWriteArrayList`。
具体说来，写时复制的实现很大程度上依赖于Java中的引用的特点，以及几个用于复制的函数`System.arraycopy`和`Arrays.copyOf`。
你可以从类`ArrayList6COW`的下面这个`add`方法get到所谓写时复制是如何实现的。
```java
public void add(E e) {
    synchronized (lock) {
        Object[] es = getArray();
        int len = es.length;
        es = Arrays.copyOf(es, len + 1);
        es[len] = e;
        setArray(es);
    }
}
```
显然，对array-list的读操作就无需上锁，这在一定程度上提高了并发的时间效率。其它的方法也较为简单，这里就不一一赘述了。
