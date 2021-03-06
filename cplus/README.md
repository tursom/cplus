<h1>cplus library</h1>
<h5>C++通用库</h5>
<h5>作者：Tursom Ulefits</h5>

本库实现目的是创建出一套方便实用的通用库，实现各种常见功能。<br>

<h3>utils</h3>
基础的工具包含在了utils文件夹下，包含cplus所有的类的基类
Objec以及各种基础类型对应的类（首字母大写），以及链表和数组等基础数据结构。<br>
<h6>String</h6>
String现在是不可变的了，如果需要构造String的话需要使用StringBuilder
或者StringBuffer。两者的区别在于StringBuffer是线程安全的（时间成本也更高），
而StringBuilder不是（成本也更低）。<br>
<h6>List</h6>
List是一个双向链表，特别之处在于提供了链表大小限制，默认为最多10240个节点。<br>
List的另一个特别之处在于其prev指针和next指针是利用魔法储存在同一个指针中的，
这使得其每个节点可以节省该计算机字长度的内存。具体实现原理是讲两个内存取按位异或，
这样只需要知道其中一个内存就可以求出另一个内存，而对于链表通用的遍历方式，
满足这个条件并不难。其缺点在于遍历链表时要多消耗少量时间，以及开发调试更加复杂，
不过通过良好的封装和调试可以改善后者。<br>
<h6>ArrayList</h6>
ArrayList是对List的一个封装，提供和List相同的操作。<br>
其特殊点在于其内部每个节点都是一个对应类型的数组，在储存大量小型数据的时候可以节省链表中指针所占用的内存
（测试环境为64位计算机，数组大小设置为128，数据类型为int，数据量足够大的情况下能节省大约70％的内存），
但是缺点是内部逻辑更加复杂，而且在数据量较少时（测试环境下储存少于40个数据左右），内存占用反而比List更大。
并且在储存更占内存的数据的时候，内存优化也不会这么明显。<br>
<h6>Stack</h6>
Stack提供类似堆栈的结构，但是其内部实现是一个单向链表，同样具有大小限制的功能，
默认也是10240个数据。<br>
Stack提供push操作和pop操作以及forEach操作。注意push和pop会修改链表结构，
而forEach不会。
<h6>ArrayStack</h6>
ArrayStack类似ArrayList，对Stack进行了封装，是ArrayList的Stack版。


<h3>thread</h3>
thread包含了多线程相关的工具类。目前的类只实现了创建线程的类和线程锁。<br>
Thread类很易用，创建的时候只需要提供 void *(void *) 类型的函数指针即可。传入的参数为该Thread对象的地址。
该类不是创建时即刻启动新线程，需要手动调用start()函数启动新线程。如果需要等待子线程结束，
则需调用该对象的 join() 函数即可。如果需要进行输入输出，则需要调用lockOutput() 来锁定输出，
调用 unlockOutput() 解锁输出，否则可能会导致输出紊乱。<br>

<h3>system</h3>
