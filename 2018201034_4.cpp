/*
 * VECTOR CLASS by Rushit M Jasani : 2018201034
 */

#include <iostream>
#include <cstdlib>
using namespace std;
class vector
{
  private:
    int size;
    int vec_capacity;
    int *vec;

  public:
    vector()
    {
        vec = (int *)malloc(2 * sizeof(int));
        if (!vec)
        {
            cout << "Memory Alloc Failed.";
            exit(1);
        }
        else
        {
            vec_capacity = 2;
            size = 0;
        }
    }
    vector(int n)
    {
        //always allocate size in multiple of 2.
        int size_temp = n, count = 1;
        while (size_temp >>= 1)
            count++;
        vec = (int *)malloc((1 << count) * sizeof(int));
        for (int i = 0; i < n; i++)
            vec[i] = 0;
        if (!vec)
        {
            cout << "Memory Alloc Failed.";
            exit(1);
        }
        else
        {
            vec_capacity = (1 << count);
            size = n;
        }
    }
    vector(int n, int x)
    {
        int size_temp = n, count = 1;
        while (size_temp >>= 1)
            count++;
        vec = (int *)malloc((1 << count) * sizeof(int));
        for (int i = 0; i < n; i++)
            vec[i] = x;
        if (!vec)
        {
            cout << "Memory Alloc Failed.";
            exit(1);
        }
        else
        {
            vec_capacity = 1 << count;
            size = n;
        }
    }
    int v_size()
    {
        return size;
    }
    int getcapacity()
    {
        return vec_capacity;
    }
    void push_back(int x)
    {
        cout << size << " ## " << vec_capacity << endl;
        if (size == vec_capacity)
        {
            vec_capacity = vec_capacity * 2;
            void *tmp = realloc(vec, vec_capacity * sizeof(int));

            if (tmp == NULL)
            {
                cout << "Memory Alloc Failed.";
                exit(1);
            }
            vec = (int *)tmp;
        }
        vec[size++] = x;
    }
    void pop_back()
    {
        if (size > 0)
        {
            size--;
        }
        else
            cout << "Vector Empty" << endl;

        if (size == (vec_capacity >> 1)-1 )
        {
            vec_capacity >>= 1;
            void *tmp = realloc(vec, vec_capacity * sizeof(int));
            if (tmp == NULL)
            {
                cout << "Memory Alloc Failed.";
                exit(1);
            }
            vec =(int *) tmp;
        }
    }
    int operator[](int i)
    {
        if (i < 0 || i >= size)
        {
            cout << "invalid index value" << endl;
            return -1;
        }
        else
            return vec[i];
    }
    int front()
    {
        if (size > 0)
        {
            return vec[0];
        }
        else
        {
            cout << "Vector Empty" << endl;
            return -1;
        }
    }
    int back()
    {
        if (size > 0)
        {
            return vec[size - 1];
        }
        else
        {
            cout << "Vector Empty" << endl;
            return -1;
        }
    }
    void insert(int i, int x)
    {
        if (i < 0 || i > size - 1)
            cout << "No Negative Indexed supported." << endl;
        push_back(x);
        for (int iter = size - 1; iter > i; iter--)
            vec[iter] = vec[iter - 1];
        vec[i] = x;
    }
    void erase(int i)
    {
        if (i < 0 || i > size - 1)
            cout << "No Negative Indexed supported." << endl;
        for (int iter = i; iter < size - 1; iter++)
            vec[iter] = vec[iter + 1];
        size--;
        if (size == (vec_capacity >> 1)-1 )
        {
            vec_capacity >>= 1;
            void *tmp = realloc(vec, vec_capacity * sizeof(int));
            if (tmp == NULL)
            {
                cout << "Memory Alloc Failed.";
                exit(1);
            }
            vec =(int *) tmp;
        }
    }
    int capacity()
    {
        return vec_capacity;
    }
    void clear()
    {
        free(vec);
        vec = (int *)malloc(2 * sizeof(int));
        if (!vec)
        {
            cout << "Memory Alloc Failed.";
            exit(1);
        }
        else
        {
            vec_capacity = 2;
            size = 0;
        }
    }
};