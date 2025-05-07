#!/usr/bin/env bash

mkdir -p test/include/
cp -r src/ test/include/
cp -r include/ test/include/
cp CMakeLists.txt test/include/

docker compose -f test/docker-compose.yaml build

# Run docker-compose up (this builds the containers and starts the services)
docker compose -f test/docker-compose.yaml up -d db

# Run the tests
docker compose -f test/docker-compose.yaml run --rm test

# docker compose -f test/docker-compose.yaml down

rm -r test/include