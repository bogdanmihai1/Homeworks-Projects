package com.tema1.main;

import java.util.ArrayList;

import com.tema1.players.Player;

public final class Round {
    // clasa Round de tip Singleton simuleaza fiecare runda
    private static Round instance = null;
    private boolean evenRound;

    private Round() {
        evenRound = false;
    }

    public static Round getInstance() {
        if (instance == null) {
            instance = new Round();
        }
        return instance;
    }

    public void nextRound(final ArrayList<Player> players) {
        for (int i = 0; i < players.size(); i++) {  // subrunde
            // i is the sheriff player
            for (int j = 0; j < players.size(); j++) {
                if (i != j) {
                    // players use their strategies and declare their goods
                    players.get(j).play();
                    // discard the unused goods
                    players.get(j).discard();
                }
            }
            // sheriff checks the other players
            players.get(i).playSheriff(players);
            // add the goods that passed inspection to market
            for (int j = 0; j < players.size(); j++) {
                if (i != j) {
                    players.get(j).updateMarket();
                }
            }
        }
        evenRound = !evenRound;
    }
    // verific paritatea rundei
    public boolean evenParity() {
        return evenRound;
    }
}
