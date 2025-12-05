#include <iostream>
#include <string>

using namespace std;

const int INF_COST = 2147483647;

struct IntPair
{
    int first;
    int second;
    IntPair() : first(0), second(0) {}
    IntPair(int a, int b) : first(a), second(b) {}

    bool operator<(const IntPair &other) const { return first < other.first; }
    bool operator>(const IntPair &other) const { return first > other.first; }
};

struct StringPair
{
    string first;
    string second;
    StringPair() {}
    StringPair(string a, string b) : first(a), second(b) {}

    bool operator==(const StringPair &other) const { return first == other.first && second == other.second; }
};

class IntVector
{
private:
    int *arr;
    int capacity;
    int currentSize;

public:
    IntVector()
    {
        capacity = 10;
        currentSize = 0;
        arr = new int[capacity];
    }

    IntVector(int size, int initialVal)
    {
        capacity = size > 10 ? size : 10;
        currentSize = size;
        arr = new int[capacity];
        for (int i = 0; i < size; i++)
            arr[i] = initialVal;
    }

    // --- CRITICAL FIX: Copy Constructor (Rule of Three) ---
    // Needed because PathResult returns this vector by value.
    IntVector(const IntVector &other)
    {
        capacity = other.capacity;
        currentSize = other.currentSize;
        arr = new int[capacity];
        for (int i = 0; i < currentSize; i++)
        {
            arr[i] = other.arr[i];
        }
    }

    // --- CRITICAL FIX: Assignment Operator ---
    IntVector &operator=(const IntVector &other)
    {
        if (this != &other)
        {
            delete[] arr;
            capacity = other.capacity;
            currentSize = other.currentSize;
            arr = new int[capacity];
            for (int i = 0; i < currentSize; i++)
            {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    ~IntVector()
    {
        if (arr)
            delete[] arr;
    }

    void push_back(int data)
    {
        if (currentSize == capacity)
        {
            int newCapacity = capacity * 2;
            int *temp = new int[newCapacity];
            for (int i = 0; i < currentSize; i++)
                temp[i] = arr[i];
            delete[] arr;
            arr = temp;
            capacity = newCapacity;
        }
        arr[currentSize++] = data;
    }

    void pop_back()
    {
        if (currentSize > 0)
            currentSize--;
    }
    int &operator[](int index) { return arr[index]; }
    int size() const { return currentSize; }
    bool empty() const { return currentSize == 0; }

    void reverse()
    {
        int start = 0, end = currentSize - 1;
        while (start < end)
        {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }
    }
};

// Replaces MyVector<IntPair> (Used in Heaps)
class IntPairVector
{
private:
    IntPair *arr;
    int capacity;
    int currentSize;

public:
    IntPairVector()
    {
        capacity = 10;
        currentSize = 0;
        arr = new IntPair[capacity];
    }

    ~IntPairVector()
    {
        if (arr)
            delete[] arr;
    }

    void push_back(IntPair data)
    {
        if (currentSize == capacity)
        {
            int newCapacity = capacity * 2;
            IntPair *temp = new IntPair[newCapacity];
            for (int i = 0; i < currentSize; i++)
                temp[i] = arr[i];
            delete[] arr;
            arr = temp;
            capacity = newCapacity;
        }
        arr[currentSize++] = data;
    }

    void pop_back()
    {
        if (currentSize > 0)
            currentSize--;
    }
    IntPair &operator[](int index) { return arr[index]; }
    int size() const { return currentSize; }
    bool empty() const { return currentSize == 0; }
};

// Replaces MyVector<StringPair> (Used in Auth)
class StringPairVector
{
private:
    StringPair *arr;
    int capacity;
    int currentSize;

public:
    StringPairVector()
    {
        capacity = 10;
        currentSize = 0;
        arr = new StringPair[capacity];
    }

    ~StringPairVector()
    {
        if (arr)
            delete[] arr;
    }

    void push_back(StringPair data)
    {
        if (currentSize == capacity)
        {
            int newCapacity = capacity * 2;
            StringPair *temp = new StringPair[newCapacity];
            for (int i = 0; i < currentSize; i++)
                temp[i] = arr[i];
            delete[] arr;
            arr = temp;
            capacity = newCapacity;
        }
        arr[currentSize++] = data;
    }

    StringPair &operator[](int index) { return arr[index]; }
    int size() const { return currentSize; }
};

// --- Custom Linked List Node (Unchanged) ---
struct Edge
{
    int destination;
    int weight;
    int congestion;
    int id;
    bool isBlocked;
};

struct ListNode
{
    Edge data;
    ListNode *next;
    ListNode(Edge val) : data(val), next(NULL) {}
};

// --- Custom Linked List (Unchanged) ---
class MyLinkedList
{
public:
    ListNode *head;

    MyLinkedList() : head(NULL) {}

    ~MyLinkedList()
    {
        clear();
    }

    void clear()
    {
        ListNode *current = head;
        while (current)
        {
            ListNode *next = current->next;
            delete current;
            current = next;
        }
        head = NULL;
    }

    void push_back(Edge val)
    {
        ListNode *newNode = new ListNode(val);
        if (!head)
        {
            head = newNode;
            return;
        }
        ListNode *temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
};

// --- Custom Min-Heap (Specific to IntPair) ---
class MyMinHeap
{
private:
    IntPairVector heap;

    void bubbleUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[index].first < heap[parent].first)
            {
                IntPair temp = heap[index];
                heap[index] = heap[parent];
                heap[parent] = temp;
                index = parent;
            }
            else
                break;
        }
    }

    void bubbleDown(int index)
    {
        int size = heap.size();
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && heap[left].first < heap[smallest].first)
                smallest = left;
            if (right < size && heap[right].first < heap[smallest].first)
                smallest = right;

            if (smallest != index)
            {
                IntPair temp = heap[index];
                heap[index] = heap[smallest];
                heap[smallest] = temp;
                index = smallest;
            }
            else
                break;
        }
    }

