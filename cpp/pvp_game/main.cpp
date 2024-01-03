#include "../player_code.h"

#include<fstream>

std::ofstream fs;
std::ofstream fs2;
std::ofstream fs3;

void init_constants() {

  fs << "from init_constants\n";

  std::cin >> Constants::NO_OF_TURNS >> Constants::MAX_NO_OF_COINS;

  fs << "Constants::NO_OF_TURNS = " << Constants::NO_OF_TURNS << "\n";
  fs << "Constants::MAX_NO_OF_COINS = " << Constants::MAX_NO_OF_COINS << "\n";
  fs.flush();

  // All the attacker types
  std::cin >> Constants::NO_OF_ATTACKER_TYPES;

  fs << "Constants::NO_OF_ATTACKER_TYPES = " << Constants::NO_OF_ATTACKER_TYPES << "\n";
  fs.flush();

  std::unordered_map<size_t, Attributes> attacker_type_to_attributes;
  for (size_t i = 1; i <= Constants::NO_OF_ATTACKER_TYPES; i++) {
    unsigned hp, range, attack_power, speed, price, is_aerial;
    std::cin >> hp >> range >> attack_power >> speed >> price >> is_aerial;
    attacker_type_to_attributes.insert(
        std::make_pair(i, Attributes(hp, range, attack_power, speed, price, is_aerial)));
  }
  Constants::ATTACKER_TYPE_ATTRIBUTES = attacker_type_to_attributes;

  // All the defender types
  std::cin >> Constants::NO_OF_DEFENDER_TYPES;

  fs << "Constants::NO_OF_DEFENDER_TYPES = " << Constants::NO_OF_DEFENDER_TYPES << "\n";
  fs.flush();

  std::unordered_map<size_t, Attributes> defender_type_to_attributes;
  for (size_t i = 1; i <= Constants::NO_OF_DEFENDER_TYPES; i++) {
    unsigned hp, range, attack_power, speed, price, is_aerial;
    std::cin >> hp >> range >> attack_power >> speed >> price >> is_aerial;
    defender_type_to_attributes.insert(
        std::make_pair(i, Attributes(hp, range, attack_power, speed, price, is_aerial)));
  }
  Constants::DEFENDER_TYPE_ATTRIBUTES = defender_type_to_attributes;
}

void init_map_for_pvp(size_t no_of_rows, size_t no_of_cols) {
  std::vector<std::vector<int>> map(no_of_rows, std::vector<int>(no_of_cols, 0));
  Constants::MAP_NO_OF_ROWS = no_of_rows;
  Constants::MAP_NO_OF_COLS = no_of_cols;
}

void output(size_t turn_no, Game &game) {

  // Player logs are logged to cerr, so that driver will collect it
  game.logr().flush();
  if (!game.logr().view().empty()) {
    std::cerr << "TURN " << turn_no << '\n';
    std::cerr << game.logr().view() << '\n';
    std::cerr << "ENDLOG" << std::endl;
  }

  // Game details logged
  const auto &spawn_positions = game.get_spawn_positions();
  const auto &player_set_targets = game.get_player_set_targets();

  std::cout << spawn_positions.size() << std::endl;
  fs << "spawn_positions.size() = " << spawn_positions.size() << "\n";
  fs.flush();

  for (const auto &entry : spawn_positions) {
    std::cout << entry.first << " " << entry.second.get_x() << " "
              << entry.second.get_y() << std::endl;
  }

  std::cout << player_set_targets.size() << std::endl;
  for (const auto &entry : player_set_targets) {
    std::cout << entry.first << " " << entry.second << std::endl;
  }
}

void dump_logs(PvPState& state, Game &game) {}

PvPState pvp_next_state(size_t cur_turn_no) {

  size_t no_of_active_opponent_attackers;
  size_t no_of_active_attackers;

  std::cin >> no_of_active_attackers;
  std::vector<Attacker> attackers;


  fs2 << "Turn no: " << cur_turn_no << "\n"; 
  fs2 << "no_of_active_attackers = " << no_of_active_attackers << "\n";
  fs2.flush();

  for (size_t i = 0; i < no_of_active_attackers; i++) {
    size_t id, hp, x, y, type;
    std::cin >> id >> x >> y >> type >> hp;
    attackers.push_back(Attacker(id, hp, type, Position(x, y)));
  }
  
  std::cin >> no_of_active_opponent_attackers;

  fs2 << "no_of_active_opponent_attackers = " << no_of_active_opponent_attackers << "\n";
  fs2.flush();

  std::vector<Attacker> opponent_attackers;
  for (size_t i = 0; i < no_of_active_opponent_attackers; i++) {
    size_t id, hp, x, y, type;
    std::cin >> id >> x >> y >> type >> hp;
    opponent_attackers.push_back(Attacker(id, hp, type, Position(x, y)));
  }

  size_t coins_left;
  std::cin >> coins_left;

  fs2 << "coins_left = " << coins_left << "\n";
  fs2.flush();

  return {move(attackers), move(opponent_attackers), coins_left, cur_turn_no + 1};
}

int main() {
  fs.open("/home/bhoopesh/Desktop/codecharacter-driver-2023/main.txt");
  fs2.open("/home/bhoopesh/Desktop/codecharacter-driver-2023/pvp_next_state.txt");
  fs3.open("/home/bhoopesh/Desktop/codecharacter-driver-2023/runner.txt");

  init_constants();

  fs.flush();

  fs << "init_constants DONE\n";
  fs.flush();

  init_map_for_pvp(64, 64);

  PvPState state({}, {}, Constants::MAX_NO_OF_COINS, 0);

  fs << "PvPState state({}, Constants::MAX_NO_OF_COINS, 0); INITIALIZED\n";

  // log the entrie game state into fs

  fs << "state.get_turn_no() = " << state.get_turn_no() << "\n";
  fs << "state.get_attackers().size() = " << state.get_attackers().size() << "\n";
  fs << "state.get_opponent_attackers().size() = " << state.get_opponent_attackers().size() << "\n";
  fs.flush();

  auto game = run(state, fs3);
  output(state.get_turn_no(), game);
  
  for (size_t i = 0; i < Constants::NO_OF_TURNS; i++) {
    state = pvp_next_state(state.get_turn_no());
    fs << "state.get_turn_no() = " << state.get_turn_no() << "\n";
    fs << "state.get_coins_left() = " << state.get_coins_left() << "\n";
    fs << "state.get_attackers().size() = " << state.get_attackers().size() << "\n";
    fs << "state.get_opponent_attackers().size() = " << state.get_opponent_attackers().size() << "\n";
    fs.flush();
    game = run(state, fs3);
    output(state.get_turn_no(), game);
  }
}
