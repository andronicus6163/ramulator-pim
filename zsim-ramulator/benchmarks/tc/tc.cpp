#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <sys/types.h>
#include <sys/time.h>
#include <omp.h>
//#define NUM_THREAD 4
#include "../../misc/hooks/zsim_hooks.h"

#include "intersect.hpp"

#define USAGE "USAGE: ./three_clique_baseline <gv_bin> <nl_bin> <mode> <start> <stop>"
#if defined GEM5_MODE
    #include "gem5/m5ops.h"
#endif



typedef struct vertex_local vertexl_t;
typedef vertex_t* vertexptr;


word_t three_clique_count_cpu(uint64_t svert, uint64_t evert, vertexptr g_v_bin, int num_omp_threads)
{
    word_t count = 0;
    int64_t i1 = 0;
    word_t *local_count = (word_t *)malloc(sizeof(word_t) * (evert - svert));
    for(i1=svert; i1<evert; i1++){
      local_count[i1 - svert] = 0;
    }

zsim_roi_begin();


#pragma omp target data map(to: svert, evert, g_v_bin[svert:evert]) map(from: local_count[0:(evert - svert)])
    {
	//bool stop;
	//do
 //   {
 //       stop = false;

      omp_set_num_threads(num_omp_threads);
      #pragma omp target
      #pragma omp parallel for 
      for(i1=svert; i1<evert; i1++)
      {
          zsim_PIM_function_begin();
          word_t v1 = i1;
          uint64_t deg1 = g_v_bin[v1].schedule_deg;
          if (deg1 == 0)
              continue;
          uint64_t i2;
          for(i2=0; i2<deg1; i2++)
          {
              word_t v2 = g_v_bin[v1].neigh[i2];
              if(v2 >= v1)
                  break;
              uint64_t deg2 = g_v_bin[v2].schedule_deg;
              if (deg2 == 0)
                  continue;

              uint64_t len3 = intersection_constrain_v(g_v_bin, v1, v2, v2);
              local_count[i1 - svert] = local_count[i1 - svert] + len3;
          }
          zsim_PIM_function_end();
      }
  //    stop = true;
  //  }
  //  while(stop);
  }
  for(i1=svert; i1<evert; i1++){
    count = count + local_count[i1 - svert];
  }
zsim_roi_end(); 

return count;
}




void read_and_load_nlistbin(const char* binfilename, const char* binfilename2 , vertexl_t *g_v_bin, uint64_t* nlist_beg){
  printf("Binfile:%s\n", binfilename);
  FILE* in_file_gv = fopen(binfilename, "rb");
  if (!in_file_gv) {
        exit(EXIT_FAILURE);
  }
  FILE* in_file_nl = fopen(binfilename2, "rb");
  if (!in_file_nl) {
        exit(EXIT_FAILURE);
  }
  uint64_t num_nodes, nlist_size = 0;

  size_t file_size;

  fseek(in_file_gv, 0, SEEK_SET);
  fseek(in_file_nl, 0, SEEK_SET);
  file_size = fread(&num_nodes, sizeof(num_nodes),1, in_file_gv);
  file_size = fread(&nlist_size, sizeof(nlist_size), 1, in_file_nl);

  
  file_size = fread(g_v_bin, sizeof(vertexl_t), num_nodes, in_file_gv); // read in all vertices 
  file_size = fread(nlist_beg, sizeof(uint64_t), nlist_size, in_file_nl); // read in all vertices

  fclose(in_file_gv);
  fclose(in_file_nl);
  
  uint64_t num_edges = 0;
  uint64_t max_deg = 0;
#ifdef TESTBIN
  printf("NumVerts:%lu\n", num_nodes);
#endif
  for(int i = 0; i < num_nodes; i++){
    g_v_bin[i].neigh = (uint64_t *)((uint64_t)nlist_beg + num_edges * sizeof(uint64_t));
    num_edges += g_v_bin[i].deg;
    if(max_deg < g_v_bin[i].deg)
      max_deg = g_v_bin[i].deg;
#ifdef TESTBIN
    print_array(g_v_bin[i].neigh, g_v_bin[i].deg);
    printf("Input pair %lu: key=%lu deg=%lu nlist_ptr=%lu\n", i, g_v_bin[i].id, g_v_bin[i].deg, g_v_bin[i].neigh);
#endif
  }
  printf("# vertices: %lu , # edges:%lu , avg deg: %lf, max deg: %lu\n", num_nodes, num_edges, ((double)num_edges)/num_nodes, max_deg);
}


