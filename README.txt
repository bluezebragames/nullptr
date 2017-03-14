Joseph implemented the minimax algorithm with alpha-beta pruning in the AI. T.J.
implemented the heuristic function in the AI.

The AI features 5-ply lookahead and a heuristic function that accounts for
frontier squares and values on a square-by-square basis. We obtained the matrix
of weights from http://play-othello.appspot.com/files/Othello.pdf. 6-ply
lookahead would have been nice, but unfortunately, it takes too much memory to
implement with our Board class. The 5-ply lookahead will work in the tournament
because we believe that most AIs in the tournament will not have lookahead
deeper than this. The heuristic function will work in the tournament because it
takes into account frontier squares and incorporates a positional strategy into
the absolute strategy of maximizing the number of stones it has on the board
while minimizing the number of stones its opponent has on the board if fifty
moves or fewer have been made on the board. This approach emphasizes the
positioning of stones on the board as well as the current score of each of the
players in the first two-thirds of the game, which we believe is a good approach
because the current score of each of the players does not matter in the first
two-thirds of the game as much as it does in the last one-third of the game.
