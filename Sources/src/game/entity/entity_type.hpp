#ifndef _ENTITY_TYPE_
#define _ENTITY_TYPE_

typedef enum {
    ALLY_CITIZEN,
    ENEMY_CITIZEN,
    HUNTER,
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


typedef enum{

    A_STAY,
    A_UP,
    A_DOWN,
    A_LEFT,
    A_RIGHT,
    A_HIT,
    A_ACTION
} AnimationType;

typedef enum{

    S_GOOD,
    S_NORMAL,
    S_TIRED,
    S_WEAK,
    S_SICK,
    S_VERY_WEAK,
} StateType;

#endif
