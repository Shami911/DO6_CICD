#!/bin/bash
file="$HOME/.docker/config.json"
line='"credsStore": "desktop",'
sed -i '' "/$line/d" "$file"

docker build -t "container" .
docker run -it -v $PWD:/tmp -w /tmp container