public:
    bool empty() { return heap.empty(); }
    void push(IntPair val)
    {
        heap.push_back(val);
        bubbleUp(heap.size() - 1);
    }
    IntPair top() { return heap[0]; }
    void pop()
    {
        if (heap.empty())
            return;
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        if (!heap.empty())
            bubbleDown(0);
    }
};

struct HashNode
{
    int key;
    int value;
    HashNode *next;
    HashNode(int k, int v) : key(k), value(v), next(NULL) {}
};

class MyHashMap
{
private:
    HashNode **table;
    int capacity;

public:
    MyHashMap()
    {
        capacity = 100;
        table = new HashNode *[capacity];
        for (int i = 0; i < capacity; i++)
            table[i] = NULL;
    }

    ~MyHashMap()
    {
        clear();
        delete[] table;
    }

    void clear()
    {
        for (int i = 0; i < capacity; i++)
        {
            HashNode *entry = table[i];
            while (entry)
            {
                HashNode *prev = entry;
                entry = entry->next;
                delete prev;
            }
            table[i] = NULL;
        }
    }

    void insert(int key, int value)
    {
        int hashIndex = key % capacity;
        HashNode *entry = table[hashIndex];

        while (entry)
        {
            if (entry->key == key)
            {
                entry->value = value;
                return;
            }
            entry = entry->next;
        }

        HashNode *newNode = new HashNode(key, value);
        newNode->next = table[hashIndex];
        table[hashIndex] = newNode;
    }

    void displayAll()
    {
        bool isEmpty = true;
        for (int i = 0; i < capacity; i++)
        {
            HashNode *entry = table[i];
            while (entry)
            {
                isEmpty = false;
                string status = (entry->value > 10) ? "HEAVY TRAFFIC" : ((entry->value > 0) ? "MODERATE" : "CLEAR");
                cout << "Road ID: " << entry->key
                     << " | Delay: " << entry->value
                     << " mins | Status: " << status << endl;
                entry = entry->next;
            }
        }
        if (isEmpty)
            cout << "No congestion data available.\n";
    }
};

