#ifndef __VERTEX_STRUCTURE_H__
#define __VERTEX_STRUCTURE_H__

typedef uint64_t* ptr;
typedef uint64_t word_t;


struct vertex_local{
  uint64_t deg;
  uint64_t id;
  ptr neigh;
};

struct vertex_local_schedule{
  uint64_t deg;
  uint64_t id;
  ptr neigh;
  uint64_t schedule_deg;
  ptr schedule_neigh;
};

typedef struct vertex{
  uint64_t deg;
  uint64_t id;
  ptr neigh;
  uint64_t schedule_deg;
  ptr schedule_neigh;
  uint64_t reserved0;
  uint64_t reserved1;
  uint64_t reserved2;
} vertex_t;


#endif