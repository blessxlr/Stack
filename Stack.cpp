#include "StackImplementation.h"
#include "Stack.h"
#include "Vector.h"
#include "List.h"
#include <stdexcept>
class VectorStack : public IStackImplementation {
    Vector _data; 
public:
    void push(const ValueType& value) override {
        _data.pushBack(value); 
    }
    
    void pop() override {
        if (_data.size() == 0) throw std::underflow_error("Stack is empty");
        _data.popBack();  
    }
    
    const ValueType& top() const override {
        if (_data.size() == 0) throw std::underflow_error("Stack is empty");
        return _data[_data.size() - 1];
    }
    
    bool isEmpty() const override {
        return _data.size() == 0;
    }
    
    size_t size() const override {
        return _data.size();
    }
};
class ListStack : public IStackImplementation {
    DFlist _data;  
public:
    void push(const ValueType& value) override {
        _data.push_back(value);  
    }
    
    void pop() override {
        if (_data.empty()) throw std::underflow_error("Stack is empty");
        _data.pop_back();  
    }
    
    const ValueType& top() const override {
        if (_data.empty()) throw std::underflow_error("Stack is empty");
        return _data.back().val;  
    }
    
    bool isEmpty() const override {
        return _data.empty();
    }
    
    size_t size() const override {
        return _data.size();
    }
};

Stack::Stack(StackContainer container) : _containerType(container) {
    switch (container) {
        case StackContainer::Vector:
            _pimpl = new VectorStack();
            break;
        case StackContainer::List:
            _pimpl = new ListStack();
            break;
        default:
            throw std::invalid_argument("Unknown container type");
    }
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container)
    : Stack(container) {
    for (size_t i = 0; i < arraySize; ++i) {
        _pimpl->push(valueArray[i]);
    }
}

Stack::Stack(const Stack& copyStack) : _containerType(copyStack._containerType) {
    switch (_containerType) {
        case StackContainer::Vector:
            _pimpl = new VectorStack(*dynamic_cast<VectorStack*>(copyStack._pimpl));
            break;
        case StackContainer::List:
            _pimpl = new ListStack(*dynamic_cast<ListStack*>(copyStack._pimpl));
            break;
        default:
            throw std::invalid_argument("Unknown container type");
    }
}

Stack& Stack::operator=(const Stack& copyStack) {
    if (this == &copyStack) return *this;
    delete _pimpl;
    _containerType = copyStack._containerType;
    switch (_containerType) {
        case StackContainer::Vector:
            _pimpl = new VectorStack(*dynamic_cast<VectorStack*>(copyStack._pimpl));
            break;
        case StackContainer::List:
            _pimpl = new ListStack(*dynamic_cast<ListStack*>(copyStack._pimpl));
            break;
        default:
            throw std::invalid_argument("Unknown container type");
    }
    return *this;
}

Stack::Stack(Stack&& moveStack) noexcept
    : _pimpl(moveStack._pimpl), _containerType(moveStack._containerType) {
    moveStack._pimpl = nullptr;
}

Stack& Stack::operator=(Stack&& moveStack) noexcept {
    if (this == &moveStack) return *this;
    delete _pimpl;
    _pimpl = moveStack._pimpl;
    _containerType = moveStack._containerType;
    moveStack._pimpl = nullptr;
    return *this;
}

Stack::~Stack() {
    delete _pimpl;
}

void Stack::push(const ValueType& value) {
    _pimpl->push(value);
}

void Stack::pop() {
    _pimpl->pop();
}

const ValueType& Stack::top() const {
    return _pimpl->top();
}

bool Stack::isEmpty() const {
    return _pimpl->isEmpty();
}

size_t Stack::size() const {
    return _pimpl->size();
}
