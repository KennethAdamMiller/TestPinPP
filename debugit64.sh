#!/bin/sh
tool=$1
shift
sudo $PIN_ROOT/pin -pause_tool 30 -t $tool -- $@
