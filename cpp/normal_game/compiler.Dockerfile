FROM gcc:latest

WORKDIR /player_code/normal_game

COPY *.cpp *.h Makefile ./

RUN make all

RUN rm run.o

CMD [ "make", "all" ]
