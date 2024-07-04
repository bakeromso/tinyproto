# Use official Ubuntu rolling base image
FROM ubuntu:24.04

# Install gcc, g++, and make
RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    make \
    cmake \
    pkg-config 

RUN apt-get update && apt-get install -y \
    git

# Since the packed Cpputest is problematic for Ubuntu, let's build it ourselves
RUN cd \root && \
    git clone https://github.com/cpputest/cpputest.git && \
    cd cpputest && \ 
    mkdir cpputest_build && \ 
    cmake -S . -B cpputest_build && \ 
    cd cpputest_build && \
    make install 


CMD [ "/bin/bash" ]