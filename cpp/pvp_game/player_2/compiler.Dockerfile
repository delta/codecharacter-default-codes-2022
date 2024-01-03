FROM gcc:latest

WORKDIR /player_code/pvp_game/player_2

COPY *.cpp *.h Makefile ./

RUN make all

RUN rm run.o

CMD [ "make", "all" ]
