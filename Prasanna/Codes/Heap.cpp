#include <iostream>
#include <vector>
#include <string>

class MaxHeap {
private:
    std::vector<std::pair<int, std::string>> heap;

    void HeapBottomUp() {
        int n = heap.size();
        for (int i = n / 2 - 1; i >= 0; --i) {
            int k = i;
            auto v = heap[k];
            bool heapified = false;

            while (!heapified && 2 * k + 1 < n) {
                int j = 2 * k + 1; 
                if (j < n - 1 && heap[j].first < heap[j + 1].first) 
                    j++;

                if (v.first >= heap[j].first)
                    heapified = true;
                else {
                    heap[k] = heap[j];
                    k = j;
                }
            }
            heap[k] = v;
        }
    }

    void heapifyDown(int idx) {
        int n = heap.size();
        int k = idx;
        auto v = heap[k];
        bool heapified = false;

        while (!heapified && 2 * k + 1 < n) {
            int j = 2 * k + 1; // Left child
            if (j < n - 1 && heap[j].first < heap[j + 1].first)
                j++;

            if (v.first >= heap[j].first)
                heapified = true;
            else {
                heap[k] = heap[j];
                k = j;
            }
        }
        heap[k] = v;
    }

public:
    MaxHeap() {}

    void buildHeap(const std::vector<std::pair<int, std::string>>& activities) {
        heap = activities;
        HeapBottomUp();
    }

    void insert(int priority, const std::string& activity) {
        heap.push_back({priority, activity});
        int i = heap.size() - 1;
        while (i > 0 && heap[(i - 1) / 2].first < heap[i].first) { 
            std::swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void deleteMax() {
        if (heap.empty()) {
            std::cout << "Heap is empty, cannot delete." << std::endl;
            return;
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    void printHeap() {
        if (heap.empty()) {
            std::cout << "Heap is empty." << std::endl;
            return;
        }
        std::cout << "Heap elements (priority, activity):" << std::endl;
        for (const auto& p : heap) {
            std::cout << "(" << p.first << ", " << p.second << ") ";
        }
        std::cout << std::endl;
    }

    void printRoot() {
        if (!heap.empty()) {
            std::cout << "Root of the heap (Max element): (" << heap[0].first << ", " << heap[0].second << ")" << std::endl;
        } else {
            std::cout << "Heap is empty." << std::endl;
        }
    }
};
