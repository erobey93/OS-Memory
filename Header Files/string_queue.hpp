// Define class StringQueue that uses a MemoryPool for storing its strings:
// 1.	Takes a MemoryPool pointer in constructor
// 2.	Method void Insert(const char * s) copies the string into space allocated in the pool and adds it to the tail of the queue or throws a FullException if there is no space available in the pool
// 3.	method char * Peek() returns a pointer to the string in the pool at the head of the queue or nullptr if empty
// 4.	Method void Remove() removes the string at the head of the queue

#ifndef STRINGQUEUEPOOL_HPP
#define STRINGQUEUEPOOL_HPP

#include <queue>
#include <cstring>
#include "memory_pool.hpp"

namespace memory_management {

template <class T>
class StringQueuePool {
public:
    StringQueuePool() = delete;
    ~StringQueuePool() = default;

    explicit StringQueuePool(MemoryPool<T>* pool);

    void Insert(const char* string);
    const char* Peek() const;
    void Remove();

private:
    MemoryPool<T>* pool_{nullptr};
    std::queue<char*> theQueue_{};
};

template <class T>
StringQueuePool<T>::StringQueuePool(MemoryPool<T>* pool) : pool_(pool) {}

template <class T>
void StringQueuePool<T>::Insert(const char* string) {
    const size_t len = strlen(string) + 1;
    char* qstr = reinterpret_cast<char*>(pool_->Allocate(len));
    #ifdef _WIN32
    strcpy_s(qstr, len, string);
    #else
    strcpy(qstr, string);
    #endif
    theQueue_.push(qstr);
}

template <class T>
const char* StringQueuePool<T>::Peek() const {
    return theQueue_.empty() ? nullptr : theQueue_.front();
}

template <class T>
void StringQueuePool<T>::Remove() {
    if (!theQueue_.empty()) {
        char* pstr = theQueue_.front();
        pool_->Free(pstr);
        theQueue_.pop();
    }
}

} // namespace memory_management

#endif // STRINGQUEUEPOOL_HPP