// ==================Main Code==================

class UserManager
{
private:
    // Uses specific StringPairVector instead of template
    StringPairVector users;

public:
    UserManager()
    {
        // Create default admin account
        users.push_back(StringPair("admin", "admin123"));
    }

    void registerUser()
    {
        string username, password;
        cout << "Enter new username: ";
        cin >> username;
        cout << "Enter new password: ";
        cin >> password;

        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].first == username)
            {
                cout << "Error: User already exists!\n";
                return;
            }
        }

        users.push_back(StringPair(username, password));
        cout << "User registered successfully! (Session Only)\n";
    }

    bool login()
    {
        string username, password;
        cout << "\n=== SYSTEM LOGIN ===\n";
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].first == username && users[i].second == password)
            {
                cout << "Login Successful! Welcome, " << username << ".\n";
                return true;
            }
        }

        cout << "Invalid Username or Password.\n";
        return false;
    }
};

// ==========================================
// 3. CORE TRAFFIC CLASSES
// ==========================================

struct PathResult
{
    IntVector path; // Uses specific IntVector
    int totalCost;
    bool found;
};

class CityGraph
{
private:
    int V;
    MyLinkedList *adj;
    MyHashMap congestionMap;

public:
    CityGraph(int vertices) : V(vertices)
    {
        adj = new MyLinkedList[V];
    }

    ~CityGraph()
    {
        delete[] adj;
    }

    void addRoad(int u, int v, int distance, int roadId, int congestionVal = 0, bool blocked = false)
    {
        Edge edge = {v, distance, congestionVal, roadId, blocked};
        adj[u].push_back(edge);
        congestionMap.insert(roadId, congestionVal);
    }

    bool addNewRoute(int u, int v, int distance, int roadId)
    {
        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            cout << "❌ Invalid intersection numbers!\n";
            return false;
        }

        if (distance <= 0)
        {
            cout << "❌ Distance must be positive!\n";
            return false;
        }

        if (roadId <= 0)
        {
            cout << "❌ Road ID must be positive!\n";
            return false;
        }

        ListNode *curr = adj[u].head;
        while (curr)
        {
            if (curr->data.id == roadId)
            {
                cout << "❌ Road ID " << roadId << " already exists!\n";
                return false;
            }
            curr = curr->next;
        }

