#include <iostream>

template <typename T, int N = 10>
class TinyStack {
public:
    TinyStack() : _capacity(N), _top(-1) 
    {
        _array = new T[_capacity];
    }

    ~TinyStack()
    {
        if(_array)
        {
            delete[] _array;
            _array = nullptr;
        }
    }

    bool full(){ return _top == _capacity -  1; }

    bool empty() {return _top == -1; }

    void push(const T &value)
    {
        if(full())
        {
            std::cout << "this stack is full" << std::endl;
            return;
        }
        _array[++_top] = value;
    }

    T top()
    {
        if(!empty())
        {
            return _array[_top];
        }

        return T();
    }

    void pop()
    {
        if(!empty())
        {
            --_top;
        }
        else
        {
            std::cout << "stack is empty" << std::endl;
        }
    }

private:
    int _capacity;
    int _top;
    T *_array;
};


int main()
{
    TinyStack<int, 10> st;
    for(int i = 0; i < 10; i++)
    {
        st.push(i);
    }

    while(!st.empty())
    {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << std::endl;


    TinyStack<double, 10> st1;
    st1.push(1.1);
    st1.push(1.2);
    st1.push(1.3);
    st1.push(1.5);


    while(!st1.empty())
    {
        std::cout << st1.top() << " ";
        st1.pop();
    }
    std::cout << std::endl;

    return 0;
}