#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct CustomerNode {
    char first_name[21];
    char last_name[21];
    int age;
    struct CustomerNode* next;
};

struct CustomerList {
    struct CustomerNode* head;
    struct CustomerNode* tail;
    uint16_t size;
};

// Let's use some state machiens for fun and profit. Doesn't make sense here, but
// it's a good exercise.
typedef enum {
  STARTUP,
  READY,
  READ,
  WRITE,
  LIST_MANIPULATION,
  CLEANUP,
  EXIT
} CustomerState;

typedef enum {
  LIST_READ,
  LIST_WRITE,
  LIST_INSERT,
  LIST_DELETE,
} ListManipulationState;

typedef enum {
  READ_FIRST_NAME,
  READ_LAST_NAME,
  READ_AGE,
  WRITE_FIRST_NAME,
  WRITE_LAST_NAME,
  WRITE_AGE,
} ReadWriteState;