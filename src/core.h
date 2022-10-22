#ifndef CORE_H
#define CORE_H

#ifdef DEBUG
#define DEBUG_LOG(msg) printf(msg);
#else
#define DEBUG_LOG
#endif

#define MAX_GRID_LENGTH 20
#define MAX_PATH_LENGTH 2 * MAX_GRID_LENGTH

#endif