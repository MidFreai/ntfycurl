#define NOB_IMPLEMENTATION
#include "nob.h"

#define FLAG_IMPLEMENTATION
#include "flag.h"

bool help = false;

void basicUsage(char* name){
  fprintf(stderr, "Usage: %s [OPTIONS] [--] [ARGS]\n", name);
  fprintf(stderr, "OPTIONS:\n");
  flag_print_options(stderr);
}

void basicFlagParse(int argc, char* argv[]){
  if(!flag_name(&help)){
    flag_bool_var(&help, "help", false, "Print help");
  }

  if (!flag_parse(argc, argv)){
    basicUsage(argv[0]);
    flag_print_error(stderr);
    exit(1);
  }

  //printf("-%-*s => %s\n", strlen(flag_name(&help)), flag_name(&help), help ? "true" : "false");
  if(help) { basicUsage(argv[0]); exit(0); }
}
