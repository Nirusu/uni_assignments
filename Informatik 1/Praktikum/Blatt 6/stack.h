#include <iostream>
#include <cstdlib>

using namespace std;

template <typename T>


class Stack
{
private:
    class Object {
    public:
       Object *next_object = nullptr;
        T data;
    };
    Object *m_top;
public:
    Stack() {m_top = nullptr;}
    bool empty()
    {
        if (m_top == nullptr)
        {
            return true;
        }
        else
            return false;
    }
    void push(T x) {
    Object *obj = new Object;
        obj->data = x;
        obj->next_object = m_top;
        m_top = obj;
    }
    T pop()
    {
        if (!empty())
        {
           Object *obj = m_top;
            T returnValue = m_top->data;
            m_top = obj->next_object;
            delete obj;// --> stürzt beim 2. Clear ab
            return returnValue;
        }
        else
        {
            cout << "Der Stapel ist leer! Beende das Programm." << endl;
            exit(1);
        }
    }
    T top()
    {
        if (!empty())
        {
            return m_top->data;
        }
        else
        {
            cout << "Der Stapel ist leer! Beende das Programm." << endl;
            exit(1);
        }
    }
    void clear()
    {
        while (!empty())
        {
            pop();
        }
    }
};