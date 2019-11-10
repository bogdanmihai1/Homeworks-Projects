package com.tema1.players;

import java.util.ArrayList;
import java.util.List;

import com.tema1.common.Constants;
import com.tema1.goods.Goods;
import com.tema1.goods.GoodsFactory;
import com.tema1.goods.GoodsType;
import com.tema1.main.Deck;

public abstract class Player {

    private ArrayList<Goods> cards;
    private ArrayList<Goods> bag;
    private int coins;
    private int bribe;
    private int kQbonus;
    private Goods declaredGood;
    private ArrayList<Integer> soldGoods;
    private int score;
    private int id;

    public Player() {
        coins = Constants.START_COINS;
        kQbonus = 0;
        bribe = 0;
        declaredGood = null;
        cards = new ArrayList<>();
        bag = new ArrayList<>();
        soldGoods = new ArrayList<Integer>();
        for (int i = 0; i <= Constants.MAX_ID; i++) {
            soldGoods.add(0);
        }
    }

    // playerul curent plateste bribe serifului
    final int getBribe() {
        this.coins -= this.bribe;
        return this.bribe;
    }

    // setez bribe
    final void setBribe(final int bribe) {
        this.bribe = bribe;
    }

    // verific daca playerul are bribe
    final boolean hasBribe() {
        if (bribe > 0) {
            return true;
        }
        return false;
    }

    public final void setScore(final int score) {
        this.score = score;
    }

    public final int getScore() {
        return score;
    }

    public final ArrayList<Integer> getSoldGoods() {
        return soldGoods;
    }

    // pierd banii dupa verificarea serifului
    final void takeCoins(final int penalty) {
        this.coins -= penalty;
    }

    // adaug banii dupa verificarea serifului
    final void addCoins(final int reward) {
        this.coins += reward;
    }

    public final int getCoins() {
        return this.coins;
    }

    final ArrayList<Goods> getCards() {
        return this.cards;
    }

    final void removeCard(final Goods card) {
        cards.remove(card);
    }

    final ArrayList<Goods> getBag() {
        return bag;
    }

    final void addToBag(final Goods card) {
        bag.add(card);
    }

    final Goods getDeclaredGood() {
        return declaredGood;
    }

    final void setDeclaredGood(final Goods good) {
        this.declaredGood = good;
    }

    public final void discard() {
        this.cards.clear();
    }

    public final void addBonus(final int bonus) {
        kQbonus += bonus;
    }

    public final int getBonus() {
        return kQbonus;
    }

    // metoda care calculeaza banii datorati serifului
    // sau banii pe care seriful trebuie sa ii plateasca
    private int paySheriff() {
        int sum = 0;
        boolean liar = false;
        ArrayList<Goods> removedGoods = new ArrayList<>();
        ArrayList<Integer> backToDeck = new ArrayList<>();

        for (Goods good : bag) {
            if (good.getType() == GoodsType.Illegal
                    || good.getId() != declaredGood.getId()) {
                liar = true;
                sum += good.getPenalty();
                removedGoods.add(good);
                backToDeck.add(good.getId());
                Deck.getInstance().addToDeck(backToDeck);
            }
        }

        if (!liar) {
            for (Goods good : bag) {
                sum -= good.getPenalty();
            }
        } else {
            for (Goods good : removedGoods) {
                bag.remove(good);
            }
        }
        return sum;
    }

    // metoda care adauga bunurile trecute de inspectie pe piata
    public final void updateMarket() {
        int goodId;
        for (Goods good : bag) {
            goodId = good.getId();
            soldGoods.set(goodId, soldGoods.get(goodId) + 1);
        }
        bag.clear();
    }

    // verificarea serifului
    final void check(final Player player) {
        int sum = player.paySheriff();
        coins += sum;
        player.takeCoins(sum);
    }

    // trage carti din pachet
    public final void draw() {
        List<Integer> cardsDrawn = Deck.getInstance().draw(Constants.HAND_SIZE);
        for (int i : cardsDrawn) {
            Goods good = GoodsFactory.getInstance().getGoodsById(i);
            cards.add(good);
        }
    }

    // adaug bunurile legale primite din bonusul celor ilegale
    public final void addIllegalBonuses() {
        int illegalId, bonusId, cnt, prevCnt;
        // Silk
        illegalId = Constants.ILLEGAL_STARTING_ID;
        cnt = soldGoods.get(illegalId) * Constants.TRIPLE_MODIFIER;
        bonusId = Constants.CHEESE_ID;
        prevCnt = soldGoods.get(bonusId);

        soldGoods.set(bonusId, prevCnt + cnt);

        // Pepper
        illegalId++;
        cnt = soldGoods.get(illegalId) * Constants.DOUBLE_MODIFIER;
        bonusId = Constants.CHICKEN_ID;
        prevCnt = soldGoods.get(bonusId);

        soldGoods.set(bonusId, prevCnt + cnt);

        // Barrel
        illegalId++;
        cnt = soldGoods.get(illegalId) * Constants.DOUBLE_MODIFIER;
        bonusId = Constants.BREAD_ID;
        prevCnt = soldGoods.get(bonusId);

        soldGoods.set(bonusId, prevCnt + cnt);

        // Beer
        illegalId++;
        cnt = soldGoods.get(illegalId) * Constants.QUADRA_MODIFIER;
        bonusId = Constants.WINE_ID;
        prevCnt = soldGoods.get(bonusId);

        soldGoods.set(bonusId, prevCnt + cnt);

        // Seafood
        illegalId++;

        // Tomato bonus
        cnt = soldGoods.get(illegalId) * Constants.DOUBLE_MODIFIER;
        bonusId = Constants.TOMATO_ID;
        prevCnt = soldGoods.get(bonusId);

        soldGoods.set(bonusId, prevCnt + cnt);

        // Potato bonus
        cnt = soldGoods.get(illegalId) * Constants.TRIPLE_MODIFIER;
        bonusId = Constants.POTATO_ID;
        prevCnt = soldGoods.get(bonusId);

        soldGoods.set(bonusId, prevCnt + cnt);

        // Chicken bonus
        cnt = soldGoods.get(illegalId);
        bonusId = Constants.CHICKEN_ID;
        prevCnt = soldGoods.get(bonusId);

        soldGoods.set(bonusId, prevCnt + cnt);
    }

    // strategia de comerciant fiecarui jucator
    public abstract void play();
    // strategia de serif a fiecarui jucator
    public abstract void playSheriff(ArrayList<Player> players);
    // metoda care afiseaza scorul
    public abstract String displayScore();

    public final int getId() {
        return id;
    }

    public final void setId(final int newId) {
        this.id = newId;
    }
}
