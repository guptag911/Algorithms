class Node() {
    Node* front;
    Node* back;
    int val;
    Node(): front(NULL), back(NULL), val(-1) {};
    Node(int x): front(NULL), back(NULL), val(x) {};
};

class LRUCache() {
    private:
    int maxCapacity;
    int capactiy;
    Node* head;
    Node* tail;
    unordered_map<int, Node*> hash;

    public:
    LRUCache(int c): maxCapacity(c), capactiy(0), head(NULL), tail(NULL) {};

    int get(int key) {
        if (hash.find(key)==hash.end()) {
            return -1;
        }
        Node* temp = hash[key];
        if (temp == head) {
            return temp->val;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        temp->next = head;
        head->prev = temp;
        head = temp;
        head->prev = NULL;
        return temp->val;
    }

    void put(int value) {
        Node* temp = new Node(value);
        if (capactiy < maxCapacity) {
            if (head == NULL) {
                head = tail = temp;
                hash[value] = temp;
            } else {
                tail->next = temp;
                temp->prev = tail;
                tail = tail->next;
            }
            capactiy++;
        } else {
            hash.erase(head->value);
            head = head->next;
            head->prev = NULL;
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
        hash[value] = temp;
    }
};
