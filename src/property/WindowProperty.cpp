//
// Created by rmamin1337 on 11.11.2024.
//

#include "WindowProperty.h"

void WindowProperty::parse(const YAML::Node& node) {
    title = node["title"].as<std::string>();
    width = node["width"].as<int>();
    height = node["height"].as<int>();
    isVsyncEnable = node["isVsyncEnable"].as<bool>();
}