#!/bin/sh
tool=$1
shift
sudo $PIN_ROOT/pin -t $tool -- $@
