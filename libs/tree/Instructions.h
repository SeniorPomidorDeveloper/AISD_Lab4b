#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

typedef enum Side
{
    LEFT,
    RIGHT
} Side;

typedef enum Find_status
{
    FOUND=6,
    NOT_FOUND
} Find_status;

typedef enum Moving_status
{
    MOVING,
    IS_ROOT,
    NO_NEED,
    MERGED
} Moving_status;

#endif // INSTRUCTIONS_H