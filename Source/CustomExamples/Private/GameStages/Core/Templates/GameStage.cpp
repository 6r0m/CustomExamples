// 6r0m, MIT liscence


#include "GameStages/Core/Templates/GameStage.h"

void UGameStage::FinishStage()
{
	OnStageFinished.ExecuteIfBound();
}
