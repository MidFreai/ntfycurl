#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

#include "dasb.h"

void print_help(char* program_name){
  printf("%s HELP\n", program_name);
}

int main(int argc, char **argv){
  char* program_name = argv[0];
  shift(argv,argc);

  if(argc < 1){
    print_help(program_name);
    return 0;
  }

  String_Builder Postfield = {0};
  String_Builder Title = {0};
  sb_append_cstr(&Title, "Title: ");

  char* url = "https://ntfy.sh/te2LHOA1g4-middo-0";
  char* message = "";

  struct curl_slist *headers = NULL;
  CURL *curl;
  CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
  if(result != CURLE_OK) return (int)result;
  curl = curl_easy_init();

  int data = 0;
  int titulo = 0;
  char* command = argv[0];
  shift(argv, argc);
  if(!strcmp(command, "-h")){
    print_help(program_name);
    return 0;
  }

  do{
    if(!strcmp(command, "-d") && !data){
      if(argc == 0){
        printf("Argumentos insuficientes para -d\n");
        print_help(program_name);
        return 0;
      }else{
        message = argv[0];
        shift(argv, argc);
        data = 1;
        if(argc > 0){ command = argv[0]; shift(argv, argc); }
      }
    }
    if(!strcmp(command, "-t") && !titulo){
      if(argc == 0){
        printf("Argumentos insuficientes para -t\n");
        print_help(program_name);
        return 0;
      }else{
        sb_append_cstr(&Title, argv[0]);
        shift(argv, argc);
        titulo = 1;
        if(argc > 0){ command = argv[0]; shift(argv, argc); }
      }
    }
  }while(argc > 0);

  if(argc == 0 && !data) {
    message = command;
    data = 1;
  }

  if(curl){
    sb_append_cstr(&Postfield, message);
    sb_append_cstr(&Postfield, " : Mensagem enviada de Omarchy");
    if(!titulo){
      sb_append_cstr(&Title, "Omarchy");
    }
    headers = curl_slist_append(headers, Title.items);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, Postfield.items);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    result = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  sb_free(Postfield);
  return 0;
}
