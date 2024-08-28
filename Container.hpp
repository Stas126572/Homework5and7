#pragma once
template<typename IndexType, typename ElementType>
class Container
{
protected:
    virtual void child_insert(IndexType, ElementType) = 0;
    virtual ElementType child_erase(IndexType) = 0;
    virtual IndexType GetElementToPushOfIndex(size_t index) = 0;
public:
    virtual ElementType GetElementOfIndex(size_t index) = 0;
    virtual size_t get_size() = 0;
    void insert(ElementType element, size_t index) {child_insert(GetElementToPushOfIndex(index), element);};
    ElementType erase(size_t index) {return child_erase(GetElementToPushOfIndex(index));};
    void push_back(ElementType element) {insert(element, get_size()-1);}
    ElementType pop_back() {return erase(get_size()-1);}
    ElementType operator [] (size_t index) {return GetElementOfIndex(index);};

};