        addRoad(u, v, distance, roadId);
        cout << "✓ Route added successfully!\n";
        cout << "  From Intersection " << u << " → " << v << "\n";
        cout << "  Road ID: " << roadId << " | Distance: " << distance << " units\n";
        return true;
    }

    void updateCongestion(int roadId, int addedDelay)
    {
        bool found = false;
        for (int i = 0; i < V; ++i)
        {
            ListNode *curr = adj[i].head;
            while (curr)
            {
                if (curr->data.id == roadId)
                {
                    curr->data.congestion = addedDelay;
                    congestionMap.insert(roadId, addedDelay);
                    cout << ">> Road " << roadId << " updated. New Delay: " << addedDelay << endl;
                    found = true;
                }
                curr = curr->next;
            }
        }
        if (!found)
            cout << "!! Road ID not found." << endl;
    }

    void blockRoad(int roadId, bool blockStatus)
    {
        for (int i = 0; i < V; ++i)
        {
            ListNode *curr = adj[i].head;
            while (curr)
            {
                if (curr->data.id == roadId)
                {
                    curr->data.isBlocked = blockStatus;
                    cout << ">> Road " << roadId << (blockStatus ? " is now BLOCKED." : " is now OPEN.") << endl;
                    return;
                }
                curr = curr->next;
            }
        }
    }

    // --- MOVED HERE: Logic for searchDirectRoute ---
    void searchDirectRoute(int u, int v)
    {
        ListNode *curr = adj[u].head;
        int found = 0;

        while (curr)
        {
            if (curr->data.destination == v)
            {
                found++;
                cout << "✓ Direct Route Found!\n";
                cout << "  From: Intersection " << u << "\n";
                cout << "  To: Intersection " << v << "\n";
                cout << "  Road ID: " << curr->data.id << "\n";
                cout << "  Distance: " << curr->data.weight << " units\n";
                cout << "  Base Delay: " << curr->data.congestion << " minutes\n";
                cout << "  Status: " << (curr->data.isBlocked ? "BLOCKED ❌" : "OPEN ✅") << "\n";
                cout << "\n";
            }
            curr = curr->next;
        }

        if (found == 0)
        {
            cout << "✗ No direct route found from Intersection " << u
                 << " to Intersection " << v << ".\n";
            cout << "Try using 'Find Route (Dijkstra)' to find an alternative path.\n";
        }
    }

    PathResult findRoute(int start, int end)
    {
        MyMinHeap pq;
        IntVector dist(V, INF_COST);
        IntVector parent(V, -1);

        dist[start] = 0;
        pq.push(IntPair(0, start));

        while (!pq.empty())
        {
            IntPair top = pq.top();
            pq.pop();

            int u = top.second;
            int currentDist = top.first;

            if (currentDist > dist[u])
                continue;
            if (u == end)
                break;

            ListNode *curr = adj[u].head;
            while (curr)
            {
                Edge &e = curr->data;

                if (!e.isBlocked)
                {
                    int weight = e.weight + e.congestion;

                    if (dist[u] != INF_COST && dist[u] + weight < dist[e.destination])
                    {
                        dist[e.destination] = dist[u] + weight;
                        parent[e.destination] = u;
                        pq.push(IntPair(dist[e.destination], e.destination));
                    }
                }
                curr = curr->next;
            }
        }

        PathResult result;
        if (dist[end] == INF_COST)
        {
            result.found = false;
            result.totalCost = -1;
        }
        else
        {
            result.found = true;
            result.totalCost = dist[end];
            int crawl = end;
            result.path.push_back(crawl);
            while (parent[crawl] != -1)
            {
                result.path.push_back(parent[crawl]);
                crawl = parent[crawl];
            }
            result.path.reverse();
        }
        return result;
    }

    void displayNetwork()
    {
        cout << "\n╔════════════════════════════════════════════════════════════════╗\n";
        cout << "║          CITY ROAD NETWORK VISUALIZATION                       ║\n";
        cout << "╚════════════════════════════════════════════════════════════════╝\n\n";

        // Dynamic ASCII visualization: list each intersection and its outgoing routes
        for (int i = 0; i < V; ++i)
        {
            cout << "┌─ Intersection " << i << " ─────────────────────────────────────────────┐\n";
            ListNode *curr = adj[i].head;
            if (!curr)
            {
                cout << "│  (no outgoing routes)\n";
            }
            else
            {
                while (curr)
                {
                    cout << "│  → To: " << curr->data.destination
                         << "  | ID: " << curr->data.id
                         << "  | Dist: " << curr->data.weight << "   | Delay: " << curr->data.congestion << " mins"
                         << "  | Status: " << (curr->data.isBlocked ? "BLOCKED" : "OPEN")
                         << "\n";
                    curr = curr->next;
                }
            }
            cout << "└────────────────────────────────────────────────────────────────┘\n\n";
        }

        // Detailed Table View (dynamic)
        cout << "╔═══════════════════════════════════════════════════════════════╗\n";
        cout << "║                    DETAILED ROAD INFORMATION                 ║\n";
        cout << "╠═════╦═════╦════╦══════╦═══════╦════════════╦════════════════╣\n";
        cout << "║Start║ End ║ ID ║Dist. ║Delay  ║   Status   ║   Congestion   ║\n";
        cout << "╠═════╬═════╬════╬══════╬═══════╬════════════╬════════════════╣\n";

        int totalRoads = 0;
        int blockedRoads = 0;
        int totalDelay = 0;

        for (int i = 0; i < V; ++i)
        {
            ListNode *curr = adj[i].head;
            while (curr)
            {
                ++totalRoads;
                if (curr->data.isBlocked)
                    ++blockedRoads;
                totalDelay += curr->data.congestion;

                // Basic fixed-width columns (best-effort)
                cout << "║  " << i << "  ║  " << curr->data.destination << "  ║ "
                     << curr->data.id << " ║ "
                     << (curr->data.weight < 10 ? " " : "") << curr->data.weight << "  ║ "
                     << (curr->data.congestion < 10 ? " " : "") << curr->data.congestion << "  ║ ";

                if (curr->data.isBlocked)
                {
                    cout << "  BLOCKED   ║";
                }
                else if (curr->data.congestion > 20)
                {
                    cout << " 🔴 HEAVY  ║";
                }
                else if (curr->data.congestion > 10)
                {
                    cout << " 🟡 MODERATE║";
                }
                else
                {
                    cout << " 🟢 CLEAR   ║";
                }

                // Congestion bar (visual)
                cout << " ";
                int barLength = curr->data.congestion / 5;
                for (int j = 0; j < barLength && j < 12; j++)
                    cout << "█";
                for (int j = barLength; j < 12; j++)
                    cout << "░";
                cout << " ║\n";

                curr = curr->next;
            }
        }

        if (totalRoads == 0)
        {
            cout << "║               No roads in the network yet.                  ║\n";
        }

        cout << "╚═════╩═════╩════╩══════╩═══════╩════════════╩════════════════╝\n";

        // Summary Statistics
        cout << "\n╔════════════════════════════════════════╗\n";
        cout << "║        NETWORK STATISTICS              ║\n";
        cout << "╠════════════════════════════════════════╣\n";
        cout << "║ Total Intersections: " << V << "               ║\n";
        cout << "║ Total Roads: " << totalRoads << "                        ║\n";
        cout << "║ Blocked Roads: " << blockedRoads << "                       ║\n";
        cout << "║ Average Delay: " << (totalRoads > 0 ? (totalDelay / totalRoads) : 0)
             << " minutes               ║\n";
        cout << "║ Network Status: " << (blockedRoads > 0 ? "⚠ PARTIAL OUTAGE" : "✓ OPERATIONAL")
             << "    ║\n";
        cout << "╚════════════════════════════════════════╝\n";
    }

    void displayCongestionStats()
    {
        cout << "\n--- Real-Time Congestion Monitor (Hash Table) ---\n";
        congestionMap.displayAll();
    }
};

