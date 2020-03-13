#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "trie.h"
#include "parser.h"

void callError(struct Info *info) {
  free(info->beg);
  info->beg = NULL;
  fprintf(stderr, "%s\n", "ERROR");
}

int32_t main() {

  struct Info *info = (struct Info*)malloc(sizeof(struct Info));
  writeInfo(info, 0, NULL, NULL, NULL);

  struct Node *trieTree = createNode();

  while(1) {
    whatToDo(readLine(), info);

    if (feof(stdin)){
      if (info->code != -1) {
        fprintf(stderr, "%s\n", "ERROR");
      }

      free(info->beg);
      info->beg = NULL;
      break;
    }

    if (info->code == -1) {
      free(info->beg);
      info->beg = NULL;
      continue;
    }

    if (info->code == 0) {
      callError(info);
      continue;
    }

    if (info->code == 1) { //DECLARE
      addHistory(info->str1, trieTree);
      printf("%s\n", "OK");
    }

    if (info->code == 2) { //REMOVE
      removeHistory(info->str1, trieTree);
      printf("%s\n", "OK");
    }

    if (info->code == 3) { //VALID
      struct Node **hisNode = getNode(info->str1, trieTree, strlen(info->str1));
      if (hisNode == NULL) printf("%s\n", "NO");
      else printf("%s\n", "YES");
    }

    if (info->code == 4) { //ENERGY
      struct Node **hisNode = getNode(info->str1, trieTree, strlen(info->str1));

      if (hisNode == NULL) {
        callError(info);
        continue;
      }

      if (info->str2 == NULL) {
        struct EnergyNode *energy = findEnergy(*hisNode);

        if (energy == NULL) {
          callError(info);
          continue;
        }

        printf("%"PRIu64"\n", energy->value);
      }
      else {
        struct EnergyNode *rep = findEnergy(*hisNode);
        uint64_t energyValue = strToNum(info->str2);

        if (energyValue == 0) {
          callError(info);
          continue;
        }

        if (rep == NULL) {
          struct EnergyNode *newEnergy = createEnergyNode(energyValue);
          (*hisNode)->Energy = newEnergy;

          printf("%s\n", "OK");
        }
        else {
          rep->value = energyValue;
          printf("%s\n", "OK");
        }
      }
    }

    if (info->code == 5) { //EQUAL
      struct Node **hisNode1 = getNode(info->str1, trieTree, strlen(info->str1));
      struct Node **hisNode2 = getNode(info->str2, trieTree, strlen(info->str2));

      if (hisNode1 == NULL || hisNode2 == NULL) {
        callError(info);
        continue;
      }

      if (*hisNode1 == *hisNode2) {
        free(info->beg);
        info->beg = NULL;
        printf("%s\n", "OK");
        continue;
      }

      if ((*hisNode1)->Energy == NULL && (*hisNode2)->Energy == NULL) {
        callError(info);
        continue;
      }

      unionEnergy(*hisNode1, *hisNode2);
      printf("%s\n", "OK");
    }

    free(info->beg);
    info->beg = NULL;
  }

  free(info);

  clearTree(trieTree);
  trieTree = NULL;

  return 0;
}
