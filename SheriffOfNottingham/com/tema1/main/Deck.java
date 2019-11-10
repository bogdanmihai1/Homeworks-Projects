package com.tema1.main;

import java.util.ArrayList;

public final class Deck {
    // Clasa Deck de tip Singleton ce reprezinta pachetul de carti
    private static Deck instance = null;
    private static ArrayList<Integer> cardOrder;

    private Deck() {
        // checkstyle
    }

    public static Deck getInstance() {
        if (instance == null) {
            instance = new Deck();
        }
        return instance;
    }

    public void init(final ArrayList<Integer> goods) {
        cardOrder = goods;
    }
    // adaug in pachet carti confiscate(cate una)
    public void addToDeck(final int goodId) {
        cardOrder.add(goodId);
    }
    // adaug in pachet toate cartile confiscate
    public void addToDeck(final ArrayList<Integer> goods) {
        cardOrder.addAll(goods);
    }

    public ArrayList<Integer> getDeck() {
        return cardOrder;
    }
    // trag carti din pachet
    public ArrayList<Integer> draw(final int size) {
        ArrayList<Integer> goods = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            Integer good = cardOrder.get(i);
            goods.add(good);
        }
        for (int i = 0; i < size; i++) {
            cardOrder.remove(0);
        }
        return goods;
    }
}
