# Vector内存布局分析脚本

# 设置断点
break main
break modify
break Read

# 运行程序
run

# 查看vector的基本信息
print unsafe_vec
print unsafe_vec.size()
print unsafe_vec.capacity()

# 查看vector的内存地址
print &unsafe_vec
print &unsafe_vec[0]

# 查看vector内部结构（假设的成员变量）
# 注意：这些是编译器实现相关的，可能因编译器而异
print *(void**)&unsafe_vec
print *(void**)((char*)&unsafe_vec + 8)
print *(void**)((char*)&unsafe_vec + 16)

# 查看vector元素
print unsafe_vec[0]
print unsafe_vec[1]
print unsafe_vec[2]

# 查看内存布局（以不同格式显示）
x/3gx &unsafe_vec          # 以8字节为单位显示
x/12x &unsafe_vec          # 以4字节为单位显示
x/24b &unsafe_vec          # 以字节为单位显示

# 查看vector指向的堆内存
# 假设第一个指针是数据指针
set $data_ptr = *(void**)&unsafe_vec
print $data_ptr
x/10x $data_ptr

# 继续执行
continue

# 当程序崩溃时，查看详细信息
bt
thread apply all bt

# 查看崩溃时的vector状态
print unsafe_vec
print unsafe_vec.size()
print unsafe_vec.capacity()

# 再次查看内存布局
x/3gx &unsafe_vec 