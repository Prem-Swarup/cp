
struct Node {
    Node* children[2];
    Node() : children{nullptr, nullptr} {}
};

class Trie {
public:
    Trie() : root(new Node()) {}

    void insert(int num) {
        Node* curr = root;
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (!curr->children[bit]) {
                curr->children[bit] = new Node();
            }
            curr = curr->children[bit];
        }
    }
    int mx(int num) {
        Node* curr = root;
        int result = 0;
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;
            int oppositeBit = 1 - bit;
            if (curr->children[oppositeBit]) {
                result |= (1 << i);
                curr = curr->children[oppositeBit];
            } else {
                curr = curr->children[bit];
            }
        }
        return result;
    }

    void erase(int num) {
        eraseHelper(root, num, 31);
    }

    void print() {
        printHelper(root, 0);
    }

private:
    Node* root;

    bool eraseHelper(Node*& node, int num, int bitIndex) {
        if (!node || bitIndex < 0) {
            return true; 
        }

        int bit = (num >> bitIndex) & 1;
        bool shouldEraseChild = eraseHelper(node->children[bit], num, bitIndex - 1);

        if (shouldEraseChild) {
            delete node->children[bit];
            node->children[bit] = nullptr;
        }

        
        return node->children[0] == nullptr && node->children[1] == nullptr;
    }

    void printHelper(Node* node, int level) {
        if (node) {
            
            std::cout << "Level " << level << ": ";
            for (int i = 0; i < 2; ++i) {
                if (node->children[i]) {
                    std::cout << i << " ";
                }
            }
            std::cout << std::endl;

            
            for (int i = 0; i < 2; ++i) {
                printHelper(node->children[i], level + 1);
            }
        }
    }
};
