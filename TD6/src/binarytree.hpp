#pragma once
#include <memory>
#include "smartNode.hpp"

struct BinaryTree {
    std::unique_ptr<SmartNode> root { nullptr };

    void insert(int value);
    bool remove(int value);
    void clear();
    bool contains(int value) const;
    size_t height() const;
};

bool contains(std::unique_ptr<SmartNode>& node, int value);
