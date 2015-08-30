/** \file fetchmail.h  header file for fetchmail */
#ifndef _FETCHMAIL_H
#define _FETCHMAIL_H
/*
 * For license terms, see the file COPYING in this directory.
 */

/* We need this for HAVE_STDARG_H, etc */
#include "config.h"

/* We need this for size_t */
#include <sys/types.h>

/*
 * We #ifdef this and use flag rather than bool
 * to avoid a type clash with curses.h
 */
#ifndef TRUE
#define FALSE	0
#define TRUE	1
#endif /* TRUE */
typedef	char	flag;

/* rfc822.c: RFC822 header parsing */
char *reply_hack(char *, const char *, size_t *);
char *nxtaddr(const char *);

/* base64.c */
void to64frombits(char *, const void *, int);
int from64tobits(void *, const char *, int maxlen);

/* unmime.c */
/* Bit-mask returned by MimeBodyType */
#define MSG_IS_7BIT       0x01
#define MSG_IS_8BIT       0x02
#define MSG_NEEDS_DECODE  0x80
extern void UnMimeHeader(char *buf);
extern int  MimeBodyType(char *hdrs, int WantDecode);
extern int  UnMimeBodyline(char **buf, flag delimited, flag issoftline);

#include "xmalloc.h"

#endif
/* fetchmail.h ends here */