/*
 * Copyright (c) 2007-2012, Paul Meng (mirnshi@gmail.com)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met:
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
**/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

#define MAX_LEN  (128)

char *getkv(char *str)
{
	static char buf[MAX_LEN];
	static char *p;
	
	if (str != NULL) {
		memset(buf, 0, sizeof(buf));
		strncpy(buf, str, strlen(str));
		p = strtok(buf, " \t");
	} else 
		p = strtok(NULL, " \t");

	return p;
}

int mkargv(char *str, char **argv, int max)
{
	int n = 0;
	char *p;
	char **args = argv;
	static char buf[MAX_LEN];
	
	if (str != NULL) {
		memset(buf, 0, sizeof(buf));
		strncpy(buf, str, strlen(str));

		p = strtok(buf, "=/ \t");
		while (p != NULL && n < max) {
			args[n++] = p;
			p = strtok(NULL, "=/ \t");
		}
	}
	args[n] = NULL;
	return n;
}

int insert_argv(int argc, char **argv, char *str)
{
	char *av[20];
	int i;
	
	for (i = 0; i < argc; i++)
		av[i] = argv[i];
	
	argv[0] = str;
	for (i = 0; i < argc; i++)
		argv[i + 1] = av[i];
	
	return (argc + 1);
}

int timeout(struct timeval tv, int mseconds)
{
	struct timeval tvx;
	unsigned int usec;
	
	gettimeofday(&(tvx), (void*)0);
	usec = (tvx.tv_sec - tv.tv_sec) * 1000000 + tvx.tv_usec - tv.tv_usec;

	return ((usec / 1000) >=  mseconds);
}

int digitstring(const char *s)
{
	int i = 0;
	
	if (s == NULL)
		return 0;

	while (*s >= '0' && *s <= '9') {
		s++;
		i++;
		if (*s == '\0')
			return i;
	}
	return 0;
}

char *ttrim(char *s)
{
	int len;
	
	if (s == NULL)
		return NULL;
	len = strlen(s);
	len--;
	while (len >= 0 && isspace(s[len]))
		len--;
	
	s[len + 1] = '\0';	
	
	return s;
}
int arg2int(const char* arg, int min, int max, int defval)
{
	int r;

	if (arg == NULL || sscanf(arg, "%d", &r) != 1)
		return defval;
	
	return r;
}
#if 0
void preh(u_char *e)
{
	int i;
	
	for (i = 0; i < 6; i++)
		printf("%2.2x ", *(e + i));
	return;
}
#endif

/* end of file */