void convert_to_new_struct(int num_nodes, vertexl_t *g_v_bin, vertex_t* g_v_bin_new){
  for(int i = 0; i < num_nodes; i++){
    g_v_bin_new[i].id = g_v_bin[i].id;
    g_v_bin_new[i].deg = g_v_bin[i].deg;
    g_v_bin_new[i].neigh = g_v_bin[i].neigh;
    int64_t deg = 0;
    for(deg = 0; deg<g_v_bin[i].deg; deg++){
      if(g_v_bin[i].neigh[deg] >= g_v_bin[i].id)
        break;
    }
    g_v_bin_new[i].schedule_deg = deg;
    g_v_bin_new[i].schedule_neigh = 0;
    g_v_bin_new[i].reserved0 = 0;
    g_v_bin_new[i].reserved1 = 0;
    g_v_bin_new[i].reserved2 = 0;
#ifdef DEBUG
  printf("g_v_bin_new:%lu, i:%lu v:%lu, deg:%lu, neigh:%lu\n", g_v_bin_new, i, g_v_bin_new[i].id, g_v_bin_new[i].deg, g_v_bin_new[i].neigh);
#endif
  }
}



int main(int argc, char* argv[]) {

  if (argc < 2) {
    printf("Insufficient Input Params\n");
    printf("%s\n", USAGE);
    exit(1);
  }
  char* filename = argv[1];
  char* filename2 = argv[2];
	int num_omp_threads; // = atoi(argv[1]);
  int mode = atoi(argv[3]);
	num_omp_threads = atoi(argv[4]);
  uint64_t svert = 0, evert;
  if(mode == 1){
    svert = atoi(argv[4]);
    evert = atoi(argv[5]);
	  num_omp_threads = atoi(argv[6]);
  }
  if(mode == 0){
    printf("Running full graph on validation mode\n");
  }
	omp_set_num_threads(num_omp_threads);	
        printf("Number of threads %d \n", omp_get_max_threads());

 
  printf("File Name:%s , ", filename);


  uint64_t num_edges, num_verts, nlist_size = 0;
  // printf("Binfile:%s\n", filename);

  FILE* in_file_gv = fopen(filename, "rb");
  if (!in_file_gv) {
        exit(EXIT_FAILURE);
  }
  FILE* in_file_nl = fopen(filename2, "rb");
  if (!in_file_nl) {
        exit(EXIT_FAILURE);
  }

  size_t file_size = 0;

  fseek(in_file_gv, 0, SEEK_SET);
  fseek(in_file_nl, 0, SEEK_SET);
  file_size = fread(&num_verts, sizeof(num_verts),1, in_file_gv);
  file_size = fread(&nlist_size, sizeof(nlist_size), 1, in_file_nl);

  fclose(in_file_gv);
  fclose(in_file_nl);


  vertexl_t *g_v_bin = reinterpret_cast<vertexl_t *>(malloc(num_verts * sizeof(vertexl_t)));
  uint64_t* nlist_beg = reinterpret_cast<uint64_t*>(malloc(nlist_size * sizeof(uint64_t)));
  vertex_t *g_v_bin_new = reinterpret_cast<vertex_t *>(malloc(num_verts * sizeof(vertex_t)));
 

  // Load all the neighborlists
  read_and_load_nlistbin(filename, filename2,  g_v_bin, nlist_beg);

  // Convert to different vertex data struct and launch TC

  convert_to_new_struct(num_verts, g_v_bin, g_v_bin_new);

  if(mode == 0 || (mode == 1 && (evert > num_verts))){
    evert = num_verts;
  }

  timeval start,end;

  gettimeofday(&start,NULL);
  word_t cpu_count = three_clique_count_cpu(svert, evert, g_v_bin_new, num_omp_threads);
#if defined GEM5_MODE
  m5_dump_reset_stats(0,0);
#else
  gettimeofday(&end,NULL);
#endif

  double time = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1000000.0;

  printf("Three Clique Count: %lu, time:%lf s\n", cpu_count,time);
  
  return 0;
}
