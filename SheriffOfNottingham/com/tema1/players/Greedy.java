package com.tema1.players;

import java.util.ArrayList;

import com.tema1.common.Constants;
import com.tema1.goods.Goods;
import com.tema1.main.Round;

public class Greedy extends Basic {

    Greedy() {
        // checkstyle
    }

    /**
     * Strategia Basic in runde impare.
     * Strategia Greedy in runde pare.
     */
    @Override
    public final void play() {
        super.play();
        if (Round.getInstance().evenParity()) {
            if (super.getBag().size() <= Constants.BAG_SIZE) {
                Goods declared = super.getDeclaredGood();
                super.playIllegal();
                super.setDeclaredGood(declared);
            }
        }
    }

    /**
     * Strategia Greedy de verificare.
     */
    @Override
    public final void playSheriff(final ArrayList<Player> players) {
        for (Player player : players) {
            if (!player.equals(this)) {
                if (player.hasBribe()) {
                    this.addCoins(player.getBribe());
                } else if (this.getCoins() >= Constants.MIN_COINS) {
                    check(player);
                }
            }
        }
    }

    /**
     * Afisare pentru Greedy.
     */
    @Override
    public String displayScore() {
        return super.getId() + "  GREEDY " + super.getScore();
    }
}
