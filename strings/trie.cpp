#include <iostream>
#include <unordered_map>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    int wordCount;

    TrieNode() : isEndOfWord(false), wordCount(0) {}
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const std::string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
            node->wordCount++;
        }
        node->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return node->isEndOfWord;
    }

    bool startsWith(const std::string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return true;
    }

    int wordCount(const std::string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return 0;
            }
            node = node->children[ch];
        }
        return node->wordCount;
    }

    int getTotalWordCount(const std::string& word) {
        TrieNode* node = root;
        int totalWordCount = 0;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                return totalWordCount;
            }
            node = node->children[ch];
            totalWordCount += node->wordCount;
        }
        return totalWordCount;
    }

    void erase(const std::string& word) {
        eraseHelper(root, word, 0);
    }

private:
    TrieNode* root;

    // Helper function for erase
    bool eraseHelper(TrieNode* node, const std::string& word, int depth) {
        if (depth == word.length()) {
            if (!node->isEndOfWord) {
                return false; // Word not found
            }
            node->isEndOfWord = false;
            return node->children.empty(); // If node has no other children, it can be removed
        }

        char ch = word[depth];
        if (node->children.find(ch) == node->children.end()) {
            return false; // Word not found
        }

        bool shouldRemoveChild = eraseHelper(node->children[ch], word, depth + 1);

        if (shouldRemoveChild) {
            delete node->children[ch];
            node->children.erase(ch);
        }

        return node->children.empty() && !node->isEndOfWord; // If node has no other children and is not the end of a word, it can be removed
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("apricot");
    trie.insert("banana");
    trie.insert("bat");

    std::cout << "Before erasing 'app':" << std::endl;
    std::cout << "Search 'app': " << std::boolalpha << trie.search("app") << std::endl; // true

    trie.erase("app");

    std::cout << "After erasing 'app':" << std::endl;
    std::cout << "Search 'app': " << std::boolalpha << trie.search("app") << std::endl; // false

    return 0;
}
