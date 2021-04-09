// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "FruitSaladHUD.generated.h"

class UTextBlock;
UCLASS()
class FRUITSALAD_API UFruitSaladHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Panel")
	int32 MinutesTimeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Panel")
	int32 SecondsTimeText;
	
	UPROPERTY(BlueprintReadOnly, meta= (BindWidget))
	UTextBlock* TextBlock_TEST = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TextBlock_Minutes = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TextBlock_Seconds = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Update Time")
	static void UpdateTimeTextBlock(UTextBlock* MinutesTextRef, UTextBlock* SecondsTextRef, int32 Minutes, int32 Seconds);

};

