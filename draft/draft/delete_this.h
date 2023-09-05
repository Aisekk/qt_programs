#ifndef DELETE_THIS_H
#define DELETE_THIS_H

#include <iostream>

namespace DeleteThis {

class SomeResource {
public:
    SomeResource() = default;

    void Close() {
        // Read state before deleting.
        const uint64_t id = id_;
        delete this;

        // Use what we read before.
        std::cout << "Closed resource with ID " << id << std::endl;
    }

private:
    // Delete via Close instead.
    //~SomeResource() = default;
    ~SomeResource() { std::cout << "Some resource with ID " << id_ << " destroyed" << std::endl; }

    const uint64_t id_ = 1;
};

}

#endif // DELETE_THIS_H
