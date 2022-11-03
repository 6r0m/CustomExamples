# CustomExamples
 6r0m's custom examples for Unreal Engine.


## GameStages
Example logic for the manipulation of multiple game stages.

GameStageManager has an array of GameStages, each of them connected with a StageActor and StandInfo.
The StageActor can be **any** with the StageActorInterface, he receives an activation phase from GameStage and requests finish. 
The StandInfo serves for the demonstration of a stage hint system.


## Manipulator
The robot arm is carrying the package to a target point.

Playtest on the map: \Manipulator\Maps\Manipulator

On the scene, there are configurables: 
- package as a AActor;
- target position at the BP_RoboManipulator;
