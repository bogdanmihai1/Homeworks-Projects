package com.tema1.main;

import java.util.ArrayList;

import com.tema1.players.Player;
import com.tema1.players.PlayerFactory;

public final class Main {
    private Main() {
        // just to trick checkstyle
    }

    public static void main(final String[] args) {
        GameInputLoader gameInputLoader = new GameInputLoader(args[0], args[1]);
        GameInput gameInput = gameInputLoader.load();
        //TODO implement homework logic
        ArrayList<Integer> deck = (ArrayList<Integer>) gameInput.getAssetIds();
        Deck.getInstance().init(deck);
        ArrayList<Player> players = new ArrayList<>();
        // creez jucatorii si ii adaug intr-un array
        for (String player : gameInput.getPlayerNames()) {
            Player newPlayer = PlayerFactory.getInstance().getPlayer(player);
            players.add(newPlayer);
        }
        // simulez fiecare runda
        for (int i = 0; i < gameInput.getRounds(); i++) {
            Round.getInstance().nextRound(players);
        }

        int index = 0;
        // adaug bonusurile ilegale
        for (Player player : players) {
            player.addIllegalBonuses();
            player.setId(index);
            index++;
        }
        // adaug king/queen si calculez scorul final pentru fiecare jucator
        ScoreCalculator.getInstance().kingQueenBonus(players);
        ScoreCalculator.getInstance().finalScore(players);
        // sortez jucatorii in functie de scor
        players.sort((final Player a, final Player b) ->
        b.getScore() - a.getScore());
        // afisare
        for (Player player : players) {
            System.out.println(player.displayScore());
        }
    }
}
