//
// Created by Hindrik  Stegenga on 15/08/2018.
//

#ifndef VKRENDERER_NOMOREITEMSEXCEPTION_H
#define VKRENDERER_NOMOREITEMSEXCEPTION_H

#include <exception>

using std::exception;

class NoMoreItemsException final : public exception {
public:
    const char *what() const noexcept override;
};


#endif //VKRENDERER_NOMOREITEMSEXCEPTION_H