// ==========================================
// 4. SYSTEM CONTROLLER
// ==========================================

class TrafficSystem
{
    CityGraph *city;
    UserManager userMgr;
    int intersectionCount;

public:
    TrafficSystem(int n) : intersectionCount(n)
    {
        city = new CityGraph(n);
    }

    ~TrafficSystem()
    {
        delete city;
    }

    void initializeSystem()
    {
        cout << "Initializing Default Road Network...\n";
        city->addRoad(0, 1, 10, 101);
        city->addRoad(0, 2, 15, 102);
        city->addRoad(1, 2, 10, 103);
        city->addRoad(1, 3, 12, 104);
        city->addRoad(2, 4, 10, 105);
        city->addRoad(3, 4, 2, 106);
        city->addRoad(3, 5, 1, 107);
        city->addRoad(4, 5, 5, 108);

        city->addRoad(1, 0, 10, 201);
        city->addRoad(2, 0, 15, 202);
        city->addRoad(2, 1, 10, 203);
        city->addRoad(3, 1, 12, 204);
        city->addRoad(4, 2, 10, 205);
        city->addRoad(4, 3, 2, 206);
        city->addRoad(5, 3, 1, 207);
        city->addRoad(5, 4, 5, 208);
    }

    void showNetwork() { city->displayNetwork(); }

    void monitorStats()
    {
        city->displayCongestionStats();
    }

    // Renamed visualizeRoute() -> findRoute()
    void findRoute()
    {

        int src, dest;
        cout << "\n--- Find Route ---\n";
        cout << "Enter Source Intersection (0-" << intersectionCount - 1 << "): ";

        while (!(cin >> src) || src < 0 || src >= intersectionCount)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ Invalid input! Please enter a number between 0 and " << intersectionCount - 1 << ": ";
        }

