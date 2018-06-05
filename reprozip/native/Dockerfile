# Define build environment for rztracer.
#
# Example usage:
#
#   % docker build --tag rztracer-make .
#   % docker run -it --rm -u1000:1000 -v $PWD/:/tmp -w /tmp rztracer-make

FROM debian:jessie-slim@sha256:c014e4ded347fa8995da96b57bc6edaaec839e2ebbcf2eddb90dc75a4976762f

RUN apt-get update \
    && apt-get install -y gcc make binutils libsqlite3-dev libreadline-dev

RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

ENTRYPOINT ["make"]
