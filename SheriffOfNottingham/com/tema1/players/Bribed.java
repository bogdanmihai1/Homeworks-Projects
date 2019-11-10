package com.tema1.players;

import java.util.ArrayList;

import com.tema1.common.Constants;
import com.tema1.goods.Goods;
import com.tema1.goods.GoodsFactory;
import com.tema1.goods.GoodsType;

public class Bribed extends Basic {
    private Player left = null;
    private Player right = null;

    // metoda ce gaseste vecinii jucatorului actual
    private void findNeighbours(final ArrayList<Player> players) {
        int playerPos = players.indexOf(this);
        int leftPos = playerPos - 1;
        int rightPos = playerPos + 1;

        if (playerPos == 0) {
            leftPos = players.size() - 1;
        }

        if (playerPos == players.size() - 1) {
            rightPos = 0;
        }

        left = players.get(leftPos);
        right = players.get(rightPos);
    }

    @Override
    public final void play() {
        this.draw();
        int illegalCnt = 0;
        int addedIllegal = 0;

        // gasesc cate carti ilegale am
        for (Goods card : super.getCards()) {
            if (card.getType() == GoodsType.Illegal) {
                illegalCnt++;
            }
        }

        // daca nu am carti ilegale sau bani suficienti, joc basic
        if (illegalCnt == 0 || super.getCoins() < Constants.MIN_BRIBE) {
            super.setBribe(0);
            super.playLegal();
            if (super.getBag().isEmpty()) {
                super.playIllegal();
            }
        } else {
            int bagSize;
            // worstcasescenario reprezinta cu cati bani am ramane daca
            // am fi verificati de serif
            int worstCaseScenario = super.getCoins();
            // verific cati bani am de bribe
            if (super.getCoins() < Constants.MAX_BRIBE) {
                bagSize = Constants.MIN_BRIBE_SIZE;
            } else {
                bagSize = Constants.BAG_SIZE;
            }

            // separ bunurile legale de cele ilegale
            ArrayList<Goods> illegalGoods = new ArrayList<>();
            ArrayList<Goods> legalGoods = new ArrayList<>();
            for (Goods card : super.getCards()) {
                if (card.getType() == GoodsType.Illegal) {
                    illegalGoods.add(card);
                } else {
                    legalGoods.add(card);
                }
            }

            // sortez bunurile ilegale dupa profit(toate au valori diferite)
            illegalGoods.sort((final Goods a, final Goods b) ->
                    b.getProfit() - a.getProfit());
            // sortez bunurile legale dupa profit si dupa id
            legalGoods.sort((final Goods a, final Goods b) ->
                    (b.getProfit() - a.getProfit() != 0)
                    ? b.getProfit() - a.getProfit() : b.getId() - a.getId());

            if (illegalCnt > bagSize) {
                illegalCnt = bagSize;
            }

            for (int i = 0; i < illegalCnt; i++) {
                Goods card = illegalGoods.get(i);
                // verific daca pot baga cartea in sac
                if (worstCaseScenario - card.getPenalty() > 0) {
                    worstCaseScenario -= card.getPenalty();
                    addedIllegal++;
                    super.getBag().add(card);
                    super.getCards().remove(card);
                }
            }

            for (Goods good : legalGoods) {
            // adaug bunurile legale in sac in functie de cati bani am
            // si de cate locuri libere mai sunt in sac
                if (worstCaseScenario - good.getPenalty() > 0
                        && super.getBag().size() < Constants.BAG_SIZE) {
                    super.getBag().add(good);
                    super.getCards().remove(good);
                    worstCaseScenario -= good.getPenalty();
                }
            }

            Goods apple = GoodsFactory.getInstance().getGoodsById(0);
            super.setDeclaredGood(apple);
            int bribe;
            if (addedIllegal > Constants.MIN_BRIBE_SIZE) {
                bribe = Constants.MAX_BRIBE;
            } else {
                bribe = Constants.MIN_BRIBE;
            }

            super.setBribe(bribe);
        }
    }

    @Override
    public final void playSheriff(final ArrayList<Player> players) {
    // verific vecinii
        findNeighbours(players);
        if (this.getCoins() >= Constants.MIN_COINS) {
            check(left);
        }
        if (this.getCoins() >= Constants.MIN_COINS) {
            if (!right.equals(left)) {
                check(right);
            }
        }
    }

    /**
     * Afisare pentru Bribed.
     */
    @Override
    public String displayScore() {
        return super.getId() + "  BRIBED " + super.getScore();
    }
}
