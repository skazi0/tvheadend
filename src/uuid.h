/*
 *  TV headend - UUID generation routines
 *
 *  Copyright (C) 2014 Adam Sutton
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TVH_UUID_H__
#define __TVH_UUID_H__

#include <stdint.h>

#define UUID_BIN_SIZE   (16)
#define UUID_HEX_SIZE   (33) // inc NUL

/* Structure to hold UUID */
typedef struct uuid {
  union {
    uint8_t bin[UUID_BIN_SIZE];
    char    hex[UUID_HEX_SIZE];
  };
} uuid_t;

/* Initialise subsystem */
void uuid_init ( void );

/* Initialise binary */
int uuid_init_bin ( uuid_t *u, const char *str );

/* Initialise hex string */
int uuid_init_hex ( uuid_t *u, const char *str );

/**
 * Convert bin to hex string
 *
 * Note: conversion is done such that a and b can be the same
 */
int uuid_bin2hex  ( const uuid_t *a, uuid_t *b );

/**
 * Convert hex string to bin (in place)
 *
 * Note: conversion is done such that a and b can be the same
 */
int uuid_hex2bin  ( const uuid_t *a, uuid_t *b );

/**
 * Hex string to binary
 */
int hex2bin ( uint8_t *buf, size_t buflen, const char *hex );

/**
 * Binary to hex string
 */
void bin2hex ( char *dst, size_t dstlen, const uint8_t *src, size_t srclen );

#endif /* __TVH_UUID_H__ */
