FROM ubuntu:16.04

RUN apt-get update && \
    apt-get install -y g++ vim

WORKDIR /app

COPY hello.cpp .

RUN g++ hello.cpp -o hello

CMD ["./hello"]