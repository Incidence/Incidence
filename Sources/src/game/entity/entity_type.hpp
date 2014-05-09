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
    S_VERY_WEAK,
    S_TIRED_GOOD,
    S_TIRED_NORMAL,
    S_TIRED_WEAK,
    S_TIRED_VERY_WEAK
}StateType;

#endif
