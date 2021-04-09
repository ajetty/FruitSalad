// Fill out your copyright notice in the Description page of Project Settings.


#include "FruitSaladHUD.h"

#include <string>

// void UFruitSaladHUD::NativeConstruct()
// {
// 	Super::NativeConstruct();
//
// 	if(TextBlock_TEST)
// 	{	
// 		TextBlock_TEST->SetText(FText::FromString("Fuck you HAHAHAHAH!"));
// 	}
// }

void UFruitSaladHUD::SynchronizeProperties()
{
	//TextBlock_TEST->SetText(FText::FromString("HERE IS ANOTHER TEST WAH!"));

	//MinutesTimeText = 999.0f;
	//SecondsTimeText = 99.0f;

	TextBlock_Minutes->SetText(FText::AsNumber(MinutesTimeText));
	TextBlock_Seconds->SetText(FText::AsNumber(SecondsTimeText));
}

void UFruitSaladHUD::UpdateTimeTextBlock(UTextBlock* MinutesTextRef, UTextBlock* SecondsTextRef, int32 Minutes, int32 Seconds)
{
	FString MinString = FString::Printf( TEXT( "%02d" ), Minutes);
	FString SecString = FString::Printf( TEXT( "%02d" ), Seconds);

	SecondsTextRef->SetText(FText::FromString(SecString));
	MinutesTextRef->SetText(FText::FromString(MinString));
	
}

