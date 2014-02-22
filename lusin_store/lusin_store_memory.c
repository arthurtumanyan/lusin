/*
    Lusin is a simple traffic accounting software.
    Copyright (C) 2013  Arthur Tumanyan <arthurtumanyan@google.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "lusin_store.h"

void * xmalloc(size_t size) {
    void * new_mem = (void *) malloc(size);

    if (new_mem == NULL) {
        fprintf(stderr, "Cannot allocate memory... Dying\n");
        exit(EXIT_FAILURE);
    }

    return new_mem;
}

void * xrealloc(void * ptr,
        size_t size) {
    void * new_mem = (void *) realloc(ptr, size);

    if (new_mem == NULL) {
        fprintf(stderr, "Cannot allocate memory... Dying\n");
        exit(EXIT_FAILURE);
    }

    return new_mem;
}

void * xcalloc(size_t nmemb,
        size_t size) {
    void * new_mem = (void *) calloc(nmemb, size);

    if (new_mem == NULL) {
        fprintf(stderr, "Cannot allocate memory... Dying\n");
        exit(EXIT_FAILURE);
    }

    return new_mem;
}
