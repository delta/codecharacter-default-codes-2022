import java.util.ArrayList;
import java.util.List;

// This initial code is well commented and serves as a small tutorial for game
// APIs, for more information you can refer to the documentation

// This is the function player has to fill
// You can define any new functions here that you want
public class RunPvP {

    // Lets say I want to spawn an attacker of each of the type in one turn
    // and I want to use the Helpers.getAllValidSpawnPositions list as well. In
    // order to keep track of the last index in the list that we spawned at, we can
    // use a private variable. We'll initialize it in the constructor for this
    // class. This class is only instantiated once so it's safe to use a private
    // variable.
    private int lastSpawned;

    public RunPvP() {
        this.lastSpawned = 0;
    }

    public Game run(PvPState state) {

        // Always start by instantiating a Game class object
        Game game = new Game();

        int remainingCoins = state.getCoinsLeft();
        game.log("TURN " + state.getTurnNo() + " LOGS:");

        // Get all the attackers and opponent in the game and store it
        List<Attacker> attackers = state.getAttackers();
        List<Attacker> opponentAttackers = state.getOpponentAttackers();

        // The function get_all_valid_spawn_positions() is a helper which will give us
        // the list of valid spawn positions in map.
        // If the position we're spawning is not one of these, the player will be
        // penalized by deducting the spawn cost but not spawning the attacker

        // The Helpers.getAllValidSpawnPositions() function
        // returns a Set<Position>, if we want to index on it,
        // we must convert to an indexable collection
        List<Position> allValidSpawnPositons = new ArrayList<Position>(Helpers.getAllValidSpawnPositions());

        for (int typeId = 1; typeId <= Constants.NO_OF_ATTACKER_TYPES; typeId++) {
            // Spawn the attacker of typeId at position
            // allValidSpawnPositions[last_spawned]

            // There are two cases when you might be panalized
            // - Spawning at invalid position
            // - Spawning at position where you have already spawned one attacker
            // in the same turn
            //
            // We have provided helpers to check just that

            // game class will keep track of all your spawned positions for you and
            // provides a helper method called already_spawned_at_position(Position)
            // to check if you already spawned in the position

            // Mostly a good practice to check with these two helpers before spawning,
            // to save up on accidental penalties
            //

            if (Helpers.isValidSpawnPosition(allValidSpawnPositons.get(lastSpawned)) &&
                    !game.alreadySpawnedAtPosition(
                            allValidSpawnPositons.get(lastSpawned))) {

                // If lets say you had run out of coins left, the game will just ignore
                // the spawn
                game.spawnAttacker(typeId, allValidSpawnPositons.get(lastSpawned));

                // This has the starting attributes for the attacker we are about to
                // spawn
                // For full information about the Attributes class refer the
                // documentation
                // This information can be used for strategizing
                Attributes attackersAttributes = Constants.ATTACKER_TYPE_ATTRIBUTES.get(typeId);

                Position pos = allValidSpawnPositons.get(lastSpawned);
                game.log(String.format("To be spawned at Position(%d,%d)\n", pos.getX(), pos.getY()));

                lastSpawned += 1;
                lastSpawned %= allValidSpawnPositons.size();
            }

        }

        // Now lets say you always want to set the target for the attackers[0] to
        // defenders[0]
        // To do that you do
        if (!attackers.isEmpty() && !opponentAttackers.isEmpty()) {
            // check if they are empty beforehand to be safe from unexpected errors
            game.setTarget(attackers.get(0).getId(), opponentAttackers.get(0).getId());
            //lets say i want to activate the ability of the first attacker
            //check if ability wasnt activated before to avoid getting penalized
            if (!Game.already_activated_attacker_ids.contains(attackers.get(0).getId())) {
                game.activateAbility(attackers.get(0).getId());
            }
        }

        // Lets log all the spawned positions for this turn
        for (var entry : game.getSpawnPositions()) {
            game.log(String.format("Type %d at Position(%d, %d)",
                    entry.getTypeId(), entry.getPos().getX(),
                    entry.getPos().getY()));
        }

        // always return the game object
        return game;
    }
}
