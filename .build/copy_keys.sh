#!/bin/bash

find  ~/c/Program\ Files\ \(x86\)/Steam/steamapps/workshop/content/221100/ -iname "*.bikey" -exec sh -c 'file=$1; cp "$file" "/home/wsl/c/Program Files (x86)/Steam/steamapps/common/DayZServer/keys/";' find-sh {} \;
