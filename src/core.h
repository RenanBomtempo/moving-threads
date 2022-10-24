#ifndef CORE_H
#define CORE_H

#ifdef DEBUG
#define DEBUG_LOG(...) printf(__VA_ARGS__);
#else
#define DEBUG_LOG(...)
#endif

#define MAX_GRID_LENGTH 20
#define MAX_PATH_LENGTH 2 * MAX_GRID_LENGTH

#endif