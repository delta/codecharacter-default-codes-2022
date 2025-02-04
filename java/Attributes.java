public class Attributes {
    public final int hp;
    public final int range;
    public final int attackPower;
    public final int speed;
    public final int price;
    public final int is_aerial;
    public final int weight;
    public final int num_ability_turns;
    public final int ability_activation_cost;
    
    public Attributes(int hp, int range, int attackPower, int speed, int price, int is_aerial, int weight, int num_ability_turns, int ability_activation_cost) {
        this.hp = hp;
        this.range = range;
        this.attackPower = attackPower;
        this.speed = speed;
        this.price = price;
        this.is_aerial = is_aerial;
        this.weight = weight;
        this.num_ability_turns = num_ability_turns;
        this.ability_activation_cost = ability_activation_cost;
    }
}
