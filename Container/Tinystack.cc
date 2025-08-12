#include <iostream>
#define MAX_SIZE 10

using std::endl;
using std::cout;

class Stack
{
public:
    Stack():
        _top(-1), _Arr(new int[MAX_SIZE]){}

    ~Stack()
    {
        if(_Arr != nullptr)
        {
            delete [] _Arr;
            _Arr = nullptr;
        }
    }

    bool empty() const
    {
        return _top == -1;
    }

    bool full() const
    {
        return _top == MAX_SIZE;
    }

    void push(int value) {
        if(full())
        {
            cout << "Stack is full!" << endl;
        }
        _Arr[++_top] = value;
    }

    void pop()
    {
        if(!empty()) {
            _top--;
        }
        else {
            cout << "Stack is empty!" << endl;
        }
    }

    int top() const
    {
        if(!empty())
        {
            return _Arr[_top];
        }
        else
        {
            cout << "Stack is empty!" << endl;
            return -1;
        }
    }

private:
    int _top;
    int *_Arr;        
};


int main()
{
    Stack s;

    // cout << s.empty() << endl;

    for(int i = 0; i < MAX_SIZE; i++)
    {
        s.push(i);
    }

    // cout << s.full() << endl;

    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }

    return 0;
}