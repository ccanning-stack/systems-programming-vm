#define _NL_LOCAL_NAME
#include <langinfo.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  setlocale(LC_ALL, "");

  char *lc_ctype = nl_langinfo(_NL_LOCALE_NAME(LC_CTYPE));

  printf("LC_CTYPE=\"%s\"\n", lc_ctype);

  char *lc_name = nl_langinfo(_NL_LOCALE_NAME(LC_NAME));

  printf("LC_NAME=\"%s\"\n", lc_name);

  printf("LC_ALL=%s\n", getenv("LC_ALL") != NULL ? getenv("LC_ALL") : "");
}
