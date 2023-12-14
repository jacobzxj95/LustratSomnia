// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/OptionsMenu.h"
#include "Widgets/WBP_ButtonsNText.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/BaseGameInstance.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Widgets/WBP_MainMenu.h"
#include "GenericPlatform/GenericWindow.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/IntPoint.h"
#include "GameFramework/GameUserSettings.h"
#include <string>
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetTextLibrary.h"
#include "Widgets/SettingsMenu.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/RichTextBlock.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"

void UOptionsMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());
}

void UOptionsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	SecretArray.Add(WindowModeText);
	SecretArray.Add(ScreenResolutionText); 
	SecretArray.Add(GraphicsText); 
	SecretArray.Add(VSyncText);

	BackButton->OnClicked.AddDynamic(this, &UOptionsMenu::OnClickedBack);

	windowmodeM->OnClicked.AddDynamic(this, &UOptionsMenu::OnClickedWindowModeM);
	windowmodeM->BackgroundButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredWindowModeM);
	windowmodeP->OnClicked.AddDynamic(this, &UOptionsMenu::OnClickedWindowModeP);
	windowmodeP->BackgroundButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredWindowModeP);

	screenresolutionM->OnClicked.AddDynamic(this, &UOptionsMenu::OnClickedScreenResolutionM);
	screenresolutionM->BackgroundButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredScreenResolutionM);
	screenresolutionP->OnClicked.AddDynamic(this, &UOptionsMenu::OnClickedScreenResolutionP);
	screenresolutionP->BackgroundButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredScreenResolutionP);

	graphicsM->OnClicked.AddDynamic(this, &UOptionsMenu::OnClickedGraphicsM);
	graphicsM->BackgroundButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredGraphicsM);
	graphicsP->OnClicked.AddDynamic(this, &UOptionsMenu::OnClickedGraphicsP);
	graphicsP->BackgroundButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredGraphicsP);

	vsyncM->OnClicked.AddDynamic(this, &UOptionsMenu::OnClickedVSyncM);
	vsyncM->BackgroundButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredVSyncM);
	vsyncP->OnClicked.AddDynamic(this, &UOptionsMenu::OnClickedVSyncP);
	vsyncP->BackgroundButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredVSyncP);

	ApplyButton->OnClicked.AddDynamic(this, &UOptionsMenu::OnClickedApply);

	settings = UGameUserSettings::GetGameUserSettings();
	settings->LoadSettings();

	graphicsIndex = settings->GetOverallScalabilityLevel();
	bIsVsync = settings->IsVSyncEnabled();
	resolution = settings->GetScreenResolution();
	if (resolution.X == 1280)
	{
		resolutionIndex = 0;
	}
	else if (resolution.X == 1600)
	{
		resolutionIndex = 1;
	}
	else if (resolution.X == 1920)
	{
		resolutionIndex = 2;
	}
	else if (resolution.X == 2560)
	{
		resolutionIndex = 3;
	}
	else if (resolution.X == 3840)
	{
		resolutionIndex = 4;
	}

	for (UWidget* boxes : VidOptBox->GetAllChildren())
	{
		FVideoOptions videoOptions;

		UHorizontalBox* box = Cast<UHorizontalBox>(boxes);
		if (box)
		{
			for (UWidget* variables : box->GetAllChildren())
			{
				UTextBlock* text = Cast<UTextBlock>(variables);
				UWBP_ButtonsNText* button = Cast<UWBP_ButtonsNText>(variables);
				if (text)
				{
					for (UTextBlock* secret : SecretArray)
					{
						if (text == secret)
						{
							videoOptions.VidOptName = text;
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("All good"));
						}
					}
				}
				else if (button)
				{
					videoOptions.ChoiceInputs.Add(button);
				}
			}
			VidOptArray.Add(videoOptions);
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(VidOptArray.Num()));

	VidOptIndex = 0;
	VidOptArray[VidOptIndex].ChoiceIndex = 0;

	UpdateButtonStates();

	if (!HasAnyUserFocus())
	{
		SetFocus();
	}
}

void UOptionsMenu::OnClickedWindowModeM_Implementation()
{
	//
	// int32 windowmodeNum;
	//windowmodeNum = UKismetMathLibrary::Conv_ByteToInt(windowmodeType);
	//windowmodeNum = FMath::Clamp(windowmodeNum - 1, 0, 2);
	/*windowmodeType = (EWindowMode)UKismetMathLibrary::Conv_IntToByte(windowmodeNum);*/
}

