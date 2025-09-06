#ifndef __INTERSECT_H__
#define __INTERSECT_H__

#include "vertex_structure.hpp"
// #define BOUNDARY_CHECK

word_t intersection(ptr list_a, uint64_t size_a, ptr list_b, uint64_t size_b){
  word_t size = 0;
  word_t pos0 = 0, pos1 = 0;
  word_t a, b;
#ifdef BOUNDARY_CHECK
  if(size_a == 0 || size_b == 0 || list_a[size_a - 1] < list_b[0] || list_a[0] > list_b[size_b - 1])
    return 0;
#endif
  while(pos0 < size_a && pos1 < size_b){
    a = list_a[pos0];
    b = list_b[pos1];
    if(a <= b)
      pos0++;
    if(a >= b)
      pos1++;
    if(a == b)
      size++;
    }
  return size;
}

word_t intersection_store(ptr list_a, uint64_t size_a, ptr list_b, uint64_t size_b, ptr list_r){
  word_t size = 0;
  word_t pos0 = 0, pos1 = 0;
  word_t a, b;
#ifdef BOUNDARY_CHECK
  if(size_a == 0 || size_b == 0 || list_a[size_a - 1] < list_b[0] || list_a[0] > list_b[size_b - 1])
    return 0;
#endif
  while(pos0 < size_a && pos1 < size_b){
    a = list_a[pos0];
    b = list_b[pos1];
    if(a <= b)
      pos0++;
    if(a >= b)
      pos1++;
    if(a == b)
      list_r[size++] = a;
    }
  return size;
}

word_t intersection_constrain(ptr list_a, uint64_t size_a, ptr list_b, uint64_t size_b, uint64_t threshold){
  word_t size = 0;
  word_t pos0 = 0, pos1 = 0;
  word_t a, b;
#ifdef BOUNDARY_CHECK
  if(size_a == 0 || size_b == 0 || list_a[size_a - 1] < list_b[0] || list_a[0] > list_b[size_b - 1])
    return 0;
#endif
  while(pos0 < size_a && pos1 < size_b)
  {
    a = list_a[pos0];
    b = list_b[pos1];
    if(a >= threshold)
      break;
    if(b >= threshold)
      break;
    if(a <= b)
      pos0++;
    if(a >= b)
      pos1++;
    if(a == b)
      size++;
  }
  return size;
}

word_t intersection_store_constrain(ptr list_a, uint64_t size_a, ptr list_b, uint64_t size_b, ptr list_r, uint64_t threshold){
  word_t size = 0;
  word_t pos0 = 0, pos1 = 0;
  word_t a, b;
#ifdef BOUNDARY_CHECK
  if(size_a == 0 || size_b == 0 || list_a[size_a - 1] < list_b[0] || list_a[0] > list_b[size_b - 1])
    return 0;
#endif
  while(pos0 < size_a && pos1 < size_b){
    a = list_a[pos0];
    b = list_b[pos1];
    if(a >= threshold)
      break;
    if(b >= threshold)
      break;
    if(a <= b)
      pos0++;
    if(a >= b)
      pos1++;
    if(a == b)
      list_r[size++] = a;
    }
  return size;
}

word_t intersection_v(vertex_t* g_v_bin, uint64_t va, uint64_t vb){
  ptr list_a = g_v_bin[va].neigh;
  uint64_t size_a = g_v_bin[va].deg;
  ptr list_b = g_v_bin[vb].neigh;
  uint64_t size_b = g_v_bin[vb].deg;

  word_t size = 0;
  word_t pos0 = 0, pos1 = 0;
  word_t a, b;
#ifdef BOUNDARY_CHECK
  if(size_a == 0 || size_b == 0 || list_a[size_a - 1] < list_b[0] || list_a[0] > list_b[size_b - 1])
    return 0;
#endif
  while(pos0 < size_a && pos1 < size_b){
    a = list_a[pos0];
    b = list_b[pos1];
    if(a <= b)
      pos0++;
    if(a >= b)
      pos1++;
    if(a == b)
      size++;
    }
  return size;
}


