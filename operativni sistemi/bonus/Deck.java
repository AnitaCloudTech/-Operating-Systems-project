package cardgame;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Deck {
    private final int MAX_SIZE = 52;
    private final List<Card> cards = new ArrayList<>();

    public Deck() {
        // Kreira prazan špil
    }

    public void fillStandardDeck() {
        cards.clear();
        for (Card.Suit suit : Card.Suit.values()) {
            for (int val = 1; val <= 13; val++) {
                cards.add(new Card(val, suit));
            }
        }
        shuffle();
    }

    public synchronized void shuffle() {
        Collections.shuffle(cards);
    }

    public synchronized Card drawCard() throws InterruptedException {
        while (cards.isEmpty()) {
            wait();
        }
        Card c = cards.remove(cards.size() - 1);
        notifyAll();
        return c;
    }

    public synchronized void addCard(Card card) throws InterruptedException {
        while (cards.size() >= MAX_SIZE) {
            wait();
        }
        cards.add(card);
        notifyAll();
    }

    public synchronized String describe() {
        StringBuilder sb = new StringBuilder();
        sb.append("Шпил карата (").append(cards.size()).append(" карата):\n");
        for (Card c : cards) {
            sb.append(c.toString()).append("\n");
        }
        return sb.toString();
    }

    public synchronized int size() {
        return cards.size();
    }
}
