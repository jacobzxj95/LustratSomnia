// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WBP_ButtonsNText.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UWBP_ButtonsNText::NativeConstruct()
{
	Super::NativeConstruct();
	ButtonText->SetText(Info);
	BackgroundButton->OnClicked.AddDynamic(this, &UWBP_ButtonsNText::OnClickedBackground);
}

void UWBP_ButtonsNText::OnClickedBackground()
{
	OnClicked.Broadcast();
}

#if WITH_EDITOR
void UWBP_ButtonsNText::OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs)
{
	Super::OnDesignerChanged(EventArgs);
	if (ButtonText)
	{
		ButtonText->SetText(Info);
	}
}
#endif