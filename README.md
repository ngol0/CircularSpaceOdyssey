# Circular Space Odyssey

# Short description
Shoot all enemies to collect enough resources and go to next level. Be careful - the enemy can predict where you are when you move and shoot there. 

Try to get the health power-up to prevent being killed when your health are low!

There are 3 levels. First one introduces 2 basic enemy types. Second and third level will introduce a new one for each. Pay attention to each enemy's behaviors so that you can move and shoot at the right position and time!
<img src="https://github.com/ngol0/CircularSpaceOdyssey/blob/main/gif2.gif" width="900" title="build">

# Technical features
## Entity-Component architecture
- Component: the parent Component class is an interface inherited by all the specific components. Each specific component contains data and logic for that component and has its own Update & Render functions.

- Game Object: a container for the components. It loops through all the components it has and updates/renders them.

- Game Object Manager: a container for the game objects. It loops through all the game objects in the game and updates/renders them if they are active or skip them if they are not.


## Design patterns for game systems & objects
- State: used to display a certain UI window when game state is changed.

- Factory: the GameObjectFactory namespace acts as a “factory” to create all the specific game objects in the game by adding suitable components to a game object.

- Object pooling: creates a number of objects (i.e: enemy, bullet, power-up, particle) up front in a single contiguous allocation and reuse them when needed.

- Observer: the template class Event is used to create an event system using the observer pattern. It uses function pointers to store the observers and their corresponding member functions. It allows objects to register and unregister as observers to be notified when the event occurs.


## Data-driven method to control enemy spawning behaviors with commands
- Reading and parsing commands from text files into a list of commands.

- Spawning enemies based on command types. Level Manager will go through each command in the list and check for the type of command in order to execute accordingly.

Level Manager is designed this way so that designers can have more control on how each level is laid out. It gives designers the flexibility to introduce new enemies and increase or decrease the level difficulties.


## Enemy AI that predicts player's movement
- Movement: enemy can move to a waypoint and stand there or follow the player or move randomly between different waypoints.

- Shooting: enemy can predict the player's next position when the player is moving. When the player is not moving, enemy simply shoot towards the player.


# Controls:
- Move: A to move left and D to move right.

- Shoot: Left click

- Pause: P

- Restart: R

## Running the game
Open **GameTest.sln** in Visual Studio 2022 and hit **F5**.

