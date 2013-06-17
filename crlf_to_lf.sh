#!/bin/sh
find . -type f | xargs file | sed -nr 's/^([^:]*).*CRLF.*/\1/p' | xargs -I {} dos2unix {}