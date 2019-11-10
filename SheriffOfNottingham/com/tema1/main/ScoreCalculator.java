package com.tema1.main;

import java.util.ArrayList;

import com.tema1.common.Constants;
import com.tema1.goods.Goods;
import com.tema1.goods.GoodsFactory;
import com.tema1.goods.LegalGoods;
import com.tema1.players.Player;

public final class ScoreCalculator {
    // clasa de tip Singleton ce calculeaza scorul jucatorilor
    private static ScoreCalculator instance = null;
    private ScoreCalculator() {
        // checkstyle
    }

    public static ScoreCalculator getInstance() {
        if (instance == null) {
            instance = new ScoreCalculator();
        }
        return instance;
    }

    public void kingQueenBonus(final ArrayList<Player> players) {
        int kingId, kingCnt, kingBonus, queenId, queenCnt, queenBonus;
        // doar bunurile legale au k/q bonus
        for (int i = 0; i <= Constants.LEGAL_LAST_ID; i++) {
            kingId = 0;
            kingCnt = 0;
            queenId = 0;
            queenCnt = 0;
            LegalGoods good = (LegalGoods) GoodsFactory.getInstance().getGoodsById(i);
            kingBonus = good.getKingBonus();
            queenBonus = good.getQueenBonus();

            for (int j = 0; j < players.size(); j++) {
                int cnt = players.get(j).getSoldGoods().get(i);
                if (cnt > kingCnt) {
                    queenCnt = kingCnt;
                    kingCnt = cnt;
                    queenId = kingId;
                    kingId = j;
                } else if (cnt > queenCnt) {
                    queenCnt = cnt;
                    queenId = j;
                }
            }
            // verific daca jucatorii king si queen au bunul respectiv
            if (kingCnt > 0) {
                players.get(kingId).addBonus(kingBonus);
            }
            if (queenCnt > 0) {
                players.get(queenId).addBonus(queenBonus);
            }
        }
    }

    public void finalScore(final ArrayList<Player> players) {
        // scorul final va fi suma dintre bonus, banii ramasi si valoarea bunurilor
        for (Player player : players) {
            int currScore = 0;
            currScore += player.getBonus();
            currScore += player.getCoins();

            for (int i = 0; i <= Constants.LEGAL_LAST_ID; i++) {
                Goods good = GoodsFactory.getInstance().getGoodsById(i);
                int cnt = player.getSoldGoods().get(i);
                currScore += good.getProfit() * cnt;
            }

            for (int i = Constants.ILLEGAL_STARTING_ID; i <= Constants.MAX_ID; i++) {
                Goods good = GoodsFactory.getInstance().getGoodsById(i);
                int cnt = player.getSoldGoods().get(i);
                currScore += good.getProfit() * cnt;
            }

            player.setScore(currScore);
        }
    }
}
