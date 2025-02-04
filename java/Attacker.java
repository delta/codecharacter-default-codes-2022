public class Attacker extends Actor {
    public final int is_ability_active;
    public Attacker(int id, int hp, int type, Position pos, int is_ability_active) {
        super(id, hp, type, pos);
        this.is_ability_active = is_ability_active;
    }
}
