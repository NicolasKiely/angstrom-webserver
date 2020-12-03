#include <stdlib.h>
#include <stdio.h>

#include "StringIO.h"


/**
 * Entry function
 */
int main(int argc, char *argv[])
{
  if (argc != 3){
    printf("Usage: %s <port #> <file>\n", argv[0]);
    printf("Port # is port to listen on (eg 8010)\n");
    printf("File is document to server over port\n");
    return EXIT_FAILURE;
  }

  char *port = argv[1]; // Port address
  char *filename = argv[2]; // File name

  /* Build http response from file */
  StringBuffer *resp = buildResponse(filename);

  // Exit on failure
  if (resp == NULL)
    return EXIT_FAILURE;

  printf("%s\n", resp->buf);

  return EXIT_SUCCESS;
}
