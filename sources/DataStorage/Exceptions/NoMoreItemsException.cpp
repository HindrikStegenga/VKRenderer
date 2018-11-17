//
// Created by Hindrik  Stegenga on 15/08/2018.
//

#include "NoMoreItemsException.h"

const char *NoMoreItemsException::what() const noexcept {
    return "There are no items left to use!";
}
