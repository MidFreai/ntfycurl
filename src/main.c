#include <stdio.h>
#include <curl/curl.h>

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

  if(argc == 1) message = argv[0];

  if(curl){
    sb_append_cstr(&Postfield, message);
    sb_append_cstr(&Postfield, " : Mensagem enviada de Omarchy");

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
