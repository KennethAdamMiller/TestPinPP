#!/bin/bash

$MPC_ROOT/mwc.pl -type make -features cpp11=1,pin=1,ia32=0,intel64=1 MPCWorkspace.mwc
touch ArgInterceptorTool
