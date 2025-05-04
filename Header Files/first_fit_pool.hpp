#ifndef FIRSTFITPOOL_HPP
#define FIRSTFITPOOL_HPP

#include <string>
#include "memory_pool.hpp"

using std::vector;
using std::string;

namespace memory_management {

template <class T>
class FirstFitPool : public MemoryPool<T> {
    using MemoryPool<T>::chunks_;

public:
    FirstFitPool() = delete;
    explicit FirstFitPool(size_t poolSize);
    vector<Chunk>::iterator FindAvailableChunk(size_t nBytes) override;
    string Name() const noexcept override;
};

template <class T>
FirstFitPool<T>::FirstFitPool(size_t poolSize) : MemoryPool<T>(poolSize) {}

template <class T>
vector<Chunk>::iterator FirstFitPool<T>::FindAvailableChunk(size_t nBytes) {
    for (auto it = chunks_.begin(); it != chunks_.end(); ++it) {
        if (!it->Allocated() && it->Size() >= nBytes) {
            return it;
        }
    }
    return chunks_.end();
}

template <class T>
string FirstFitPool<T>::Name() const noexcept {
    return "First-Fit Pool";
}

}  // namespace memory_management

#endif  // FIRSTFITPOOL_HPP
