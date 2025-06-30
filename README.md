# Treasure-Hunt-Game
C-based game with linked list for undo feature and struct for storing player’s and snake’s movement. The player has to capture the treasure denoted by the symbol, $ without being eaten by the snake, ~. There’s a dark mode feature in the game which limits the player’s visibility. The player has to capture the lattern, @ to increase his visibility. 

# Compilation and Execution
```
Compilation(no dark mode): make, Compilation(dark mode): make DARK=1
Execution: ./treasure map.txt
Clean(remove object and executable files): make clean
```
- Always clean up(make clean) before switching to a new mode
