package cardgame;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Player {
    private final String name;
    private final List<Card> hand = new ArrayList<>();
    private final Random random = new Random();

    public Player(String name) {
        this.name = name;
    }

    public synchronized void takeCard(Deck deck) throws InterruptedException {
        Card c = deck.drawCard();
        hand.add(c);
        System.out.println(name + " узима карту: " + c);
    }

    public synchronized void playRandomCard(Deck deck) throws InterruptedException {
        if (hand.isEmpty()) {
            System.out.println(name + " нема карти у руци да одигра.");
            return;
        }
        int idx = random.nextInt(hand.size());
        Card c = hand.remove(idx);
        deck.addCard(c);
        System.out.println(name + " враћа карту у шпил: " + c);
    }

    public synchronized int handValueSum() {
        return hand.stream().mapToInt(Card::getValue).sum();
    }

    public synchronized String describe() {
        StringBuilder sb = new StringBuilder();
        sb.append("Играч ").append(name).append(" има ").append(hand.size()).append(" карти у руци:\n");
        for (Card c : hand) {
            sb.append("  ").append(c.toString()).append("\n");
        }
        return sb.toString();
    }

    public String getName() {
        return name;
    }
}