word_t intersection_store_v(vertex_t* g_v_bin, uint64_t va, uint64_t vb, ptr list_r){
  ptr list_a = g_v_bin[va].neigh;
  uint64_t size_a = g_v_bin[va].deg;
  ptr list_b = g_v_bin[vb].neigh;
  uint64_t size_b = g_v_bin[vb].deg;

  word_t size = 0;
  word_t pos0 = 0, pos1 = 0;
  word_t a, b;
#ifdef BOUNDARY_CHECK
  if(size_a == 0 || size_b == 0 || list_a[size_a - 1] < list_b[0] || list_a[0] > list_b[size_b - 1])
    return 0;
#endif
  while(pos0 < size_a && pos1 < size_b){
    a = list_a[pos0];
    b = list_b[pos1];
    if(a <= b)
      pos0++;
    if(a >= b)
      pos1++;
    if(a == b)
      list_r[size++] = a;
    }
  return size;
}

word_t intersection_constrain_v(vertex_t* g_v_bin, uint64_t va, uint64_t vb, uint64_t threshold){
  ptr list_a = g_v_bin[va].neigh;
  uint64_t size_a = g_v_bin[va].deg;
  ptr list_b = g_v_bin[vb].neigh;
  uint64_t size_b = g_v_bin[vb].deg;

  word_t size = 0;
  word_t pos0 = 0, pos1 = 0;
  word_t a, b;
#ifdef BOUNDARY_CHECK
  if(size_a == 0 || size_b == 0 || list_a[size_a - 1] < list_b[0] || list_a[0] > list_b[size_b - 1])
    return 0;
#endif
  while(pos0 < size_a && pos1 < size_b)
  {
    a = list_a[pos0];
    b = list_b[pos1];
    if(a >= threshold)
      break;
    if(b >= threshold)
      break;
    if(a <= b)
      pos0++;
    if(a >= b)
      pos1++;
    if(a == b)
      size++;
  }
  return size;
}

word_t intersection_constrain_v(vertex_t* g_v_bin, uint64_t va, uint64_t vb, uint64_t threshold, double &n_edges){
  ptr list_a = g_v_bin[va].neigh;
  uint64_t size_a = g_v_bin[va].deg;
  ptr list_b = g_v_bin[vb].neigh;
  uint64_t size_b = g_v_bin[vb].deg;

  word_t size = 0;
  word_t pos0 = 0, pos1 = 0;
  word_t a, b;
#ifdef BOUNDARY_CHECK
  if(size_a == 0 || size_b == 0 || list_a[size_a - 1] < list_b[0] || list_a[0] > list_b[size_b - 1])
    return 0;
#endif
  while(pos0 < size_a && pos1 < size_b)
  {
    a = list_a[pos0];
    b = list_b[pos1];
    if(a >= threshold)
      break;
    if(b >= threshold)
      break;
    if(a <= b)
      pos0++;
    if(a >= b)
      pos1++;
    if(a == b)
      size++;
  }
  n_edges = n_edges + pos0 + pos1;
  return size;
}

word_t intersection_store_constrain_v(vertex_t* g_v_bin, uint64_t va, uint64_t vb, ptr list_r, uint64_t threshold){
  ptr list_a = g_v_bin[va].neigh;
  uint64_t size_a = g_v_bin[va].deg;
  ptr list_b = g_v_bin[vb].neigh;
  uint64_t size_b = g_v_bin[vb].deg;

  word_t size = 0;
  word_t pos0 = 0, pos1 = 0;
  word_t a, b;
#ifdef BOUNDARY_CHECK
  if(size_a == 0 || size_b == 0 || list_a[size_a - 1] < list_b[0] || list_a[0] > list_b[size_b - 1])
    return 0;
#endif
  while(pos0 < size_a && pos1 < size_b){
    a = list_a[pos0];
    b = list_b[pos1];
    if(a >= threshold)
      break;
    if(b >= threshold)
      break;
    if(a <= b)
      pos0++;
    if(a >= b)
      pos1++;
    if(a == b)
      list_r[size++] = a;
    }
  return size;
}

