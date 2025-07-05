package cardgame;

public class Card {
    private static int nextId = 1;

    private final int id;
    private final int value; // 1-13
    private final Suit suit;

    public enum Suit {
        HEARTS("Срце"), DIAMONDS("Каро"), CLUBS("Треф"), SPADES("Пик");
        private final String name;
        Suit(String name) { this.name = name; }
        @Override
        public String toString() { return name; }
    }

    public Card(int value, Suit suit) {
        this.id = nextId++;
        this.value = value;
        this.suit = suit;
    }

    public int getId() { return id; }
    public int getValue() { return value; }
    public Suit getSuit() { return suit; }

    public Card copy() {
        return new Card(this.value, this.suit);
    }

    @Override
    public String toString() {
        String valStr;
        switch (value) {
            case 1: valStr = "As"; break;
            case 11: valStr = "Žandar"; break;
            case 12: valStr = "Dama"; break;
            case 13: valStr = "Kralj"; break;
            default: valStr = String.valueOf(value);
        }
        return valStr + " " + suit;
    }
}
