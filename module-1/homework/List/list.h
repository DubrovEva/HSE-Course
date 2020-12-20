#pragma once
#include <cstddef>

namespace task {
    
    class list {
    private:
        class elem {
        public:
            elem* prev;
            elem* next;
            int value;
            elem(const int& new_value);
        };
        elem* first;
        elem* last;
        size_t lsize;

    public:
        list(); //+
        list(size_t count, const int& value = int()); //+
        list(const list& x); 
        ~list();
        list& operator=(const list& other);
        
        int& front();
        const int& front() const;

        int& back();
        const int& back() const;

        bool empty() const;
        size_t size() const;
        void clear();

        void push_back(const int& value);
        void pop_back();
        void push_front(const int& value);
        void pop_front();
        void resize(size_t count);
        void swap(list& other);

        void remove(const int& value);
        void unique();
        void sort();

    };

} 