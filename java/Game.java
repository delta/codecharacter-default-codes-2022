import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Game {
    private final Map<Integer, Integer> _playerSetTargets;
    private final List<SpawnDetail> _spawnPositions;
    private final Set<Position> _alreadySpawnedPositions;
    private final StringBuilder _logr;
    private final List<Integer> _ability_activations;
    public static Set<Integer> already_activated_attacker_ids;

    public Game() {
        _playerSetTargets = new HashMap<>();
        _spawnPositions = new ArrayList<>();
        _alreadySpawnedPositions = new HashSet<>();
        _logr = new StringBuilder();
        _ability_activations = new ArrayList<>();
    }

    public void spawnAttacker(int id, Position pos) {
        _spawnPositions.add(new SpawnDetail(id, pos));
        _alreadySpawnedPositions.add(pos);
    }

    public void activateAbility(int attacker_id) {
        _ability_activations.add(attacker_id);
        already_activated_attacker_ids.add(attacker_id);
    }

    public List<SpawnDetail> getSpawnPositions() {
        return _spawnPositions;
    }

    public Map<Integer, Integer> getPlayerSetTargets() {
        return _playerSetTargets;
    }

    public List<Integer> getAbilityActivations() {
        return _ability_activations;
    }

    public boolean alreadySpawnedAtPosition(Position pos) {
        return _alreadySpawnedPositions.contains(pos);
    }

    public void setTarget(int attackerId, int defenderId) {
        _playerSetTargets.put(attackerId, defenderId);
    }

    public void setTarget(Attacker attacker, Defender defender) {
        setTarget(attacker.getId(), defender.getId());
    }

    public void setTarget(Attacker attacker, Attacker opponent_attacker) {
        setTarget(attacker.getId(), opponent_attacker.getId());
    }

    public void log(String s) {
        _logr.append(s + "\n");
    }

    public String getLog() {
        return _logr.toString();
    }

    public void clearLog() {
        _logr.setLength(0);
    }
}
