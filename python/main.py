import sys
from player_code import Position, Attacker, Defender, Constants, Map, State, Game, PvPState, GameType
from run import run
from runpvp import run_pvp


all_logs: str = ""


def string_to_game_type(game_type_str) -> GameType:
    if game_type_str.lower() == "normal":
        return GameType.NORMAL
    else:
        return GameType.PVP


def output(turn_no: int, game: Game):
    log_line = game.get_log()
    if log_line and len(log_line)!=0:
        global all_logs
        all_logs += "TURN " + str(turn_no) + "\n"
        all_logs += log_line
        all_logs += "ENDLOG\n"

    sys.stdout.write(f"{len(game.spawn_positions)}\n")
    for id, position in game.spawn_positions:
        sys.stdout.write(f"{id} {position.x} {position.y}\n")

    sys.stdout.write(f"{len(game.player_set_targets)}\n")
    for (attacker_id, defender_id) in game.player_set_targets.items():
        sys.stdout.write(f"{attacker_id} {defender_id}\n")



def next_state(cur_turn_no: int) -> State:
    no_of_active_attackers = int(sys.stdin.readline())
    attackers = []

    for _ in range(no_of_active_attackers):
        id, x, y, a_type, hp = map(int, sys.stdin.readline().split())
        attackers.append(
            Attacker(id, hp, Constants.ATTACKER_TYPE_ATTRIBUTES[a_type], Position(x, y))
        )

    no_of_active_defenders = int(sys.stdin.readline())
    defenders = []

    for _ in range(no_of_active_defenders):
        id, x, y, d_type, hp = map(int, sys.stdin.readline().split())
        defenders.append(
            Defender(id, hp, Constants.DEFENDER_TYPE_ATTRIBUTES[d_type], Position(x, y))
        )

    no_of_coins_left = int(sys.stdin.readline())

    return State(attackers, defenders, no_of_coins_left, cur_turn_no + 1)

def next_pvp_state(cur_turn_no: int) -> PvPState:
    no_of_active_attackers = int(sys.stdin.readline())
    attackers = []

    for _ in range(no_of_active_attackers):
        id, x, y, a_type, hp = map(int, sys.stdin.readline().split())
        attackers.append(
            Attacker(id, hp, Constants.ATTACKER_TYPE_ATTRIBUTES[a_type], Position(x, y))
        )

    no_of_opponent_attackers = int(sys.stdin.readline())
    opponent_attackers = []

    for _ in range(no_of_opponent_attackers):
        id, x, y, d_type, hp = map(int, sys.stdin.readline().split())
        opponent_attackers.append(
            Attacker(id, hp, Constants.DEFENDER_TYPE_ATTRIBUTES[d_type], Position(x, y))
        )

    return PvPState(attackers, opponent_attackers, Constants.PVP_FIXED_COINS, cur_turn_no + 1)


if len(sys.argv) < 2:
    sys.stderr.write(f"Usage: {sys.argv[0]} [game-type]")
    sys.exit(1)

game_type = string_to_game_type(sys.argv[1])

Constants.initialize(game_type)

if game_type == GameType.NORMAL:
    Map.initialize()

    state = State([], Map.spawn_defenders(), Constants.MAX_NO_OF_COINS, 0)

    game = run(state)

    output(state.turn_no, game)

    for i in range(Constants.NO_OF_TURNS):
        state = next_state(state.turn_no)
        game = run(state)
        output(state, game)

elif game_type == GameType.PVP:
    state = PvPState([], [], Constants.PVP_FIXED_COINS, 0)

    game = run_pvp(state)

    output(state.turn_no, game)

    for i in range(Constants.NO_OF_TURNS):
        state = next_pvp_state(state.turn_no)
        game = run_pvp(state)
        output(state.turn_no, game)

sys.stderr.write(all_logs)
