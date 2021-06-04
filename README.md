# Fruit Salad: Banana-man's Rampage 

## About
This is a game demo built with Unreal Engine 4.26 with Blueprints and C++. 

There is one level of a town with destructible buildings and fleeing NPCs. The player drives a bulldozer and destroys both the buildings and NPCs with it while a timer runs down to zero. All of the orange outlined buildings must be destroyed before the timer reaches zero to win. The game ends when either of those conditions happen.  

[Game Design Document PDF](https://ajetty.github.io/ReadMe_Images/Fruit%20Salad%20Game%20Design%20Document.pdf) 

[Gameplay Demo Video](https://youtu.be/sE0fJ1PAJq4)

## Goals

Here are my goals that I wanted to achieve when creating this demo:

- To create a vehicle that could be moved by the player and had physics. 
- Have the vehicle the ability to right itself up when toppled. 
- Have NPCs that reacted to their environment by avoiding obstacles when traveling.
- Have NPCs flee from the player when approached.  
- Have destructible buildings that showed their health through a texture erosion process. 
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

The Bulldozer has two data assets called BulldozerBackWheel and BulldozerFrontWheel. Each of these assets have Tire, Wheel, Suspension, and Brake information that tells the Bulldozer how to run its wheels and perform in the environment. 

You move the Bulldozer with the WASD keys and break using the space bar. 

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

Buildings have a Destructible Mesh that allows it to break when something applies force on it. The Buildings are given a max health value and when hit by the Bulldozer, decrements in health. A Dynamic Material Instance is a property of the C++ class and when the Building mesh is hit, overlays onto the original texture to show the player that damage is being done to the Building. With the decrease of a Building's health, the Dynamic Material becomes more dark and pronounced until the mesh collapses into pieces. Within the Damage function the variable that deals with the Crack Texture's alpha increases and lerp's into the base texture's alpha value. 

<a href="https://ajetty.github.io/ReadMe_Images/DynamicMaterial.png">
<img src="https://ajetty.github.io/ReadMe_Images/DynamicMaterial.png" alt="Dynamic Material Graph" width="70%" >
</a>
<br />    

### Building Targets

<a href="https://ajetty.github.io/ReadMe_Images/M_OutlineTarget.png">
<img src="https://ajetty.github.io/ReadMe_Images/M_OutlineTarget.png" alt="Outline Target Image" width="70%" >
</a>
<br /><br />

These actors are inheriting from the main Building Base class and act in the same way. The main difference is that these buildings have a material that outline's them in orange. This is done by taking the original texture depth/size and expanding it with an offset value by how thick of an outline we want. Then with each texel, adding it's UV screen position with (x+offset, 0), (x-offset, 0), (0, y+offset), (0, y-offset) that will gives us four coordinates that we can compare with the original. Each difference in depth of each left, right, top, bottom result is then masked in the red channel and a min and max of these values are calculated (this is a range of 0 to 1). Once the difference between a min and max is calculated then the difference between the two values is calculated. If the result is 2 then that depth is filled in with an orange color. For a Target Building to have an outline, its Custom Depth Stencil value must be set to the value 2. For other actors to show in front of the outline then their value must be 1. Once a Target Building is destroyed then the value is set to 1 to get rid of the outline.         

## Fruit

<a href="https://ajetty.github.io/ReadMe_Images/RandomWander.gif">
<img src="https://ajetty.github.io/ReadMe_Images/RandomWander.gif" alt="Fruit Random Wander Image" width="320px" >
</a>
<br /><br />

[Github Folder Link for Fruit](https://github.com/ajetty/FruitSalad/tree/main/Source/FruitSalad/Fruit)

[Github Folder Link for Fruit AI](https://github.com/ajetty/FruitSalad/tree/main/Source/FruitSalad/AI)


### Behavior Tree

<a href="https://ajetty.github.io/ReadMe_Images/FruitBehaviorTree.png">
<img src="https://ajetty.github.io/ReadMe_Images/FruitBehaviorTree.png" alt="Fruit Behavior Tree Image" width="70%" >
</a>
<br /><br />

Each NPC has an AI Controller that calls for the Fruit Behavior Tree. This tree has two branches that controls two actions: to run from the player when at a certain distance, to randomly pick a point within a certain radius and navigate there. 

Run From Player is a sequence that runs two EQS Queries: Find Player and Run From Player. Find Player locates the player by using a grid spawned from the NPC's location. If the player is located or queried from the grid then the second EQS Query runs. The Run From Player Query also uses a grid that locates the furthest point from both the player and the buildings. After this query then the resulting position is given to the Blackboard Key, TargetMoveLocation. With TargetMoveLocation set then a Move To task is performed and the NPC location is changed away from the player.

If the Find Player Query fails then another sequence, Random Wander, is performed. First the Behavior Tree task Find Navigable Location, a custom task made in C++, runs. In this task, a random point is chosen from within a circular area's circumference originating from the NPC. This is done with Game World FNavigationSystem's function K2_GetRandomPointInRadius. To check to see if this location doesn't hit any of the buildings, the NPC's a line trace is done from the NPC's location to the resulting random point. If the ray tracing results in a hit then another point is chosen. 

The result is then stored in the Blackboard Key called TargetMoveLocation and the next task in the sequence, Move To, is then performed. With these steps then the NPC wanders throughout the level until the player approaches.       

### Data Assets  

<a href="https://ajetty.github.io/ReadMe_Images/FruitAsset.png">
<img src="https://ajetty.github.io/ReadMe_Images/FruitAsset.png" alt="Fruit Data Asset Image" width="30%" >
</a>  
<br />

<a href="https://ajetty.github.io/ReadMe_Images/FruitUML.png">
<img src="https://ajetty.github.io/ReadMe_Images/FruitUML.png" alt="Fruit Diagram Image" >
</a>
<br /><br />

To be able to switch NPC information in the Character Fruit Base class, Data Assets are used to give the class the information it needs to perform. The C++ class has a UProperty that calls for the asset and assigns the appropriate mesh, damage, max health, and time gain at run time. This allows for a dynamic way of adding more NPCs without changing the foundation of the class itself.

## Game Mode

[Github Folder Link for Fruit Salad Game Mode Base](https://github.com/ajetty/FruitSalad/blob/main/Source/FruitSalad/FruitSaladGameModeBase.cpp)

This is were win and lose conditions are calculated and the end game is processed.

When the game begins, all references of actor class Building Target is collected into an array and then the number of elements is stored into an integer. When a Building Target is destroyed then the Game Mode decreases that integer and once it's equal to zero then a winning condition is handled. The other actors are also taken to account and call on the function ActorDied. If not a Building Target then only time is added to the count down timer.   

 

### Timer

When BeginPlay is called then a TimerDelegate and Handle is created. The delegate is set to a Handle Game Over function while the Handle is set to the minutes and seconds that the UProperty in the blueprint provides. For every tick, the Handle is queried and the main HUD that holds the textblocks that show time are updated. When any of the actor's in the level is destroyed then time is added to the count down timer based on what the TimeGain variable their class or data asset is holding. 


## HUD

[Github Folder Link for HUD](https://github.com/ajetty/FruitSalad/tree/main/Source/FruitSalad/HUD) 

The HUD that shows gameplay is manipulated using a C++ class FruitSaladHUD which inherits from UserWidget. This class has synchronized widget blueprint properties that allows it to change what components are shown on screen. For example, the timer in the top left corner. 

### Title Menu
<a href="https://ajetty.github.io/ReadMe_Images/TitleScreen.gif">
<img src="https://ajetty.github.io/ReadMe_Images/TitleScreen.gif" alt="Title Menu Image" width="320px" >
</a>
<br />

A widget blueprint that holds the title menu. In the event graph, gets the player controller and allows the selection within the button menu. Start Game allows switching from the Menu Level that plays at the start of the game to the level that holds the actual gameplay level. Options switches over to another menu selection system that changes the resolution of the screen. Quit closes the application.   

### Pause Menu

<a href="https://ajetty.github.io/ReadMe_Images/PauseMenu.png">
<img src="https://ajetty.github.io/ReadMe_Images/PauseMenu.png" alt="Pause Menu Image" width="50%" >
</a>
<br />

By clicking the key 'P', a player can go to a pause menu. This freezes gameplay until either the button 'Resume' or 'Quit' is pressed. The logic for the 'P' event is done within the Bulldozer blueprint and uses a reference to the Pause Menu widget blueprint.

<a href="https://ajetty.github.io/ReadMe_Images/Pause.png">
<img src="https://ajetty.github.io/ReadMe_Images/Pause.png" alt="Pause Menu Image" width="70%" >
</a>
<br /><br />   

### Win Screen

<a href="https://ajetty.github.io/ReadMe_Images/WinScreen.png">
<img src="https://ajetty.github.io/ReadMe_Images/WinScreen.png" alt="Win Screen Image" width="50%" >
</a>
<br />

Once all of the Target Buildings are destroyed, the Game Mode calls for this screen to be displayed. 

### Lose Screen

<a href="https://ajetty.github.io/ReadMe_Images/LoseScreen.png">
<img src="https://ajetty.github.io/ReadMe_Images/LoseScreen.png" alt="Lose Screen Image" width="50%" >
</a>
<br />

Once the timer reaches zero, the Game Mode calls for this screen to be displayed. 

