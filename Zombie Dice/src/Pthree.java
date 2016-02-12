//
// Pthree
//
// This class provides a "main" method that acts as a driver program for
// a Zombie Dice game player.
// 
// Zombie Dice is a trademark of Steve Jackson Games.  For more information
// about this game, see "zombiedice.sjgames.com".
//
//


public class Pthree {

    public static void main(String[] args) {
	Game session = new Game();
	session.play();
	session = null;
    }

}
