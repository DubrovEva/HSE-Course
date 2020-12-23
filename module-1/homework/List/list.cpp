#include "list.h"

task::list::elem::elem(const int& new_value) : value(new_value) {}

task::list::list() {}

task::list::list(size_t count, const int& value) {
	while (lsize < count) {
		push_back(value);
	}
}

task::list::list(const list& other) {
    clear();
	for (elem * cur = other.first; cur != nullptr; cur = cur -> next) {
        push_back(cur -> value);
    }
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
        first = new elem { value };
        last = first;
	} else {
        elem * new_elem = new elem { value };
        new_elem -> prev = last;
		last -> next = new_elem;
        last = new_elem;
	}
	++lsize;
}

void task::list::pop_back() {
    if (lsize >= 2) {
        last -> prev -> next = nullptr;
        elem * penult = last -> prev;
        delete last;
        last = penult;
    } else if (lsize == 1) {
        delete last;
        first = last = nullptr;
    } else {
        return;
    }
    --lsize;
}

void task::list::push_front(const int& value) {
	if (empty()) {
        first = new elem { value };
        last = first;
	} else {
        elem * new_elem = new elem { value };
        new_elem -> next = first;
		first -> prev = new_elem;
        first = new_elem;
	}
	++lsize;
}

void task::list::pop_front() {
    if (lsize >= 2) {
        first -> next -> prev = nullptr;
        elem * second = first -> next;
        delete first;
        first = second;
    } else if (lsize == 1) {
        delete first;
        first = last = nullptr;
    } else {
        return;
    }
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
    elem * t = first;
    first = other.first;
    other.first = t;
    t = last;
    last = other.last;
    other.last = t;
    int m = lsize;
    lsize = m;
    other.lsize = m;
}

task::list::~list() {
    clear();
}

task::list& task::list::operator=(const list& other) {
	clear();
	for (elem * cur = other.first; cur != nullptr; cur = cur -> next) {
        push_back(cur -> value);
    }
    return *this;
}

void task::list::remove(const int& value) {
    if (empty())
        return;
	if (first -> value == value) {
        pop_front();
    } else {
        for (elem * cur_elem = first -> next; cur_elem != nullptr; cur_elem = cur_elem -> next) {
            if (cur_elem -> next == nullptr && cur_elem -> value == value) {
                pop_back();
            } else if (cur_elem -> value == value) {
                cur_elem -> prev -> next = cur_elem -> next;
                cur_elem -> next -> prev = cur_elem -> prev;
                --lsize;
                delete cur_elem;
                break;
            }  
	    } 
    }
}

void task::list::unique() {
	if (lsize <= 1) 
        return;
	
    for (elem * cur_elem = first -> next; cur_elem != nullptr; cur_elem = cur_elem -> next) {
        if (cur_elem -> next == nullptr && cur_elem -> value == cur_elem -> prev -> value) {
            pop_back();
            break;
        } else if (cur_elem -> value == cur_elem -> prev -> value) {
            cur_elem -> prev -> next = cur_elem -> next;
            cur_elem -> next -> prev = cur_elem -> prev;
            elem * temp = cur_elem -> prev;
            delete cur_elem;

            cur_elem = temp;
        }
	} 
}


void task::list::sort() {
    if (lsize <= 1)
        return;
	for (size_t i = 0; i < lsize; ++i) {
	    elem * cur_elem = first;
        for (size_t j = 0; j < lsize - 1; ++j) {
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
