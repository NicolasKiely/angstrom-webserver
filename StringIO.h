#ifndef _STRINGIO_H_
#define _STRINGIO_H_

/** Default buffer chunk size */
#define BUFFER_SIZE 4096

/* Name of server */
#define SERVER_NAME "Angstrom/0.0.1"

/**
 * HTTP header template string. Parameterized by:
 * - [integer] Content length
 * - [string] Server name
 */
#define HTTP_HEADER "HTTP/1.0 200 OK\n" \
  "Content-Type: text/text; charset=UTF-8\n" \
  "Content-Length: %d\n" \
  "Server: %s\n" \
  "\n"


/**
 * Resizeable string buffer
 */
typedef struct {
  char *buf; // Data buffer
  int size;  // Allocated buffer size
  int len;   // String length
} StringBuffer;


/**
 * Creates newly allocated buffer
 */
StringBuffer *newBuffer();

/**
 * Frees string buffer
 * @param str Buffer to deallocate
 */
void freeBuffer(StringBuffer *str);

/**
 * Reads file and returns contents as string buffert
 * @param filename Name of file to read
 */
StringBuffer *readFile(char *filename);


/**
 * Builds full http response from file
 */
StringBuffer *buildResponse(char *filename);

#endif
