#ifndef __EPGGRAB_H__
#define __EPGGRAB_H__

#include <pthread.h>
#include "cron.h"

/* **************************************************************************
 * Type definitions
 * *************************************************************************/

/*
 * Grab statistics
 */
typedef struct epggrab_stats_part
{
  int created;
  int modified;
  int total;
} epggrab_stats_part_t;

typedef struct epggrab_stats
{
  epggrab_stats_part_t channels;
  epggrab_stats_part_t brands;
  epggrab_stats_part_t seasons;
  epggrab_stats_part_t episodes;
  epggrab_stats_part_t broadcasts;
} epggrab_stats_t;

/*
 * Grabber base class
 */
typedef struct epggrab_module
{
  const char* (*name)    ( void );
  void        (*enable)  ( void );
  void        (*disable) ( void );
  htsmsg_t*   (*grab)    ( const char *opts );
  int         (*parse)   ( htsmsg_t *data, epggrab_stats_t *stats );
  void        (*ch_add)  ( struct channel *ch );
  void        (*ch_rem)  ( struct channel *ch );
  void        (*ch_mod)  ( struct channel *ch );
} epggrab_module_t;

/*
 * Schedule specification
 */
typedef struct epggrab_sched
{ 
  LIST_ENTRY(epggrab_sched) es_link;
  cron_t                    cron;  ///< Cron definition
  epggrab_module_t          *mod;  ///< Module
  char                      *opts; ///< Extra (advanced) options
} epggrab_sched_t;

/*
 * Schedule list
 */
LIST_HEAD(epggrab_sched_list, epggrab_sched);
typedef struct epggrab_sched_list epggrab_sched_list_t;

/* **************************************************************************
 * Variables
 * *************************************************************************/

/*
 * Lock this if accessing configuration
 */
pthread_mutex_t epggrab_mutex;

/* **************************************************************************
 * Functions
 * *************************************************************************/

/*
 * Setup
 */
void epggrab_init ( void );

/*
 * Access the list of supported modules
 */
//epggrab_module_t** epggrab_module_list         ( void );
epggrab_module_t*  epggrab_module_find_by_name ( const char *name );

/*
 * Set configuration
 */
void epggrab_set_simple   ( uint32_t interval, epggrab_module_t* mod );
void epggrab_set_advanced ( uint32_t count, epggrab_sched_t* sched );
void epggrab_set_eit      ( uint32_t eit );

/*
 * Channel handling
 */
void epggrab_channel_add ( struct channel *ch );
void epggrab_channel_rem ( struct channel *ch );
void epggrab_channel_mod ( struct channel *ch );

#endif /* __EPGGRAB_H__ */