#########################################################################
# File Name: build.sh
# Author: starjiang
# mail: 82776315@qq.com
# Created Time: Thu 11 Dec 2014 03:50:20 PM SGT
#########################################################################
#!/bin/bash
g++ -oanyvalue.so -O2 -shared -fPIC decode.cpp encode.cpp anyvalue.cpp
