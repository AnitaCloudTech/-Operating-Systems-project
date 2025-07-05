package cardgame;

public class Game {
    public static void main(String[] args) throws InterruptedException {
        Deck deck = new Deck();
        deck.fillStandardDeck();

        Player player1 = new Player("Петар");
        Player player2 = new Player("Милош");

        for (int i = 0; i < 3; i++) {
            player1.takeCard(deck);
            player2.takeCard(deck);
        }

        System.out.println("--- Почетно стање ---");
        System.out.println(player1.describe());
        System.out.println(player2.describe());
        System.out.println(deck.describe());

        for (int round = 1; round <= 3; round++) {
            System.out.println("\nТура " + round + ":");
            player1.takeCard(deck);
            player2.takeCard(deck);
        }

        for (int round = 1; round <= 3; round++) {
            System.out.println("\nВраћање карти у шпил - Тура " + round + ":");
            player1.playRandomCard(deck);
            player2.playRandomCard(deck);
        }

        System.out.println("\n--- Коначни статус ---");
        System.out.println(player1.describe());
        System.out.println(player2.describe());
        System.out.println(deck.describe());

        int sum1 = player1.handValueSum();
        int sum2 = player2.handValueSum();

        if (sum1 < sum2) {
            System.out.println("Победник је: " + player1.getName());
        } else if (sum2 < sum1) {
            System.out.println("Победник је: " + player2.getName());
        } else {
            System.out.println("Нерешено је.");
        }
    }
}
