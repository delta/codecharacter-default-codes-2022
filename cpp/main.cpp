#include "player_code.h"

std::ostringstream all_logs;

//make global object for holding all ids of attackers whose abilities activated

void init_constants() {
  // All the attacker types
  std::cin >> Constants::NO_OF_ATTACKER_TYPES;

  std::unordered_map<size_t, Attributes> attacker_type_to_attributes;
  for (size_t i = 1; i <= Constants::NO_OF_ATTACKER_TYPES; i++) {
    unsigned hp, range, attack_power, speed, price, is_aerial , weight, num_ability_turns, ability_activation_cost;
    std::cin >> hp >> range >> attack_power >> speed >> price >> is_aerial >> weight >> num_ability_turns >> ability_activation_cost;
    attacker_type_to_attributes.insert(
        std::make_pair(i, Attributes(hp, range, attack_power, speed, price, is_aerial,weight, num_ability_turns,ability_activation_cost)));
  }
  Constants::ATTACKER_TYPE_ATTRIBUTES = attacker_type_to_attributes;

  // All the defender types
  std::cin >> Constants::NO_OF_DEFENDER_TYPES;

  std::unordered_map<size_t, Attributes> defender_type_to_attributes;
  for (size_t i = 1; i <= Constants::NO_OF_DEFENDER_TYPES; i++) {
    unsigned hp, range, attack_power, speed, price, is_aerial;
    std::cin >> hp >> range >> attack_power >> speed >> price >> is_aerial;
    defender_type_to_attributes.insert(
        std::make_pair(i, Attributes(hp, range, attack_power, speed, price, is_aerial,0,0,0)));
  }
  Constants::DEFENDER_TYPE_ATTRIBUTES = defender_type_to_attributes;
}

Map get_initial_map() {
  auto map = Map::get(std::cin);
  Constants::MAP_NO_OF_ROWS = map.no_of_rows;
  Constants::MAP_NO_OF_COLS = map.no_of_rows;
  return map;
}

void output(size_t turn_no, Game &game) {
  game.logr().flush();

  if (!game.logr().view().empty()) {
    all_logs << "TURN " << turn_no << std::endl;
    all_logs << game.logr().view() << std::endl;
    all_logs << "ENDLOG" << std::endl;
  }

  // Game details logged
  const auto &spawn_positions = game.get_spawn_positions();
  const auto &player_set_targets = game.get_player_set_targets();
  const auto &ability_activations = game.get_ability_activations();

  std::cout << spawn_positions.size() << std::endl;
  for (const auto &entry : spawn_positions) {
    std::cout << entry.first << " " << entry.second.get_x() << " "
              << entry.second.get_y() << std::endl;
  }

  std::cout << player_set_targets.size() << std::endl;
  for (const auto &entry : player_set_targets) {
    std::cout << entry.first << " " << entry.second << std::endl;
  }

  std::cout << ability_activations.size() << std::endl;
  for (const auto &attacker_id : ability_activations) {
    std::cout << attacker_id << std::endl;
  }
}

void dump_logs(State &state, Game &game) {}

void dump_logs(PvPState& state, Game &game) {}

State next_state(size_t cur_turn_no) {
  size_t no_of_active_defenders;
  size_t no_of_active_attackers;

  std::cin >> no_of_active_attackers;
  std::vector<Attacker> attackers;
  for (size_t i = 0; i < no_of_active_attackers; i++) {
    size_t id, hp, x, y, type, is_ability_active;
    std::cin >> id >> x >> y >> type >> hp >> is_ability_active;
    attackers.push_back(Attacker(id, hp, type, Position(x, y), is_ability_active));
  }

  std::cin >> no_of_active_defenders;
  std::vector<Defender> defenders;
  for (size_t i = 0; i < no_of_active_defenders; i++) {
    size_t id, hp, x, y, type;
    std::cin >> id >> x >> y >> type >> hp;
    defenders.push_back(Defender(id, hp, type, Position(x, y)));
  }

  size_t coins_left;
  std::cin >> coins_left;

  return {move(attackers), move(defenders), coins_left, cur_turn_no + 1};
}

PvPState pvp_next_state(size_t cur_turn_no) {
  size_t no_of_active_attackers;
  size_t no_of_opponent_attackers;

  std::cin >> no_of_active_attackers;
  std::vector<Attacker> attackers;
  for (size_t i = 0; i < no_of_active_attackers; i++) {
    size_t id, hp, x, y, type, is_ability_active;
    std::cin >> id >> x >> y >> type >> hp >> is_ability_active;
    attackers.push_back(Attacker(id, hp, type, Position(x, y), is_ability_active));
  }

  std::cin >> no_of_opponent_attackers;
  std::vector<Attacker> opponent_attackers;
  for (size_t i = 0; i < no_of_opponent_attackers; i++) {
    size_t id, hp, x, y, type, is_ability_active;
    std::cin >> id >> x >> y >> type >> hp >> is_ability_active;
    opponent_attackers.push_back(Attacker(id, hp, type, Position(x, y), is_ability_active));
  }

  return {move(attackers), move(opponent_attackers), Constants::PVP_FIXED_COINS, cur_turn_no + 1};
}

enum class GameType {
  NORMAL,
  PVP
};

GameType string_to_game_type(std::string type) {
  if (type == std::string("normal")) {
    return GameType::NORMAL;
  } else {
    return GameType::PVP;
  }
}

int main(int argc, char** argv) {
  
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " [game-type]\n";
    exit(1);
  }

  auto gameType = string_to_game_type(std::string(argv[1]));

  switch (gameType) {
    case GameType::NORMAL: {
      std::cin >> Constants::NO_OF_TURNS >> Constants::MAX_NO_OF_COINS;
      init_constants();
      Map initial_map = get_initial_map();
      State state({}, initial_map.spawn_defenders(), Constants::MAX_NO_OF_COINS, 0);

      auto game = run(state);
      output(state.get_turn_no(), game);

      for (size_t i = 0; i < Constants::NO_OF_TURNS; i++) {
        state = next_state(state.get_turn_no());
        game = run(state);
        output(state.get_turn_no(), game);
      }
      
      break;
    }

    case GameType::PVP: {
      std::cin >> Constants::NO_OF_TURNS >> Constants::PVP_FIXED_COINS;
      init_constants();
      PvPState state({},{},Constants::PVP_FIXED_COINS, 0);

      auto game = run(state);
      output(state.get_turn_no(), game);

      for (size_t i = 0; i < Constants::NO_OF_TURNS; i++) {
        state = pvp_next_state(state.get_turn_no());
        game = run(state);
        output(state.get_turn_no(), game);
      }

      break;
    }
  }

  std::cerr << all_logs.str() << std::endl;
}