        cout << "Enter Destination Intersection (0-" << intersectionCount - 1 << "): ";
        while (!(cin >> dest) || dest < 0 || dest >= intersectionCount)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ Invalid input! Please enter a number between 0 and " << intersectionCount - 1 << ": ";
        }

        // REMOVED emergency selection UI and logic
        PathResult res = city->findRoute(src, dest);

        if (res.found)
        {
            cout << "\n╔════════════════════════════════════════╗\n";
            cout << "║       OPTIMAL ROUTE VISUALIZATION      ║\n";
            cout << "╚════════════════════════════════════════╝\n";
            cout << "Total Time: " << res.totalCost << " minutes\n\n";

            for (int i = 0; i < res.path.size(); ++i)
            {
                cout << "  ╔═══════════════════╗\n";
                cout << "  ║  Intersection " << res.path[i] << "   ║\n";
                cout << "  ╚═══════════════════╝\n";
                if (i < res.path.size() - 1)
                {
                    cout << "        ║\n";
                    cout << "        ▼\n";
                }
            }

            cout << "\n✓ Route successfully calculated!\n";
        }
        else
        {
            cout << "\n✗ No route exists between Intersection " << src << " and " << dest << ".\n";
        }
    }

    void simulateCongestion()
    {
        int roadId, delay;
        cout << "\n--- Dynamic Traffic Simulation ---\n";
        cout << "Enter Road ID (e.g., 101-108 for forward, 201-208 for reverse): ";

        while (!(cin >> roadId) || roadId <= 0)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ Invalid input! Please enter a positive road ID: ";
        }

        cout << "Enter Traffic Delay in minutes (0-60): ";
        while (!(cin >> delay) || delay < 0 || delay > 60)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ Invalid input! Please enter a number between 0 and 60: ";
        }

        city->updateCongestion(roadId, delay);
    }

    void manageBlockages()
    {
        int roadId, op;
        cout << "\n--- Road Maintenance ---\n";
        cout << "Enter Road ID (e.g., 101-108 for forward, 201-208 for reverse): ";

        while (!(cin >> roadId) || roadId <= 0)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ Invalid input! Please enter a positive road ID: ";
        }

        cout << "Select Operation:\n  1. Block Road\n  2. Open Road\nEnter Choice (1 or 2): ";
        while (!(cin >> op) || (op != 1 && op != 2))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ Invalid input! Please enter 1 or 2: ";
        }

        city->blockRoad(roadId, (op == 1));
    }

    bool authenticate()
    {
        bool check = false;
        while (check == false)
        {
            int c;
            cout << "\n1. Login\n2. Register New Admin (Session)\nEnter Choice (1 or 2): ";
            cin >> c;
            if (c == 1)
            {
                check = userMgr.login();
            }
            else if (c == 2)
                userMgr.registerUser();
            else
                cout << "❌ Invalid input! Please enter 1 or 2: ";
        }

        return check;
    }

    void addNewRoute()
    {
        int u, v, distance, roadId;

        cout << "\n╔════════════════════════════════════════╗\n";
        cout << "║         ADD NEW ROUTE TO NETWORK       ║\n";
        cout << "╚════════════════════════════════════════╝\n\n";

        cout << "Available Intersections: 0-" << intersectionCount - 1 << "\n\n";

        // Input: Source Intersection
        cout << "Enter Source Intersection (0-" << intersectionCount - 1 << "): ";
        while (!(cin >> u) || u < 0 || u >= intersectionCount)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ Invalid! Enter a number between 0 and " << intersectionCount - 1 << ": ";
        }

        // Input: Destination Intersection
        cout << "Enter Destination Intersection (0-" << intersectionCount - 1 << "): ";
        while (!(cin >> v) || v < 0 || v >= intersectionCount)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ Invalid! Enter a number between 0 and " << intersectionCount - 1 << ": ";
        }

        // Check if same intersection
        if (u == v)
        {
            cout << "❌ Source and destination cannot be the same!\n";
            return;
        }

        // Input: Distance
        cout << "Enter Distance (in units, 1-100): ";
        while (!(cin >> distance) || distance <= 0 || distance > 100)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ Invalid! Enter a number between 1 and 100: ";
        }

        // Input: Road ID
        cout << "Enter Road ID (positive integer, e.g., 101-999): ";
        while (!(cin >> roadId) || roadId <= 0)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ Invalid! Enter a positive integer: ";
        }

        // Add the route
        bool success = city->addNewRoute(u, v, distance, roadId);

        if (success)
        {
            cout << "\n--- Would you like to add the reverse route? ---\n";
            cout << "1. Yes (Add reverse route)\n";
            cout << "2. No (Skip)\n";
            cout << "Enter Choice (1 or 2): ";

            int choice;
            while (!(cin >> choice) || (choice != 1 && choice != 2))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "❌ Invalid! Please enter 1 or 2: ";
            }

            if (choice == 1)
            {
                int reverseRoadId = roadId + 100; // Create unique reverse ID
                if (city->addNewRoute(v, u, distance, reverseRoadId))
                {
                    cout << "✓ Reverse route also added!\n";
                }
            }
        }
    }

    void viewAllRoutes()
    {
        cout << "\n╔════════════════════════════════════════╗\n";
        cout << "║        ALL AVAILABLE ROUTES            ║\n";
        cout << "╚════════════════════════════════════════╝\n\n";
        city->displayNetwork();
    }

    void searchRoute()
    {
        int u, v;
        cout << "\n--- Search Direct Route ---\n";
        cout << "Enter Source Intersection (0-" << intersectionCount - 1 << "): ";

        while (!(cin >> u) || u < 0 || u >= intersectionCount)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ Invalid input! Please enter a number between 0 and " << intersectionCount - 1 << ": ";
        }

        cout << "Enter Destination Intersection (0-" << intersectionCount - 1 << "): ";
        while (!(cin >> v) || v < 0 || v >= intersectionCount)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ Invalid input! Please enter a number between 0 and " << intersectionCount - 1 << ": ";
        }

        // FIXED: Call the method on the city object
        city->searchDirectRoute(u, v);
    }
};