word_t intersection_idx(vertex_t* g_v_bin, uint64_t v1, uint64_t idx_a, uint64_t idx_b){
  uint64_t va = g_v_bin[v1].neigh[idx_a];
  uint64_t vb = g_v_bin[v1].neigh[idx_b];
  ptr list_a = g_v_bin[va].neigh;
  uint64_t size_a = g_v_bin[va].deg;
  ptr list_b = g_v_bin[vb].neigh;
  uint64_t size_b = g_v_bin[vb].deg;

  word_t size = 0;
  word_t pos0 = 0, pos1 = 0;
  word_t a, b;
#ifdef BOUNDARY_CHECK
  if(size_a == 0 || size_b == 0 || list_a[size_a - 1] < list_b[0] || list_a[0] > list_b[size_b - 1])
    return 0;
#endif
  while(pos0 < size_a && pos1 < size_b){
    a = list_a[pos0];
    b = list_b[pos1];
    if(a <= b)
      pos0++;
    if(a >= b)
      pos1++;
    if(a == b)
      size++;
    }
  return size;
}


word_t intersection_store_idx(vertex_t* g_v_bin, uint64_t v1, uint64_t idx_a, uint64_t idx_b, ptr list_r){
  uint64_t va = g_v_bin[v1].neigh[idx_a];
  uint64_t vb = g_v_bin[v1].neigh[idx_b];
  ptr list_a = g_v_bin[va].neigh;
  uint64_t size_a = g_v_bin[va].deg;
  ptr list_b = g_v_bin[vb].neigh;
  uint64_t size_b = g_v_bin[vb].deg;

  word_t size = 0;
  word_t pos0 = 0, pos1 = 0;
  word_t a, b;
#ifdef BOUNDARY_CHECK
  if(size_a == 0 || size_b == 0 || list_a[size_a - 1] < list_b[0] || list_a[0] > list_b[size_b - 1])
    return 0;
#endif
  while(pos0 < size_a && pos1 < size_b){
    a = list_a[pos0];
    b = list_b[pos1];
    if(a <= b)
      pos0++;
    if(a >= b)
      pos1++;
    if(a == b)
      list_r[size++] = a;
    }
  return size;
}

word_t intersection_constrain_idx(vertex_t* g_v_bin, uint64_t v1, uint64_t idx_a, uint64_t idx_b, uint64_t threshold){
  uint64_t va = g_v_bin[v1].neigh[idx_a];
  uint64_t vb = g_v_bin[v1].neigh[idx_b];
  ptr list_a = g_v_bin[va].neigh;
  uint64_t size_a = g_v_bin[va].deg;
  ptr list_b = g_v_bin[vb].neigh;
  uint64_t size_b = g_v_bin[vb].deg;

  word_t size = 0;
  word_t pos0 = 0, pos1 = 0;
  word_t a, b;
#ifdef BOUNDARY_CHECK
  if(size_a == 0 || size_b == 0 || list_a[size_a - 1] < list_b[0] || list_a[0] > list_b[size_b - 1])
    return 0;
#endif
  while(pos0 < size_a && pos1 < size_b)
  {
    a = list_a[pos0];
    b = list_b[pos1];
    if(a >= threshold)
      break;
    if(b >= threshold)
      break;
    if(a <= b)
      pos0++;
    if(a >= b)
      pos1++;
    if(a == b)
      size++;
  }
  return size;
}

word_t intersection_store_constrain_idx(vertex_t* g_v_bin, uint64_t v1, uint64_t idx_a, uint64_t idx_b, ptr list_r, uint64_t threshold){
  uint64_t va = g_v_bin[v1].neigh[idx_a];
  uint64_t vb = g_v_bin[v1].neigh[idx_b];
  ptr list_a = g_v_bin[va].neigh;
  uint64_t size_a = g_v_bin[va].deg;
  ptr list_b = g_v_bin[vb].neigh;
  uint64_t size_b = g_v_bin[vb].deg;
  
  word_t size = 0;
  word_t pos0 = 0, pos1 = 0;
  word_t a, b;
#ifdef BOUNDARY_CHECK
  if(size_a == 0 || size_b == 0 || list_a[size_a - 1] < list_b[0] || list_a[0] > list_b[size_b - 1])
    return 0;
#endif
  while(pos0 < size_a && pos1 < size_b){
    a = list_a[pos0];
    b = list_b[pos1];
    if(a >= threshold)
      break;
    if(b >= threshold)
      break;
    if(a <= b)
      pos0++;
    if(a >= b)
      pos1++;
    if(a == b)
      list_r[size++] = a;
    }
  return size;
}

#endif