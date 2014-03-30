#ifndef _ENTITY_TYPE_
#define _ENTITY_TYPE_

typedef enum {
    ALLY_CITIZEN,
    ENEMY_CITIZEN,
    WILD_ANIMAL,
    PEACEFUL_ANIMAL,
    DEFAULT_ENTITY
} EntityType;

typedef enum {
    MOVE,
    MOVE_HOME,
    MOVE_RESOURCE,
    INTERACT_HOME,
    INTERACT_RESOURCE,
    ATTACK,
    RECOLT,
    IDLE
} Action;

typedef enum {
    GOOD,
    NORMAL,
    WEAK,
    VERY_WEAK,
    DEAD
} Health;

#endif
