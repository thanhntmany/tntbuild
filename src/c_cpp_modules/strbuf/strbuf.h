#ifndef STRBUF_H
#define STRBUF_H

struct strbuf {
	size_t len;
	char *buf;
};

#define STRBUF_INIT  { .buf = strbuf_slopbuf }


#endif