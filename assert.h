#pragma once
#include <iostream>
#include <cassert>

void testMap() {
    BST<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    BST<int> mappedTree = tree.map<int>([](int val) { return val * val; });
    std::vector<int> expectedMapped = {9, 25, 49};

    assert(mappedTree.inorderTraversal1() == expectedMapped);
}

void testWhere() {
    BST<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    BST<int> filteredTree = tree.where([](int val) { return val > 4; });

    std::vector<int> expectedFiltered = {5, 7};

    assert(filteredTree.inorderTraversal1() == expectedFiltered);
}

void testExtractSubtree() {
    BST<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);

    BST<int> extractedTree = tree.extractSubtree(3);
    std::vector<int> expectedExtract = {1,3,4};

    assert(extractedTree.inorderTraversal1() == expectedExtract);
}

void test() {

    BST<int> testTree;
    testTree.insert(5);
    testTree.insert(3);
    testTree.insert(7);
    testTree.insert(1);
    testTree.insert(4);

    assert(testTree.search(5) != nullptr);
    assert(testTree.search(3) != nullptr);
    assert(testTree.search(7) != nullptr);
    assert(testTree.search(1) != nullptr);
    assert(testTree.search(4) != nullptr);
    assert(testTree.search(2) == nullptr);

    std::vector<int> bfsResult = testTree.bfs();
    assert(bfsResult == std::vector<int>({5, 3, 7, 1, 4}));

    std::vector<int> inorderResult = testTree.inorderTraversal();
    assert(inorderResult == std::vector<int>({1, 3, 4, 5, 7}));

    testExtractSubtree();

    testMap();
    testWhere();

    Heap<int> heap;
    heap.insert(5);
    heap.insert(10);
    heap.insert(3);
    assert(heap.size() == 3);
    assert(heap.top() == 10);

    assert(heap.extractMax() == 10);
    assert(heap.size() == 2);
    assert(heap.top() == 5);

    Heap<int> heap2({1, 2, 3, 4});
    auto mappedHeap = heap2.map<double>([](int x) { return x * 1.5; });
    assert(mappedHeap.size() == 4);
    assert(mappedHeap.top() == 6.0);

    auto filteredHeap = heap2.where([](int x) { return x % 2 == 0; });
    assert(filteredHeap.size() == 2);
    assert(filteredHeap.top() == 4);

    Heap<int> heap3({6, 7, 8});
    auto mergedHeap = heap2.mergeHeaps(heap2, heap3);
    assert(mergedHeap.size() == 7);
    assert(mergedHeap.top() == 8);

    assert(heap3.extractMax() == 8);
    assert(heap3.size() == 2);
    assert(heap3.top() == 7);

    Heap<int> emptyHeap;
    assert(emptyHeap.size() == 0);

}
