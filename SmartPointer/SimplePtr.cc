#include <iostream>

template <typename T>
class SimpleSmartPointer
{
private:
    struct ControlBlock
    {
        T *ptr;
        int ref_count; // 引用计数

        ControlBlock(T *p) : ptr(p), ref_count(1) {}

        void Increment() { ref_count++; }

        int Decrement() { return ref_count--; }
    };

    void release()
    {
        //std::cout << "release()" << std::endl;
        if (_block)
        {
            const int new_count = _block->Decrement(); // 引用计数先--
            if (new_count == 0)
            {
                // 引用计数为 0, 回收内存
                delete _block->ptr;
                delete _block;
            }
            _block = nullptr;
        }
    }

public:
    explicit SimpleSmartPointer(T *ptr = nullptr) : _block(nullptr)
    {
        if (ptr != nullptr)
        {
            _block = new ControlBlock(ptr);
        }
    }

    ~SimpleSmartPointer()
    {
        //std::cout << "~SimpleSmartPointer()" << std::endl;
        release();
    }

    SimpleSmartPointer(const SimpleSmartPointer &rhs) : _block(rhs._block)
    {
        if (_block != nullptr)
        {
            _block->Increment();
        }
    }

    // 移动操作不会改变被移动资源的引用计数，只是改变了资源的所有者

    SimpleSmartPointer(SimpleSmartPointer &&lhs) noexcept
        : _block(lhs._block) // 1. 资源接管   不增加引用计数，因为所有权被转移而不是共享
    {
        //std::cout << "SimpleSmartPointer(&&)" << std::endl;
        // 2. 原对象置空
        // 移动后，源对象不再指向该资源，所以共享该资源的智能指针数量并没有改变（只是从源对象转移到了目标对象）
        lhs._block = nullptr;
    }

    SimpleSmartPointer &operator=(const SimpleSmartPointer &lhs)
    {
        //std::cout << "Assignment Operator" << std::endl;
        if (this != &lhs)
        {
            // 先处理当前对象的引用计数
            release();

            // 指向新的对象
            _block = lhs._block;
            if (_block)
            {
                _block->Increment();
            }
        }

        return *this;
    }

    SimpleSmartPointer &operator=(SimpleSmartPointer &&lhs) noexcept
    {
        //std::cout << "SimpleSmartPointer &operator=(&&)" << std::endl;
        if (this != &lhs)
        {
            release(); // 释放当前对象持有的资源  -> 当前对象会接管 lhs 的资源 -> 所以 lhs 的引用计数不会变

            _block = lhs._block;  // 接管 lhs 的资源
            lhs._block = nullptr; // 置空lhs 的资源指针
        }
        return *this;
    }

    T *operator->() const
    {
        return _block->ptr;
    }

    // 解引用运算符
    T &operator*() const
    {
        return *_block->ptr;
    }

    T *get() const
    {
        return _block ? _block->ptr : nullptr;
    }

    int use_count() const
    {
        return _block ? _block->ref_count : 0;
    }

private:
    ControlBlock *_block; // 指针(所有共享同一对象的shared_ptr可以指向同一个控制块)
};

// 测试类
class Test
{
public:
    Test(int val) : value(val)
    {
        std::cout << "Test Constructor: " << value << std::endl;
    }
    ~Test()
    {
        std::cout << "Test Destructor: " << value << std::endl;
    }
    void show() const
    {
        std::cout << "Value: " << value << std::endl;
    }

private:
    int value;
};

int main()
{
    // 1. 基本构造和析构
    std::cout << "=== Basic Construction ===" << std::endl;
    {
        SimpleSmartPointer<Test> sptr(new Test(100));
        sptr->show();
        std::cout << "Use count: " << sptr.use_count() << std::endl;
    }

    // 


    return 0;
}