void UOptionsMenu::OnHoveredWindowModeM()
{
	VidOptIndex = 0;
	VidOptArray[VidOptIndex].ChoiceIndex = 0;
	UpdateButtonStates();
}

void UOptionsMenu::OnClickedWindowModeP_Implementation()
{
	//int32 windowmodeNum;
	//windowmodeNum = UKismetMathLibrary::Conv_ByteToInt(EWindowMode::Type);
	//windowmodeNum = UKismetMathLibrary::Conv_ByteToInt(windowmodeType);
	//windowmodeNum = FMath::Clamp(windowmodeNum + 1, 0, 2);
	/*windowmodeType = (EWindowMode)UKismetMathLibrary::Conv_IntToByte(windowmodeNum);*/
}

void UOptionsMenu::OnHoveredWindowModeP()
{
	VidOptIndex = 0;
	VidOptArray[VidOptIndex].ChoiceIndex = 1;
	UpdateButtonStates();
}

//FText UOptionsMenu::GetScreenResolutionText()
//{
//
//}

void UOptionsMenu::OnClickedScreenResolutionM()
{
	resolutionIndex = FMath::Clamp(resolutionIndex - 1, 0, 4);
	switch (resolutionIndex)
	{
		case 0:
			resolution.X = 1280;
			resolution.Y = 720;
			break;

		case 1:
			resolution.X = 1600;
			resolution.Y = 900;
			break;

		case 2:
			resolution.X = 1920;
			resolution.Y = 1080;
			break;

		case 3:
			resolution.X = 2560;
			resolution.Y = 1440;
			break;

		case 4:
			resolution.X = 3840;
			resolution.Y = 2160;
			break;

		//default:
		//	resolution.X = 1920;
		//	resolution.Y = 1080;
		//	break;
	}
}

void UOptionsMenu::OnHoveredScreenResolutionM()
{
	VidOptIndex = 1;
	VidOptArray[VidOptIndex].ChoiceIndex = 0;
	UpdateButtonStates();
}

void UOptionsMenu::OnClickedScreenResolutionP()
{
	resolutionIndex = FMath::Clamp(resolutionIndex + 1, 0, 4);
	switch (resolutionIndex)
	{
	case 0:
		resolution.X = 1280;
		resolution.Y = 720;
		break;

	case 1:
		resolution.X = 1600;
		resolution.Y = 900;
		break;

	case 2:
		resolution.X = 1920;
		resolution.Y = 1080;
		break;

	case 3:
		resolution.X = 2560;
		resolution.Y = 1440;
		break;

	case 4:
		resolution.X = 3840;
		resolution.Y = 2160;
		break;
	}
}

void UOptionsMenu::OnHoveredScreenResolutionP()
{
	VidOptIndex = 1;
	VidOptArray[VidOptIndex].ChoiceIndex = 1;
	UpdateButtonStates();
}

void UOptionsMenu::OnClickedGraphicsM()
{
	graphicsIndex = FMath::Clamp(graphicsIndex - 1, 0, 4);
}

void UOptionsMenu::OnHoveredGraphicsM()
{
	VidOptIndex = 2;
	VidOptArray[VidOptIndex].ChoiceIndex = 0;
	UpdateButtonStates();
}

void UOptionsMenu::OnClickedGraphicsP()
{
	graphicsIndex = FMath::Clamp(graphicsIndex + 1, 0, 4);
}

void UOptionsMenu::OnHoveredGraphicsP()
{
	VidOptIndex = 2;
	VidOptArray[VidOptIndex].ChoiceIndex = 1;
	UpdateButtonStates();
}

void UOptionsMenu::OnClickedVSyncM()
{
	bIsVsync = false;
}

void UOptionsMenu::OnHoveredVSyncM()
{
	VidOptIndex = 3;
	VidOptArray[VidOptIndex].ChoiceIndex = 0;
	UpdateButtonStates();
}

void UOptionsMenu::OnClickedVSyncP()
{
	bIsVsync = true;
}

void UOptionsMenu::OnHoveredVSyncP()
{
	VidOptIndex = 3;
	VidOptArray[VidOptIndex].ChoiceIndex = 1;
	UpdateButtonStates();
}

void UOptionsMenu::OnClickedApply_Implementation()
{
	//TObjectPtr<class UGameUserSettings> settings;
	settings = UGameUserSettings::GetGameUserSettings();
	//settings->SetFullscreenMode(windowmodeType);
	settings->SetOverallScalabilityLevel(graphicsIndex);
	settings->SetVSyncEnabled(bIsVsync);
	settings->SetScreenResolution(resolution);
	settings->ApplySettings(true);
}

