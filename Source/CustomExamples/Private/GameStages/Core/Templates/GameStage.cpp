// 6r0m, MIT liscence


#include "GameStages/Core/Templates/GameStage.h"

void UGameStage::FinishStage()
{
	OnStageFinished.ExecuteIfBound();

	// if this stage no needed anymore - to force GC use ConditionalBeginDestroy() on this
}
