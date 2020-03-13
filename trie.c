#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

struct EnergyNode {
  uint64_t value;
  struct EnergyNode *rep;
  uint32_t inCount;
};

struct Node {
  struct Node *pointers[4];
  struct EnergyNode *Energy;
};

struct EnergyNode *createEnergyNode(uint64_t value) {
  struct EnergyNode *new = (struct EnergyNode*)malloc(sizeof(struct EnergyNode));
  if (new == NULL) exit(1);

  new->value = value;
  new->rep = new;
  new->inCount = 1;

  return new;
}

struct Node *createNode() {
  struct Node *new = (struct Node*)malloc(sizeof(struct Node));
  if (new == NULL) exit(1);

  for(uint32_t i=0; i<4; i++) new->pointers[i] = NULL;
  new->Energy = NULL;

  return new;
}

// Usuwa krawedz wchodzaca do wiercholka EnergyNode. Jesli liczba wchodzacych
// krawedzi spadnie do zera, wiercholek zostaje usuniety, a w zwiazku z tym
// funkcja wywoluje sie rekurencyjnie dla reprezentanta

void decreaseEnergy(struct EnergyNode *ptr) {
  ptr->inCount--;

  if (ptr->inCount == 0){
    if (ptr->rep != ptr) decreaseEnergy(ptr->rep);

    ptr->rep = NULL;
    ptr->value = 0;

    free(ptr);
  }
}

// Dla podanej historii zwraca wskaznik na wskaznik na odpowiadajacy tej
// historii Node (albo NULL). Podwojny wskaznik jest tu uzyty ze wzgledu na
// funkcje removeHistory. Dzieki temu, ze getNode zwraca mi adres wskaznika
// z nizszego wezla w drzewie, po usunieciu historii latwo jest ustawic go na NULL.

struct Node **getNode(char *s, struct Node *tree, uint32_t len) {
  while(1){
    if (tree->pointers[*s - '0'] == NULL) return NULL;
    if (len == 1) return &(tree->pointers[*s - '0']);

    tree = tree->pointers[*s - '0'];
    s++;
    len--;
  }
}

void addHistory(char *s, struct Node *tree) {
  while (1) {
    if (*s == 0) return;
    if (tree->pointers[*s - '0'] == NULL) break;

    tree = tree->pointers[*s - '0'];
    s++;
  }

  while (1) {
    if (*s == 0) return;

    struct Node *new = createNode();
    tree->pointers[*s - '0'] = new;
    tree = new;
    s++;
  }
}

void clearTree(struct Node *tree) {
  for (uint32_t i=0; i<4; i++) {
    if (tree->pointers[i] != NULL) {
      clearTree(tree->pointers[i]);
      tree->pointers[i] = NULL;
    }
  }

  if (tree->Energy != NULL) {
    decreaseEnergy(tree->Energy);
    tree->Energy = NULL;
  }
  free(tree);
}

void removeHistory(char *s, struct Node *tree) {
  struct Node **historyNodePtr = getNode(s, tree, (uint32_t)strlen(s));

  if (historyNodePtr != NULL) {
    clearTree(*historyNodePtr);
    *historyNodePtr = NULL;
  }
}

// Znajduje reprezentanta podanego EnergyNode, a przy cofaniu sie rekurencji
// przepina do niego wszystkie wiercholki na sciezce.

struct EnergyNode *findRep(struct EnergyNode **ptr) {
  if ((*ptr)->rep == *ptr) return *ptr;

  struct EnergyNode *rep = findRep(&((*ptr)->rep));
  rep->inCount++;
  decreaseEnergy(*ptr);
  *ptr = rep;

  return rep;
}

struct EnergyNode *findEnergy(struct Node *historyNode) {
  if (historyNode->Energy == NULL) return NULL;
  return findRep(&(historyNode->Energy));
}

void unionEnergy(struct Node *historyNode1, struct Node *historyNode2) {
  if (historyNode1 == historyNode2) return;

  if (historyNode1->Energy != NULL) {
    struct EnergyNode *rep1 = findEnergy(historyNode1);

    if (historyNode2->Energy != NULL) {
      struct EnergyNode *rep2 = findEnergy(historyNode2);
      if(rep1 == rep2) return;

      uint64_t fix = (rep1->value & rep2->value & 1);
      uint64_t average = rep1->value / 2 + rep2->value / 2 + fix;

      rep1->rep = rep2;
      rep1->value = 0;
      rep2->value = average;
      rep2->inCount++;
    }
    else {
      historyNode2->Energy = rep1;
      rep1->inCount++;
    }
  }
  else {
    unionEnergy(historyNode2, historyNode1);
  }
}

uint64_t strToNum(char *s) {
  uint64_t result = 0;
  uint64_t multiplier = 1;
  char *end = s + strlen(s) - 1;

  while (1) {
    result += (uint64_t)(*end - '0') * multiplier;
    multiplier *= 10;
    if(end == s) break;
    end--;
  }

  return result;
}
