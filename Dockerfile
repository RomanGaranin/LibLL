FROM ubuntu:latest
RUN apt-get upgrade
RUN apt-get update  -y
RUN apt-get install -y git 
RUN apt-get install -y gcc
RUN apt-get install -y g++
RUN apt-get install -y libgtest-dev 
RUN apt-get install -y cmake
RUN apt-get install -y ninja-build 
