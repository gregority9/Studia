#include <iostream>
#include <stdexcept>
#include <fstream>

#define oo 1<<30

constexpr int MAXN = 1.5e3+5;

// long long l1 = 0;
// long long l2 = 0;

using namespace std;

struct heapStruct{
    int x;
    int y;
    int time;
};

class minHeap {
    private:
        heapStruct* heap;
        int capacity;
        int size;
 
        static int parent(int i) { return (i - 1) / 2; }
        static int leftChild(int i) { return (2 * i + 1); }
        static int rightChild(int i) { return (2 * i + 2); }

        void heapifyUp(int index) {
            while (index != 0 && heap[parent(index)].time > heap[index].time) {
                std::swap(heap[index], heap[parent(index)]);
                index = parent(index);
            }
        }
        void heapifyDown(int index) {
            int smallest = index;
            int left = leftChild(index);
            int right = rightChild(index);

            if (left < size && heap[left].time < heap[smallest].time) {
                smallest = left;
            }
            if (right < size && heap[right].time < heap[smallest].time) {
                smallest = right;
            }
            if (smallest != index) {
                std::swap(heap[index], heap[smallest]);
                heapifyDown(smallest);
            }
        }
        void resize() {
            capacity *= 2;
            heapStruct* newHeap = new heapStruct[capacity];
            for (int i = 0; i < size; ++i)
                newHeap[i] = heap[i];
            delete[] heap;
            heap = newHeap;
        }

    public:
        minHeap(int initialCapacity = 10) : capacity(initialCapacity), size(0) {
            heap = new heapStruct[capacity];
        }

        ~minHeap() {
            delete[] heap;
        }

        void insert(heapStruct key) {
            if(size == capacity) {
                resize();
            }
            heap[size] = key;
            heapifyUp(size);
            ++size;
        }

        heapStruct extractMin() {
            heapStruct root = heap[0];
            heap[0] = heap[size - 1];
            --size;
            heapifyDown(0);
            return root;
        }
        bool isEmpty() const {
            return size == 0;
        }
};

struct pos{
    int x;
    int y;
};

struct train{
    pos start;
    pos end;
    int duration;
    int time;
};

int max(int a, int b){
    if(a>b) return a;
    return b;
}

void djikstraAlgorithm(pos start, pos end, int sizeX, int sizeY, int **map, train trains[], int nTrains, minHeap& heap, int **dist/* , int trainsAvailable[1505][1505][50] */){
    // cout << "sizeX: " << sizeX << " sizeY: " << sizeY << endl;
    heap.insert({start.x, start.y, 0});
    while(!heap.isEmpty()){
    // l1++;
        heapStruct current = heap.extractMin();
        // cout << current.x << " " << current.y << " " << current.time << endl;
        if(dist[current.x][current.y] != oo) continue;
        if(current.x == end.x && current.y == end.y){

            cout << current.time << endl;
            // cout << l1 << endl << l2 << endl;
            // for(int i=0; i<sizeY; i++){
            //     for(int j=0; j<sizeX; j++){
            //         cout << dist[i][j] << " ";
            //     }
            //     cout << endl;
            // }
            return;
        }
        // l2++;
        dist[current.x][current.y] = current.time;
        if(current.x - 1 >= 0 && dist[current.x - 1][current.y] == oo){
            heap.insert({current.x-1, current.y, max(current.time+1, current.time + 1 - map[current.x][current.y] + map[current.x - 1][current.y])});
        }
        if(current.x + 1 < sizeY && dist[current.x + 1][current.y] == oo){
            heap.insert({current.x + 1, current.y, max(current.time+1, current.time + 1 - map[current.x][current.y] + map[current.x + 1][current.y])});
        }
        if(current.y - 1 >= 0 && dist[current.x][current.y - 1] == oo){
            heap.insert({current.x, current.y - 1, max(current.time+1, current.time + 1 - map[current.x][current.y] + map[current.x][current.y - 1])});
        }
        if(current.y + 1 < sizeX && dist[current.x][current.y + 1] == oo){
            heap.insert({current.x, current.y + 1, max(current.time+1, current.time + 1 - map[current.x][current.y] + map[current.x][current.y + 1])});
        }
        // int j = 0;
        // while(trainsAvailable[current.x][current.y][j] != 0){
        //     train ciufcia = trains[trainsAvailable[current.x][current.y][j]];
        //     heap.insert({ciufcia.end.x, ciufcia.end.y, current.time + ciufcia.time - current.time%ciufcia.time + ciufcia.duration});
        // }
    }

}

int main() {
    //ifstream cin("w.in");
    cin.tie(0); cout.tie(0);
    ios::sync_with_stdio(0);
    int sizeX, sizeY;
    pos start, end;
    int nTrains;
    // for(int i=0; i<MAXN; i++){
    //     for(int j=0; j<MAXN; j++){
    //         trainAvailable[i][j][0] = 0;
    //     }
    // }
    cin >> sizeX >> sizeY;
    cin >> start.y >> start.x;
    cin >> end.y >> end.x;
    // cout << start.x << start.y << end.x << end.y << endl;
    cin >> nTrains;
    train *trains = new train[nTrains];
    // for(int i = 0; i < nTrains; i++){
    //     cin >> trains[i].start.x >> trains[i].start.y;
    //     cin >> trains[i].end.x >> trains[i].end.y;
    //     int j = 0;
    //     while(trainAvailable[trains[i].start.x][trains[i].start.y][j] != 0) j++;
    //     trainAvailable[trains[i].start.x][trains[i].start.y][j] = i;
    //     trainAvailable[trains[i].start.x][trains[i].start.y][j+1] = 0;
    //     cin >> trains[i].duration >> trains[i].time;
    // }

    //sizeX = x = 9
    //sizeY = y = 8
    //[x][y]

    int **map = new int*[sizeY];
    for(int i=0; i<sizeY; i++){
        map[i] = new int[sizeX];
    }

    for(int i = 0; i < sizeY; i++){
        for(int j = 0; j < sizeX; j++){
            cin >> map[i][j];
        }
    }

    // for(int i = 0; i < sizeY; i++){
    //     for(int j = 0; j < sizeX; j++){
    //         cout << map[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    minHeap heap;
    heap.insert({start.x, start.y, 0});
    int **dist = new int*[sizeY];
    for(int i = 0; i < sizeY; i++){
        dist[i] = new int[sizeX];
    }

    for(int i=0; i<sizeY; i++){
        for(int j=0; j<sizeX; j++){
            dist[i][j] = oo;
        }
    }

    // for(int i=0; i<sizeY; i++){
    //     for(int j=0; j<sizeX; j++){
    //         cout << dist[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    //cout << "jest gitówa";

    djikstraAlgorithm(start, end, sizeX, sizeY, map, trains, nTrains, heap, dist/* , trainAvailable */);
}