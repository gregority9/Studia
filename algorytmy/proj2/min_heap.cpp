#include <iostream>
#include <stdexcept>

class minHeap {
    private:
        int* heap;
        int capacity;
        int size;
 
        int parent(int i) { return (i - 1) / 2; }
        int leftChild(int i) { return (2 * i + 1); }
        int rightChild(int i) { return (2 * i + 2); }

        void heapifyUp(int index) {
            while (index != 0 && heap[parent(index)] > heap[index]) {
                std::swap(heap[index], heap[parent(index)]);
                index = parent(index);
            }
        }
        void heapifyDown(int index) {
            int smallest = index;
            int left = leftChild(index);
            int right = rightChild(index);

            if (left < size && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < size && heap[right] < heap[smallest]) {
                smallest = right;
            }
            if (smallest != index) {
                std::swap(heap[index], heap[smallest]);
                heapifyDown(smallest);
            }
        }
        void resize() {
            capacity *= 2;
            int* newHeap = new int[capacity];
            for (int i = 0; i < size; ++i)
                newHeap[i] = heap[i];
            delete[] heap;
            heap = newHeap;
        }

    public:
        minHeap(int initialCapacity = 10) : capacity(initialCapacity), size(0) {
            heap = new int[capacity];
        }

        ~minHeap() {
            delete[] heap;
        }

        void insert(int key) {
            if(size == capacity) {
                resize();
            }
            heap[size] = key;
            heapifyUp(size);
            ++size;
        }

        int extractMin() {
            if(size <= 0){
                throw std::out_of_range("Heap is empty");
            }
            int root = heap[0];
            heap[0] = heap[size - 1];
            --size;
            heapifyDown(0);
            return root;
        }
        int getMin() const {
            if(size <= 0){
                throw std::out_of_range("Heap is empty");
            }
            return heap[0];
        }
        bool isEmpty() const {
            return size == 0;
        }
};