#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "StringIO.h"


StringBuffer *newBuffer()
{
  StringBuffer *str = (StringBuffer *) malloc(sizeof(StringBuffer));
  str->buf = (char *) malloc(BUFFER_SIZE);
  str->size = BUFFER_SIZE;
  str->len = 0;

  return str;
}


void freeBuffer(StringBuffer *str)
{
  if (!str)
    return;
  if (str->buf)
    free(str->buf);
  free(str);
}


StringBuffer *readFile(char *filename)
{
  int fd = open(filename, O_RDONLY);
  if (fd == -1){
    printf("Error, cannot open file for read\n");
    return NULL;
  }

  StringBuffer *str = newBuffer();

  // Read loop
  while (1){
    int sz = read(fd, str->buf, BUFFER_SIZE);

    // Handle response
    if (sz < 0){
      // Error
      close(fd);
      freeBuffer(str);
      printf("Error raised when reading from file\n");
      return NULL;

    } else if (sz == 0){
      // EOF
      break;
    }

    // Update buffer struct
    str->len += sz;
    if (str->len + BUFFER_SIZE > str->size){
      // Resize buffer
      str->size *= 2;
      str->buf = realloc(str->buf, str->size);
    }
  }

  // Finished reading file
  close(fd);
  return str;
}


StringBuffer *buildResponse(char *filename)
{
  // Read in file contents
  StringBuffer *str = readFile(filename);
  if (str == NULL)
    return NULL;

  // Setup http header template
  char *tmpl = HTTP_HEADER;
  int tmplLen = strlen(tmpl);
  char *sname = SERVER_NAME;

  // Create http header
  int hdrsz = tmplLen + BUFFER_SIZE;
  char *hdr = malloc(hdrsz);
  snprintf(hdr, hdrsz, HTTP_HEADER, str->len, sname);
  int hdrlen = strlen(hdr);

  // Combine header with response
  hdr = realloc(hdr, hdrlen + str->len);
  memcpy(hdr, str->buf, hdrlen-1);
  free(str->buf);
  str->buf = hdr;

  return str;
}
