constexpr char BASE_CH = '0';
constexpr char END_CH = '9';
constexpr int CNUM = END_CH - BASE_CH + 1;

struct Trie
{
    Trie* child[CNUM];
    bool hasStr;
    bool hasChild;

    Trie()
    {
        for(int i = 0; i < CNUM; i++) {
            child[i] = nullptr;
        }
        hasStr = false;
        hasChild = false;
    }

    ~Trie()
    {
        for(int i = 0; i < CNUM; i++) {
            if(child[i] != nullptr) delete child[i];
        }
    }

    void insert(const char* str)
    {
        Trie* current = this;

        while(*str != '\0') {
            int ch = *str - BASE_CH;

            if(current->child[ch] == nullptr) {
                current->child[ch] = new Trie();
                current->hasChild = true;
            }

            current = current->child[ch];
            str++;
        }
        current->hasStr = true;
    }
};
