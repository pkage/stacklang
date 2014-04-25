#! /bin/sh

slang++ core.cpp -o slang -DSL_COMPILER=\"clang++\" -DSL_DATE_COMPILED="__TIME__ + \", \" __DATE__"
