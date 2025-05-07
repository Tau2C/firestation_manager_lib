# Dockerfile

# Use an official Ubuntu base image
FROM ubuntu:25.04

# Install dependencies
RUN apt-get update &&  \
    apt-get install -y \
    g++                \
    cmake              \
    libpqxx-dev        \
    make               \
    git                \
    postgresql-client  \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update &&  \
    apt-get install -y \
    libgtest-dev       \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Build Google Test
RUN cd /usr/src/gtest && cmake . && make && cp lib/* /usr/lib/

# Copy the necessary files to the container
COPY . /app
RUN chmod +x /app/wait-for-db.sh

# Build library
RUN rm -rf build-tests && mkdir build-tests && cd build-tests && cmake .. && make

# Set the entrypoint to run tests
CMD ["sh", "-c", "/app/wait-for-db.sh && ctest --test-dir /app/build-tests/tests --output-on-failure"]
