#include <iostream>

class Data
{
public:
    int getData() const
    {
        return _data;
    }

private:
    int _data = 1;
};

class MiddleLayer
{
public:
    MiddleLayer(Data *p)
    {
        _pdata = p;
    }
    //...

    ~MiddleLayer()
    {
        if (_pdata)
        {
            delete _pdata;
            _pdata = nullptr;
        }
    }

    Data *operator->() const
    {
        return _pdata;
    }

private:
    Data *_pdata;
};

class ThirdLayer
{
public:
    ThirdLayer(MiddleLayer *pm)
    {
        _pml = pm;
    }
    //...

    ~ThirdLayer()
    {
        if (_pml)
        {
            delete _pml;
            _pml = nullptr;
        }
    }

    // MiddleLayer &operator->() const
    // {
    //     return *_pml;
    // }

    MiddleLayer *operator->() const
    {
        return _pml;
    }

private:
    MiddleLayer *_pml;
};

int main()
{
    MiddleLayer ML(new Data());

    ML->getData();

    // Create MiddleLayer on heap for ThirdLayer to manage
    MiddleLayer *pML = new MiddleLayer(new Data());
    ThirdLayer TL(pML);

    // TL->getData();

    // std::cout << TL.operator->()->getData() << std::endl;

    TL.operator->()->operator->()->getData();

    return 0;
}