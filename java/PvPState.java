import java.util.List;

public class PvPState {
    private final List<Attacker> _attackers;
    private final List<Attacker> _opponentAttackers;
    private final int _noOfCoinsLeft;
    private final int _turnNo;

    public PvPState(List<Attacker> attackers, List<Attacker> opponentAttackers,
            int noOfCoinsLeft, int turnNo) {
        _attackers = attackers;
        _opponentAttackers = opponentAttackers;
        _noOfCoinsLeft = noOfCoinsLeft;
        _turnNo = turnNo;
    }

    public List<Attacker> getAttackers() {
        return _attackers;
    }

    public List<Attacker> getOpponentAttackers() {
        return _opponentAttackers;
    }

    public int getTurnNo() {
        return _turnNo;
    }

    public int getCoinsLeft() {
        return _noOfCoinsLeft;
    }
}
