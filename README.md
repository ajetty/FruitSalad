# Fruit Salad: Banana-man's Rampage 

## About
This is a game demo built with Unreal Engine 4.26 with Blueprints and C++. 

There is one level of a town with destructible buildings and fleeing NPCs. The player drives a bulldozer and destroys both the buildings and NPCs with it while a timer runs down to zero. All of the orange outlined buildings must be destroyed before the timer reaches zero to win. The game ends when either of those conditions happen.  

If you would like to read the game design document in pdf form then please click [here](https://ajetty.github.io/ReadMe_Images/Fruit%20Salad%20Game%20Design%20Document.pdf). 

## Goals

Here are my goals that I wanted to achieve when creating this demo:

- To create a vehicle that could be moved by the player and had physics. 
- Have the vehicle the ability to right itself up when toppled. 
- Have NPCs that reacted to their enviroment by avoiding obstacles when traveling.
- Have NPCs flee from the player when approached.  
- Have destructable buildings that showed their health through a texture erosion process. 
- Have certain buildings show the player their importance visually.
- When a building has zero health then destruct into smaller components.
- When destroying a building or an NPC, add time to the game play timer.
- Have a game over either when all of the game play time has expired or when all of the targeted buildings have been destroyed.   

## Bulldozer

<a href="https://ajetty.github.io/ReadMe_Images/Bulldozer.png">
<img src="https://ajetty.github.io/ReadMe_Images/Bulldozer.png" alt="Bulldozer Asset Image" width="50%" />
</a>
<br /> 

[Github Folder Link for Bulldozer](https://github.com/ajetty/FruitSalad/tree/main/Source/FruitSalad/Bulldozer)

The model was created in Blender and then given a skeletal mesh with a physics asset in Unreal. A C++ class was created for this actor with it inheriting from AWheeledVehicle. This allows for the use of UWheeledVehicleMovementComponent4W that allows to bind actions to the vehicle that relate to a vehicle body. 

The Bulldozer has two data assets called BulldozerBackWheel and BulldozerFrontWheel. Each of these assets have Tire, Wheel, Suspension, and Brake information that tells the Bulldozer how to run its wheels and perform in the enviroment. 

You move the Bulldozer with the WASD keys and break using the spacebar. 

A function within main PawnBulldozer.cpp, UpdateInAirControl takes a line trace and checks to see if the Bulldozer is in an upright position by getting the dot product of its up vector with the world's. If not upright then the function will try to calculate a roll by a new movement vector determined by a constant called air movement force pitch and the player's input using the 'a' and 'd' keys. This updates the Bulldozer's rotation.    

## Buildings

<a href="https://ajetty.github.io/ReadMe_Images/Buildings2.png">
<img src="https://ajetty.github.io/ReadMe_Images/Buildings2.png" alt="Building Asset Image" width="70%" />
</a>
<br />

<a href="https://ajetty.github.io/ReadMe_Images/DestroyBuilding.gif">
<img src="https://ajetty.github.io/ReadMe_Images/DestroyBuilding.gif" alt="Fruit Data Asset Image" width="320px" >
</a>
<br />
 
[Github Link for Buildings](https://github.com/ajetty/FruitSalad/tree/main/Source/FruitSalad/Building)


### Building Base

<a href="https://ajetty.github.io/ReadMe_Images/BuildingUML.png">
<img src="https://ajetty.github.io/ReadMe_Images/BuildingUML.png" alt="Buildings UML Diagram" width="70%" >
</a>
<br />

### Building Targets

## Fruit

[Github Folder Link for Fruit](https://github.com/ajetty/FruitSalad/tree/main/Source/FruitSalad/Fruit)

[Github Folder Link for Fruit AI](https://github.com/ajetty/FruitSalad/tree/main/Source/FruitSalad/AI)

### Behavior Tree

<a href="https://ajetty.github.io/ReadMe_Images/FruitBehaviorTree.png">
<img src="https://ajetty.github.io/ReadMe_Images/FruitBehaviorTree.png" alt="Fruit Behavior Tree Image" width="70%" >
</a>
<br />

### Data Assets

<a href="https://ajetty.github.io/ReadMe_Images/FruitAsset.png">
<img src="https://ajetty.github.io/ReadMe_Images/FruitAsset.png" alt="Fruit Data Asset Image" width="30%" >
</a>
<br />

## HUD

[Github Folder Link for HUD](https://github.com/ajetty/FruitSalad/tree/main/Source/FruitSalad/HUD)

### Title Menu
<a href="https://ajetty.github.io/ReadMe_Images/TitleScreen.gif">
<img src="https://ajetty.github.io/ReadMe_Images/TitleScreen.gif" alt="Fruit Data Asset Image" width="320px" >
</a>
<br />

### Pause Menu

<a href="https://ajetty.github.io/ReadMe_Images/PauseMenu.png">
<img src="https://ajetty.github.io/ReadMe_Images/PauseMenu.png" alt="Fruit Data Asset Image" width="50%" >
</a>
<br />

### Win Screen

### Lose Screen


