#include "list.h"

task::list::elem::elem(const int& new_value) {
    value = new_value;
    prev = next = nullptr;
}

task::list::list() {
    first = nullptr;
    last = nullptr;
    lsize = 0;
}


task::list::list(size_t count, const int& value) {
	while (lsize < count) {
		push_back(value);
	}
}

task::list::list(const list& other) : list() {
	*this = other;
}

int& task::list::front() {
	return first->value;
}

const int& task::list::front() const {
	return first->value;
}

int& task::list::back() {
	return last->value;
}

const int& task::list::back() const {
	return last->value;
}

bool task::list::empty() const {
	return lsize == 0;
}

size_t task::list::size() const {
	return lsize;	
}

void task::list::clear() {
  while (lsize) 
    pop_back();
}

void task::list::push_back(const int& value) {
	if (lsize == 0) {
        first = last = new elem { value };
	} else {
        elem * new_elem = new elem { value };
		last -> next = new_elem;
        last = new_elem;
	}
	++lsize;
}

void task::list::pop_back() {
    last -> prev -> next = nullptr;
    elem * penult = last -> prev;
	delete last;
    last = penult;
	--lsize;
}

void task::list::push_front(const int& value) {
	if (lsize == 0) {
        first = last = new elem { value };
	} else {
        elem * new_elem = new elem { value };
		first -> prev = new_elem;
        first = new_elem;
	}
	++lsize;
}

void task::list::pop_front() {
	first -> next -> prev = nullptr;
    elem * second = first -> next;
	delete first;
    first = second;
	--lsize;
}

void task::list::resize(size_t count) {
    while (lsize < count) {
        push_back(0);
    }
    while(lsize > count) {
        pop_back();
    }
}

void task::list::swap(list& other) {
    list * current = this;
    *this = other;
    other = * current;
}

task::list::~list() {
	task::list::clear();
}

task::list& task::list::operator=(const list& other) {
	clear();
	first = new elem ( (other.first)-> value);
    elem * cur_elem = (other.first) -> next;
	for(int i = 0; i < other.lsize; ++i) {
		push_back(cur_elem -> value);
		cur_elem = cur_elem -> next;
        if (i == other.lsize - 1)
            last = cur_elem;
	} 
    lsize = other.lsize;
    return *this;
}

void task::list::remove(const int& value) {
	if (first -> value == value) {
        pop_front();
    } else {
        elem * cur_elem = first -> next;
        for(int i = 0; i < lsize; ++i) {
            if (i == lsize - 1 && cur_elem -> value == value) {
                pop_back();
            } else if (cur_elem -> value == value) {
                cur_elem -> prev -> next = cur_elem -> next;
                cur_elem -> next -> prev = cur_elem -> prev;
                delete cur_elem;
                break;
            }
            cur_elem = cur_elem -> next;
            
	    } 
    }
}

void task::list::unique() {
	if (empty()) 
        return;
	elem * cur_elem = first -> next;
    for (int i = 0; i < lsize; ++i) {
        if (i == lsize && cur_elem -> value == cur_elem -> prev -> value) {
            pop_back();
        } else if (cur_elem -> value == cur_elem -> prev -> value) {
            cur_elem -> prev -> next = cur_elem -> next;
            cur_elem -> next -> prev = cur_elem -> prev;
            delete cur_elem;
            break;
        }
        cur_elem = cur_elem -> next;        
	} 
}

void task::list::sort() {
	for (int i = 0; i < lsize; ++i) {
	    elem * cur_elem = first;
        for (int j = 0; j < lsize - 1; ++j) {
            if ( (cur_elem -> value) > (cur_elem -> next -> value) ) {
                if (j == 0 && j == lsize - 1) {
                    first = last;
                    last = cur_elem;
                } else if (j == 0) {
                    first -> next -> next -> prev = first;
                    elem * t = first;
                    first = first -> next;
                    first -> next = t;
                } else if (j == lsize - 1) {
                    cur_elem -> prev -> next = last;
                    elem * t = last;
                    last = cur_elem;
                    cur_elem = t;
                } else {
                    cur_elem -> prev -> next = cur_elem -> next;
                    cur_elem -> next -> next -> prev = cur_elem;
                    elem * t = cur_elem -> next;
                    cur_elem -> next = cur_elem;
                    cur_elem = t;
                }
            }
            cur_elem = cur_elem -> next;
        }
    }
}