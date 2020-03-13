#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

const char *_declare = "DECLARE";
const char *_remove = "REMOVE";
const char *_valid = "VALID";
const char *_energy = "ENERGY";
const char *_equal = "EQUAL";

struct Info {
  uint32_t code;
  char *str1;
  char *str2;
  char *beg;
};

void writeInfo(struct Info *dest, uint32_t code, char *str1, char *str2, char *beg) {
  dest->code = code;
  dest->str1 = str1;
  dest->str2 = str2;
  dest->beg = beg;
}

char *readLine() {
  uint32_t buffer_size = 10;
  uint32_t counter = 0;

  char *str = (char*)malloc(buffer_size);
  if(str == NULL) exit(1);
  char *ptr = str;

  bool isBad = 0;
  bool isFirst = 1;
  bool ignore = 0;

  while (1) {
    if (counter == buffer_size - 1) {
      buffer_size *= 2;
      str = (char*)realloc(str, buffer_size);
      if(str == NULL) exit(1);
      ptr = str + counter;
    }

    *ptr = fgetc(stdin);

    if (feof(stdin)) {
      break;
    }

    if (isFirst) {
      if (*ptr == '#') ignore = 1;
      isFirst = 0;
    }

    if (*ptr == 10) break;
    bool is_number = *ptr >= 48 && *ptr <= 57;
    bool is_char = *ptr >= 65 && *ptr <= 90;
    if (*ptr != 32 && !is_number && !is_char) isBad = 1;

    counter++;
    ptr++;
  }

  if (isBad && !ignore) {
    free(str);
    return NULL;
  }

  *ptr = 0;
  return str;
}

/*
Zwraca podslowo do najblizszej spacji/konca stringa.
Zapisuje iformacje o stringu we wskazanych zmiennych.
*/
char *extract(char *s, uint32_t *curr_dist, bool *isNumber, bool *alphCheck) {
  char *ptr = s;
  *curr_dist = 0;
  *isNumber = 1;
  *alphCheck = 1;

  while (1) {
    if (*ptr == 0 || *ptr == 32) break;
    if (*ptr != 48 && *ptr != 49 && *ptr != 50 && *ptr != 51) *alphCheck = 0;
    if (*ptr < 48 || *ptr > 57) *isNumber = 0;
    (*curr_dist)++;
    ptr++;
  }

  *ptr = 0;
  return s;
}

void whatToDo(char *s, struct Info *dest) {
  if (s == NULL) { writeInfo(dest, 0, NULL, NULL, s); return;}
  if (*s == '#' || *s == 0) { writeInfo(dest, -1, NULL, NULL, s); return;}

  uint32_t len = strlen(s);

  uint32_t curr_dist_value = 0;
  uint32_t *curr_dist = &curr_dist_value;

  bool isNumber_value = 0;
  bool *isNumber = &isNumber_value;

  bool alphCheck_value = 0;
  bool *alphCheck = &alphCheck_value;

  char *first_substr = extract(s, curr_dist, isNumber, alphCheck);
  uint32_t firstSpace = *curr_dist;

  if (firstSpace == len || firstSpace == 0) {
    writeInfo(dest, 0, NULL, NULL, s);
    return;
  }

  bool cp_declare = !strcmp(first_substr, _declare);
  bool cp_remove = !strcmp(first_substr, _remove);
  bool cp_valid = !strcmp(first_substr, _valid);
  bool cp_energy = !strcmp(first_substr, _energy);
  bool cp_equal = !strcmp(first_substr, _equal);

  if (!(cp_declare || cp_remove || cp_valid || cp_energy || cp_equal)) {
    writeInfo(dest, 0, NULL, NULL, s);
    return;
  }

  char *sec_substr = extract(s + firstSpace + 1, curr_dist, isNumber, alphCheck);
  uint32_t secSpace = firstSpace + 1 + *curr_dist;
  bool sec_alphCheck = *alphCheck;

  if (secSpace == firstSpace + 1) {
    writeInfo(dest, 0, NULL, NULL, s);
    return;
  }

  if (secSpace == len) {
    if (!(*alphCheck)) { writeInfo(dest, 0, NULL, NULL, s); return;}

    if (cp_declare) {
      writeInfo(dest, 1, sec_substr, NULL, s);
      return;
    }

    if (cp_remove) {
      writeInfo(dest, 2, sec_substr, NULL, s);
      return;
    }

    if (cp_valid) {
      writeInfo(dest, 3, sec_substr, NULL, s);
      return;
    }

    if (cp_energy) {
      writeInfo(dest, 4, sec_substr, NULL, s);
      return;
    }
  }

  char *third_substr = extract(s + secSpace + 1, curr_dist, isNumber, alphCheck);
  uint32_t end_location = secSpace + 1 + *curr_dist;

  if (end_location == secSpace + 1) {
    writeInfo(dest, 0, NULL, NULL, s);
    return;
  }

  if (end_location != len) { writeInfo(dest, 0, NULL, NULL, s); return;}

  if (cp_energy) {
    if (!sec_alphCheck) { writeInfo(dest, 0, NULL, NULL, s); return;}
    if (!(*isNumber)) { writeInfo(dest, 0, NULL, NULL, s); return;}

    writeInfo(dest, 4, sec_substr, third_substr, s);
    return;
  }

  if (cp_equal) {
    if (!sec_alphCheck) { writeInfo(dest, 0, NULL, NULL, s); return;}
    if (!(*alphCheck)) { writeInfo(dest, 0, NULL, NULL, s); return;}

    writeInfo(dest, 5, sec_substr, third_substr, s);
    return;
  }
  writeInfo(dest, 0, NULL, NULL, s);
}
