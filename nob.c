#include "./buildsys/utils.c"

int main(int argc, char *argv[]){
  NOB_GO_REBUILD_URSELF_PLUS(argc, argv, "./buildsys/utils.c");

  bool* run = flag_bool("run", false, "Run the program");

  basicFlagParse(argc, argv);

  Nob_Cmd cmd = {0};

  nob_cmd_append(&cmd, "clang", "src/main.c", "-o", "ntfy", "-lcurl", "-Wall", "-Wextra");
  nob_cmd_run(&cmd);

  if(*run){
    nob_cmd_append(&cmd, "./ntfy");
    nob_cmd_run(&cmd);
  }

  return 0;
}
