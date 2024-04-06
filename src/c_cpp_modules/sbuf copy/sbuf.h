#ifndef SBUF_H
#define SBUF_H

#include <stddef.h> // size_t
#include <fcntl.h>  // off_t
#include "sbufio.h" // off_t

/**************************************
 * segbuf
 */

/* Operations */
void sbuf_pwd();
void sbuf_concat();
void sbuf_substr();
void sbuf_load_str();
void sbuf_as_str();
void sbuf_to_str();

#endif