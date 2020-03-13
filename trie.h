
struct EnergyNode{
  uint64_t value;
  struct EnergyNode *rep;
  int inCount;
};

struct Node{
  struct Node *pointers[4];
  struct EnergyNode *Energy;
};

struct EnergyNode *createEnergyNode(uint64_t value);
struct Node *createNode();
struct Node **getNode(char *s, struct Node *tree, int len);
void addHistory(char *s, struct Node *tree);
void clearTree(struct Node *tree);
void removeHistory(char *s, struct Node *tree);
struct EnergyNode *findEnergy(struct Node *historyNode);
void unionEnergy(struct Node *historyNode1, struct Node *historyNode2);
uint64_t strToNum(char *s);
