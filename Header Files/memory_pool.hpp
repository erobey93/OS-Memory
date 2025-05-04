#ifndef MEMORYPOOL_HPP
#define MEMORYPOOL_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "chunk.hpp"
#include "adt_exception.hpp"

using std::vector;
using std::string;

namespace memory_management {

// Custom exception for out of memory conditions
class OutOfMemoryException : public AdtException {
public:
    explicit OutOfMemoryException(const std::string& msg) 
        : AdtException("Out of Memory: " + msg) {}
};

template<class T>
class MemoryPool {
public:
    explicit MemoryPool(size_t poolSize);
    MemoryPool() = delete;
    virtual ~MemoryPool();

    virtual void* Allocate(size_t nBytes);
    virtual void Free(void* block);
    virtual void DebugPrint();
    virtual string Name() const noexcept = 0;

protected:
    T* pool_{nullptr};
    size_t length_{0};
    vector<Chunk> chunks_;

    virtual vector<Chunk>::iterator FindAvailableChunk(size_t nBytes) = 0;
};

template<class T>
MemoryPool<T>::MemoryPool(size_t poolSize) : length_(poolSize) {
    pool_ = new T[poolSize];
    chunks_.emplace_back(0, poolSize, false);
}

template<class T>
MemoryPool<T>::~MemoryPool() {
    delete[] pool_;
    chunks_.clear();
}

template<class T>
void* MemoryPool<T>::Allocate(size_t nBytes) {
    if (nBytes == 0) return nullptr;

    auto chunkIt = FindAvailableChunk(nBytes);
    
    if (chunkIt == chunks_.end()) {
        throw OutOfMemoryException("No available memory block of size " + std::to_string(nBytes));
    }

    size_t originalSize = chunkIt->Size();
    size_t startingIndex = chunkIt->StartingIndex();

    chunkIt->Allocated(true);
    
    if (originalSize > nBytes) {
        chunks_.emplace(chunkIt + 1, startingIndex + nBytes, 
                       originalSize - nBytes, false);
        chunkIt->Size(nBytes);
    }

    return static_cast<void*>(pool_ + startingIndex);
}

template<class T>
void MemoryPool<T>::Free(void* block) {
    if (!block) return;

    T* ptr = static_cast<T*>(block);
    size_t index = ptr - pool_;

    for (auto it = chunks_.begin(); it != chunks_.end(); ++it) {
        if (it->StartingIndex() == index) {
            it->Allocated(false);

            auto nextIt = it + 1;
            if (nextIt != chunks_.end() && !nextIt->Allocated()) {
                it->Size(it->Size() + nextIt->Size());
                chunks_.erase(nextIt);
            }

            if (it != chunks_.begin()) {
                auto prevIt = it - 1;
                if (!prevIt->Allocated()) {
                    prevIt->Size(prevIt->Size() + it->Size());
                    chunks_.erase(it);
                }
            }
            break;
        }
    }
}

template<class T>
void MemoryPool<T>::DebugPrint() {
    std::cout << Name();
    for (const auto& chunk : chunks_) {
        std::cout << "\n\tIndex: " << chunk.StartingIndex() 
                  << " Size: " << chunk.Size() 
                  << " Allocated: " << (chunk.Allocated() ? "true" : "false");
    }
}

}  // namespace memory_management

#endif  // MEMORYPOOL_HPP
