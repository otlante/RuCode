FROM gcc:latest
WORKDIR /app
RUN apt-get update && apt-get install -y coreutils diffutils
COPY run.sh /app/run.sh
RUN chmod +x /app/run.sh
ENTRYPOINT ["/app/run.sh"]