FROM gcc:latest

WORKDIR /pvp_game/player_1

COPY *.cpp *.h Makefile ./

RUN make all

RUN rm run.o

CMD [ "make", "all" ]