void UOptionsMenu::OnClickedBack()
{
	RemoveFromParent();
	SettingsHUD = CreateWidget<USettingsMenu>(GetWorld(), SettingsClass);
	SettingsHUD->AddToViewport();
}

void UOptionsMenu::UpdateButtonStates()
{
	for (int i = 0; i < VidOptArray.Num(); i++)
	{
		if (i == VidOptIndex)
		{
			FText temp = VidOptArray[i].VidOptName->GetText();
			FString temp2 = temp.ToString();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, VidOptArray[i].VidOptName->GetText().ToString());
			VidOptArray[i].VidOptName->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));

			for (int j = 0; j < VidOptArray[i].ChoiceInputs.Num(); j++)
			{
				if (j == VidOptArray[i].ChoiceIndex)
				{
					VidOptArray[i].ChoiceInputs[j]->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
				}
				else
				{
					VidOptArray[i].ChoiceInputs[j]->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}

		}
		else
		{
			VidOptArray[i].VidOptName->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
			VidOptArray[i].ChoiceInputs[0]->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
			VidOptArray[i].ChoiceInputs[1]->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

void UOptionsMenu::MoveThroughOptionsDown()
{
	if (VidOptIndex < VidOptArray.Num() - 1)
	{
		int choicebox = VidOptArray[VidOptIndex].ChoiceIndex;
		VidOptIndex++;
		VidOptArray[VidOptIndex].ChoiceIndex = choicebox;
	}
	else
	{
		int choicebox = VidOptArray[VidOptIndex].ChoiceIndex;
		VidOptIndex = 0;
		VidOptArray[VidOptIndex].ChoiceIndex = choicebox;
	}
	UpdateButtonStates();
}

void UOptionsMenu::MoveThroughOptionsUp()
{
	if (VidOptIndex > 0)
	{
		int choicebox = VidOptArray[VidOptIndex].ChoiceIndex;
		VidOptIndex--;
		VidOptArray[VidOptIndex].ChoiceIndex = choicebox;
	}
	else
	{
		int choicebox = VidOptArray[VidOptIndex].ChoiceIndex;
		VidOptIndex = VidOptArray.Num() - 1;
		VidOptArray[VidOptIndex].ChoiceIndex = choicebox;
	}
	UpdateButtonStates();
}

void UOptionsMenu::MoveThroughChoicesRight()
{
	if (VidOptArray[VidOptIndex].ChoiceIndex < VidOptArray[VidOptIndex].ChoiceInputs.Num() - 1)
	{
		VidOptArray[VidOptIndex].ChoiceIndex++;
	}
	else
	{
		VidOptArray[VidOptIndex].ChoiceIndex = 0;
	}
	UpdateButtonStates();
}

void UOptionsMenu::MoveThroughChoicesLeft()
{
	if (VidOptArray[VidOptIndex].ChoiceIndex > 0)
	{
		VidOptArray[VidOptIndex].ChoiceIndex--;
	}
	else
	{
		VidOptArray[VidOptIndex].ChoiceIndex = VidOptArray[VidOptIndex].ChoiceInputs.Num() - 1;
	}
	UpdateButtonStates();
}

void UOptionsMenu::OnChoice()
{
	switch (VidOptIndex)
	{
	case 0:
	{
		switch (VidOptArray[VidOptIndex].ChoiceIndex)
		{
		case 0:
		{
			OnClickedWindowModeM();
			break;
		}
		case 1:
		{
			OnClickedWindowModeP();
			break;
		}
		}
		break;
	}
	case 1:
	{
		switch (VidOptArray[VidOptIndex].ChoiceIndex)
		{
		case 0:
		{
			OnClickedScreenResolutionM();
			break;
		}
		case 1:
		{
			OnClickedScreenResolutionP();
			break;
		}
		}
		break;
	}
	case 2:
	{
		switch (VidOptArray[VidOptIndex].ChoiceIndex)
		{
		case 0:
		{
			OnClickedGraphicsM();
			break;
		}
		case 1:
		{
			OnClickedGraphicsP();
			break;
		}
		}
		break;
	}
	case 3:
	{
		switch (VidOptArray[VidOptIndex].ChoiceIndex)
		{
		case 0:
		{
			OnClickedVSyncM();
			break;
		}
		case 1:
		{
			OnClickedVSyncP();
			break;
		}
		}
		break;
	}
	}
}
