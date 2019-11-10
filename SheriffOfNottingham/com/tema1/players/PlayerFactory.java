package com.tema1.players;

public final class PlayerFactory {
    // Factory ce genereaza jucatorii
    private static PlayerFactory instance = null;

    private PlayerFactory() {
        // checkstyle
    }

    public static PlayerFactory getInstance() {
        if (instance == null) {
            instance = new PlayerFactory();
        }
        return instance;
    }

    public Player getPlayer(final String name) {

        if (name.equals("basic")) {
            return new Basic();
        } else if (name.equals("greedy")) {
            return new Greedy();
        } else if (name.equals("bribed")) {
            return new Bribed();
        }

        return null;
    }
}
