#include <iostream>
#include "first_fit_pool.hpp"
#include "best_fit_pool.hpp"
#include "string_queue.hpp"

using namespace memory_management;
using uchar_t = unsigned char;

int main() {
    try {
        // a simple test ....
        // current state
        // 10 free first fit
        // 10 allocated
        // 5 free best fit
        // 10 allocated
        // 65 Free
        // want to
        // allocate 5 bytes
        FirstFitPool<uchar_t> ffp(100);
        ffp.DebugPrint();
        std::cout << "\n";

        uchar_t* p0 = static_cast<uchar_t*>(ffp.Allocate(10));
        ffp.DebugPrint();
        std::cout << "\n";

        uchar_t* p1 = static_cast<uchar_t*>(ffp.Allocate(10));
        ffp.DebugPrint();
        std::cout << "\n";

        uchar_t* p2 = static_cast<uchar_t*>(ffp.Allocate(10));
        ffp.DebugPrint();
        std::cout << "\n";

        ffp.Free(p1);
        ffp.DebugPrint();
        std::cout << "\n";

        ffp.Free(p0);
        ffp.DebugPrint();
        std::cout << "\n";

        ffp.Free(p2);
        ffp.DebugPrint();
        std::cout << "\n";

        // TODO:
        // need implement StringQueue and demonstrate above with the queue
        // insert("012345678") -> allocate 10 bytes
        // insert("abcdefghi") -> allocate 10 bytes
        // remove() -> free the first chunk of 18 bytes
        // what is the sequence of insert() / remove() that creates the pattern we need?
        StringQueuePool<uchar_t> queue(&ffp);
        
        queue.Insert("012345678");
        queue.Insert("abcdefghi");
        std::cout << "Peek result: " << queue.Peek() << "\n";
        queue.Remove();
        
        // Clean up
        while (queue.Peek() != nullptr) {
            queue.Remove();
        }
    }
    catch (const AdtException& ex) {
        std::cerr << ex;
    }
    
    return 0;
}
