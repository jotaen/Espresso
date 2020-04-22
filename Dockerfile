FROM gcc:9.3.0

WORKDIR /app
COPY . ./

ENTRYPOINT ["./runtest"]
