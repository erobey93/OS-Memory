#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <cstddef>  // for size_t

class Chunk {
public:
    Chunk() = delete;
    ~Chunk() = default;

    explicit Chunk(size_t starting_index, size_t pool_size, bool allocated);

    Chunk(const Chunk& copy) = default;
    Chunk(Chunk&& rhs) = default;
    Chunk& operator=(const Chunk& rhs) = default;
    Chunk& operator=(Chunk&& move) noexcept = default;

    size_t StartingIndex() const noexcept;
    void StartingIndex(size_t new_index) noexcept;

    size_t Size() const noexcept;
    void Size(size_t new_size) noexcept;

    bool Allocated() const noexcept;
    void Allocated(bool allocated) noexcept;

private:
    size_t startingIndex{0};
    size_t size_{0};
    bool allocated{false};
};

inline Chunk::Chunk(size_t si, size_t s, bool a) : startingIndex(si), size_(s), allocated(a) {}

inline size_t Chunk::StartingIndex() const noexcept {
    return startingIndex;
}

inline void Chunk::StartingIndex(size_t new_index) noexcept {
    startingIndex = new_index;
}

inline size_t Chunk::Size() const noexcept {
    return size_;
}

inline void Chunk::Size(size_t new_size) noexcept {
    size_ = new_size;
}

inline bool Chunk::Allocated() const noexcept {
    return allocated;
}

inline void Chunk::Allocated(bool new_allocated) noexcept {
    allocated = new_allocated;
}

#endif // CHUNK_HPP
