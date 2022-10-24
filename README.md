# CustomExamples
 6r0m's custom examples for Unreal Engine.


## GameStages
Example logic for the manipulation of multiple game stages.

GameStageManager has an array of GameStages, each of them connected with a StageActor and StandInfo.
The StageActor can be **any** with the StageActorInterface, he receives an activation phase from GameStage and requests finish. 
The StandInfo serves for the demonstration of a stage hint system.