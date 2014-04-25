#ifndef _CORE_GAME_EVENT_
#define _CORE_GAME_EVENT_

typedef enum GameType{
    EV_1,
    EV_2,
    EV_MORE_LUMBERJACK,
    EV_LESS_LUMBERJACK,
    EV_MORE_PICKMAN,
    EV_LESS_PICKMAN,
    EV_MORE_HUNTER,
    EV_LESS_HUNTER,
    EV_MORE_GATHERER,
    EV_LESS_GATHERER,
    EV_SELECT_RAIN,
    EV_SELECT_SUN,
    EV_VALID,
    EV_DEFAULT
} GameType;


typedef struct GameEvent {
    GameType type;
    int number;
    std::string text;
} GameEvent;

#endif // _CORE_GAME_EVENT_
