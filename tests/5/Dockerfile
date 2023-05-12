FROM ubuntu:22.04 as builder

RUN apt update \
    && apt upgrade -y \
    && apt install build-essential -y

WORKDIR /app

COPY client.cpp server.cpp ./

RUN g++ -Wall -O3 -o client client.cpp
RUN g++ -Wall -O3 -o server server.cpp

FROM ubuntu:22.04

WORKDIR /app

COPY --from=builder /app/client /app/server ./