// ==========================================
// 5. MAIN FUNCTION
// ==========================================

int main()
{
    TrafficSystem ts(6);
    ts.initializeSystem();

    // Admin Login (Loop until successful)
    while (!ts.authenticate())
    {
        cout << "Access Denied. Please try again.\n";
    }

    cout << "Access Granted. Welcome to the Smart Traffic System.\n";

    int choice;
    do
    {
        cout << "\n╔════════════════════════════════════════════════════════════╗\n";
        cout << "║        SMART TRAFFIC SYSTEM (Admin Control Panel)          ║\n";
        cout << "╚════════════════════════════════════════════════════════════╝\n";
        cout << "\n📍 ROUTE MANAGEMENT:\n";
        cout << "   1. View All Routes (Network)\n";
        cout << "   2. Add New Route\n";
        cout << "   3. Search Direct Route\n";
        cout << "\n🚗 VEHICLE ROUTING:\n";
        cout << "   4. Find Route\n";
        cout << "\n🚦 TRAFFIC CONTROL:\n";
        cout << "   5. Add Traffic (Congestion)\n";
        cout << "   6. Monitor Congestion (Hash Map)\n";
        cout << "   7. Block/Open Road\n";
        cout << "\n   0. Exit\n";
        cout << "════════════════════════════════════════════════════════════\n";
        cout << "Enter Choice (0-7): ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            ts.viewAllRoutes();
            break;
        case 2:
            ts.addNewRoute();
            break;
        case 3:
            ts.searchRoute();
            break;
        case 4:
            ts.findRoute();
            break;
        case 5:
            ts.simulateCongestion();
            break;
        case 6:
            ts.monitorStats();
            break;
        case 7:
            ts.manageBlockages();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "❌ Invalid input! Please enter a number between 0 and 7: ";
        }
    } while (choice != 0);

    return 0;
}