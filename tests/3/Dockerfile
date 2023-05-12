FROM python:3.11-bullseye

RUN apt update \
    && apt upgrade -y \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY server.py client.py ./
