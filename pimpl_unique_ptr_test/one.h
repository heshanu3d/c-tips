#pragma once
#include <memory>
class two;

class one {
public:
    // ~one();
    ~one() {}
    std::unique_ptr<two> twou;
};

