#pragma once
#include <iostream>
#include <string>
#include <utility>

class GameException : public std::exception {
private:
    std::string message;
public:
    explicit GameException(std::string  msg) : message(std::move(msg)) {}
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

class GameInitException : public GameException {
public:
    using GameException::GameException;
};

class ObjectException : public GameException {
public:
    using GameException::GameException;
};

class EnemyException : public GameException {
public:
    using GameException::GameException;
};
