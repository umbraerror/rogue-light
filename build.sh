#!/bin/bash
/usr/bin/clang++ -std=c++20 main.cpp -o rogue_app \
$(pkg-config --cflags --libs sfml-graphics) \
-isysroot "$(xcrun --show-sdk-path)"
