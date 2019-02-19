#include "game.h"

int min(int x, int y) {
    return x < y ? x : y;
}

int max(int x, int y) {
    return x > y ? x : y;
}

int clamp(int lower, int x, int upper) {
    return min(upper, max(x, lower));
}