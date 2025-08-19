(gdb) break main
Breakpoint 1 at 0x14ad: file VecTest.cc, line 23.
(gdb) break modify
Breakpoint 2 at 0x13d5: file VecTest.cc, line 7.
(gdb) break Read
Breakpoint 3 at 0x1439: file VecTest.cc, line 15.

(gdb) i b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000000014ad in main() at VecTest.cc:23
2       breakpoint     keep y   0x00000000000013d5 in modify() at VecTest.cc:7
3       breakpoint     keep y   0x0000000000001439 in Read() at VecTest.cc:15

(gdb) run
Breakpoint 1, main () at VecTest.cc:23
23      int main() {

(gdb) print unsafe_vec
$1 = std::vector of length 3, capacity 3 = {1, 2, 3}
(gdb) print unsafe_vec.size()
$2 = 3

(gdb) x/3gx &unsafe_vec
0x55555555b160 <unsafe_vec>:    0x000055555556deb0      0x000055555556debc
0x55555555b170 <unsafe_vec+16>: 0x000055555556debc


地址                   | 值                | 对应成员
----------------------------------------------------
0x55555555b160 (0)   | 0x000055555556deb0 | _M_start
0x55555555b168 (8)   | 0x000055555556debc | _M_finish
0x55555555b170 (16)  | 0x000055555556debc | _M_end_of_storage

(0x000055555556debc - 0x000055555556deb0) / sizeof(int)
= (0x0000000000000C) / 4 = 12 / 4 = 3      所以vector中有3个元素，容量也是3

#6  0x0000757c2c0a0cfc in malloc_printerr (str=str@entry=0x757c2c1de7b0 "double free or corruption (!prev)")
    at ./malloc/malloc.c:5664
#7  0x0000757c2c0a2e7c in _int_free (av=0x757c24000030, p=0x757c240017b0, have_lock=<optimized out>)
    at ./malloc/malloc.c:4591
#8  0x0000757c2c0a5453 in __GI___libc_free (mem=<optimized out>) at ./malloc/malloc.c:3391
#9  0x000060d90eaa3d8a in __gnu_cxx::new_allocator<int>::deallocate (this=0x60d90eaa8160 <unsafe_vec>, __p=0x757c240017c0, 
    __t=2308) at /usr/include/c++/11/ext/new_allocator.h:145
#10 0x000060d90eaa3a9d in std::allocator_traits<std::allocator<int> >::deallocate (__a=..., __p=0x757c240017c0, __n=2308)
    at /usr/include/c++/11/bits/alloc_traits.h:496
#11 0x000060d90eaa349c in std::_Vector_base<int, std::allocator<int> >::_M_deallocate (this=0x60d90eaa8160 <unsafe_vec>, 
    __p=0x757c240017c0, __n=2308) at /usr/include/c++/11/bits/stl_vector.h:354
#12 0x000060d90eaa3092 in std::vector<int, std::allocator<int> >::_M_realloc_insert<int const&> (
    this=0x60d90eaa8160 <unsafe_vec>, __position=6032) at /usr/include/c++/11/bits/vector.tcc:500
--Type <RET> for more, q to quit, c to continue without paging--
#13 0x000060d90eaa29c6 in std::vector<int, std::allocator<int> >::push_back (this=0x60d90eaa8160 <unsafe_vec>, 
    __x=@0x757c2b7fdd84: 0) at /usr/include/c++/11/bits/stl_vector.h:1198

场景:
T1: 线程1开始扩容，分配新内存
T2: 线程2同时调用push_back，可能触发另一次扩容
T3: 线程1释放旧内存
T4: 线程2也尝试释放同一块内存 → double free!


(gdb) print unsafe_vec
$1 = std::vector of length 1003, capacity 1536 = {1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 
  19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 
  49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 
  79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 
  107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 
  131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 
  155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 
  179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196...}


vector包含重复的序列: {1,2,3,0,1,2,3,4,5...}
问题分析: 多个线程同时添加元素，阔若过程中内存管理混乱，导致同一块内存被多次释放