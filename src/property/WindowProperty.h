//
// Created by rmamin1337 on 11.11.2024.
//
#pragma once

#include <yaml-cpp/yaml.h>

#include <string>

#ifndef WINDOWPROPERTY_H
#define WINDOWPROPERTY_H

class WindowProperty {
public:
    std::string title;
    int width;
    int height;
    bool isVsyncEnable;

    void parse(const YAML::Node& node);
};

#endif  // WINDOWPROPERTY_H