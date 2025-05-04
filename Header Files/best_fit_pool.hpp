// Define derived class BestFitPool that uses the best-fit algorithm the pool
#ifndef BESTFITPOOL_HPP
#define BESTFITPOOL_HPP

#include <string>
#include "memory_pool.hpp"

using std::vector;
using std::string;

namespace memory_management {

template <class T>
class BestFitPool : public MemoryPool<T> {
    using MemoryPool<T>::chunks_;

public:
    BestFitPool() = delete;
    explicit BestFitPool(size_t poolSize);
    vector<Chunk>::iterator FindAvailableChunk(size_t nBytes) override;
    string Name() const noexcept override;
};

template <class T>
BestFitPool<T>::BestFitPool(size_t poolSize) : MemoryPool<T>(poolSize) {}

template <class T>
vector<Chunk>::iterator BestFitPool<T>::FindAvailableChunk(size_t nBytes) {
    auto iterator = chunks_.begin();
    while (iterator != chunks_.end() && (iterator->Size() < nBytes || iterator->Allocated())) {
        ++iterator;
    }
    return iterator;
}

template <class T>
string BestFitPool<T>::Name() const noexcept {
    return "Best-Fit Pool";
}

}  // namespace memory_management

#endif  // BESTFITPOOL_HPP
