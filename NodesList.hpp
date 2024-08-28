#pragma once
#include "Container.hpp"



template<typename ElementType>
struct Node
{
    Node* next;
    Node* prev;
    ElementType data;
};

template<typename ElementType>
class NodesList;

template<typename ElementType>
class Iterator
{
    Node<ElementType>* I;
    friend NodesList<ElementType>;
private:
    Iterator(Node<ElementType>*I)
    {
        this->I = I;
    }

public:
    ElementType operator*()
    {
        return get();
    } 
    ElementType get()
    {
        return I->data;   
    }
};

template<typename ElementType>
class NodesList :public Container<Node<ElementType>*, ElementType>
{
    Node<ElementType>* last;
    Node<ElementType>* first;
    size_t size;
private:


    Iterator<ElementType>begin()
    {
        Iterator<ElementType>it{first};
        return it;
    }
    Iterator<ElementType>end()
    {
        Iterator<ElementType>it{last};
        return it;
    }
    void child_insert(Node<ElementType>*index, ElementType element) override 
    {
        Node<ElementType>* this_node = new Node<ElementType>{};
        this_node->data = element;
        

        index->next->prev = this_node;
        this_node->next = index->next;
        this_node->prev = index;
        index->next = this_node;

        size++;
    };
    ElementType child_erase(Node<ElementType>*index) override {
        index->prev->next = index->next;
        index->next->prev = index->prev;
        ElementType element = index->data;
        delete index;
        size--;
        return element;
    }
    Node<ElementType>* GetElementToPushOfIndex(size_t index) override
    {
        Node<ElementType>* return_element;
        size_t sredni_index = size / 2;
        if (index > sredni_index)
        {
            return_element = last;
            for (int i = size; i!=index; i--)
            {
                return_element = return_element->prev;
            }
        }
        else
        {
            return_element = first;
            for (int i = 0; i<index; i++)
            {
                return_element = return_element->next;
            }
        }
        return return_element;
    }
public:
    NodesList(NodesList&& rv)
    {
        this->last = rv->last;
        this->first = rv->first;
        Node<ElementType>* first_rv = rv->first;
        Node<ElementType>* two;
        ElementType el;
        for (size_t i = 0; i < rv->size; i++)
        {
            first_rv->data = el;
            two = first_rv->next;
            first_rv->next = nullptr;
            first_rv = two;
        }
    }
    NodesList(NodesList& nd)
    {
        Nodes<ElementType>* element = last;
        Nodes<ElementType>* element2 = nd->last;
        for (int i = 0; i < size; i++)
        {
            element->data = element2->data;
            element = element->prev;
            element2 = element2->prev;
        }       
    }

    ~NodesList()
    {
        Node<ElementType>* element2;
        for (int i = 0; i<size; i++)
        {
            element2 = last->prev;
            delete last;
            last = element2;
        }
        delete element2;
        
    }
    size_t get_size() override {
        return size;
    }
    NodesList() {
        size = 1;
        first = new Node<ElementType>{};
        last = new Node<ElementType>{};
        first->next = last;
        last->prev = first;
    }
    ElementType GetElementOfIndex(size_t index) override
    {
        return GetElementToPushOfIndex(index+1)->data;
    }
};