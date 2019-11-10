package com.tema1.players;

import java.util.ArrayList;

import com.tema1.common.Constants;
import com.tema1.goods.Goods;
import com.tema1.goods.GoodsFactory;
import com.tema1.goods.GoodsType;

public class Basic extends Player {

    // legal basic strategy
    final void playLegal() {
        int[] cnt = new int[Constants.LEGAL_LAST_ID + 1];
        int maxCnt = 0;
        int maxProfit = 0;
        Goods declared;
        int declaredId = 0;
        // cnt va fi un vector de frecventa pentru bunuri legale
        for (Goods card : super.getCards()) {
            int id = card.getId();
            if (card.getType() == GoodsType.Legal) {
                cnt[id]++;
            }
        }

        // gasesc bunul care apare de cele mai multe ori
        // daca sunt doua bunuri diferite cu aceeasi frecventa, il adaug
        // pe cel mai valoros
        for (int i = 0; i <= Constants.LEGAL_LAST_ID; i++) {
            Goods good = GoodsFactory.getInstance().getGoodsById(i);
            if (cnt[i] > maxCnt) {
                maxCnt = cnt[i];
                declaredId = i;
                maxProfit = good.getProfit();
            } else if (cnt[i] == maxCnt && maxProfit <= good.getProfit()) {
                declaredId = i;
                maxProfit = good.getProfit();
            }
        }

        declared = GoodsFactory.getInstance().getGoodsById(declaredId);
        setDeclaredGood(declared);

        // verific sa nu adaug prea multe obiecte in bag
        if (maxCnt > Constants.BAG_SIZE) {
            maxCnt = Constants.BAG_SIZE;
        }

        // declar cartile si le bag in sac
        for (int i = 0; i < maxCnt; i++) {
            super.addToBag(declared);
            super.removeCard(declared);
        }
    }

    // illegal basic strategy
    final void playIllegal() {
        if (super.getCoins() >= Constants.ILLEGAL_PENALTY) {
            Goods bestCard = null;
            for (Goods card : super.getCards()) {
                if (bestCard == null || bestCard.getProfit() <= card.getProfit()) {
                    bestCard = card;
                }
            }

            if (bestCard != null && bestCard.getType() == GoodsType.Illegal) {
                super.addToBag(bestCard);
                super.removeCard(bestCard);
                Goods apple = GoodsFactory.getInstance().getGoodsById(0);
                super.setDeclaredGood(apple);
            }
        }
    }

    /**
     * Strategia Basic.
     */
    public void play() {
        this.draw();
        playLegal();
        if (super.getBag().isEmpty()) {
            playIllegal();
        }
    }

    /**
     * Seriful Basic.
     */
    public void playSheriff(final ArrayList<Player> players) {
        for (Player player : players) {
            if (!player.equals(this)
                    && this.getCoins() >= Constants.MIN_COINS) {
                check(player);
            }
        }
    }

    /**
     * Afisare pentru Basic.
     */
    public String displayScore() {
        return super.getId() + "  BASIC " + super.getScore();
    }
}
