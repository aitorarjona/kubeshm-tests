FROM ubuntu:22.04 as builder

RUN apt update \
    && apt upgrade -y \
    && apt install build-essential -y

WORKDIR /app

COPY client.cpp master.cpp ./

RUN g++ -o client client.cpp
RUN g++ -o master master.cpp

FROM ubuntu:22.04

WORKDIR /app

COPY --from=builder /app/client /app/master ./
