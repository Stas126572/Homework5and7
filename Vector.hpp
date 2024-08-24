#pragma once
template<typename ElementType>
class Vector: public Obolochka<size_t, ElementType>
{
private:
    ElementType* values;
    size_t size;
public:
    size_t get_size() {return size+1;};
    Vector() {size = 0; values = new ElementType[0];}
    size_t GETPP(size_t index) override
    {
        return index;
    };
    ElementType GIE(size_t index) override
    {
        return values[index];
    }
    void child_insert(size_t index, ElementType element)
    {
        ElementType* new_values;
        if (values[size]!=((size_t)-1))
        {
            new_values = new ElementType[size+2];
            int plus_new_index = 0;
            for (int i = 0; i<=size; i++)
            {

                if (i==index) {
                    new_values[i+plus_new_index] = element;

                    plus_new_index++;
                }
                else {
                    new_values[i+plus_new_index] = values[i];

                }
            }
            delete[] values;
            values = new_values;
        }
        else
        {
            ElementType element2;
            ElementType element = values[index];
            values[index] = element;
            for (size_t i = index+1; i<size+1; i++)
            {
                element2 = values[i];
                values[i] = element;
                element = element2;
            }
        }
        

        size++;
    }
    virtual ElementType child_erase(size_t index)
    {
        ElementType element = GIE(index);
        ElementType* new_values = new ElementType[size-1];
        int minas_new_index = 0;
        for (int i = 0; i<size; i++)
        {
            if (i==index) {
                minas_new_index++;
            }
            else {
                new_values[i-minas_new_index] = values[i];
            }
        }
        delete[] values;
        values = new_values;
        size--;
        return element;
    }
};