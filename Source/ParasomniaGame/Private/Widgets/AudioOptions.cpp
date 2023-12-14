// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/AudioOptions.h"
#include "Widgets/SettingsMenu.h"
#include "Widgets/WBP_ButtonsNText.h"
#include "Utility/BaseGameInstance.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"

void UAudioOptions::NativePreConstruct()
{
	Super::NativePreConstruct();
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());
}

void UAudioOptions::NativeConstruct()
{
	Super::NativeConstruct();

	ToggleAll->OnClicked.AddDynamic(this, &UAudioOptions::OnClickedToggleAll);
	ToggleAll->BackgroundButton->OnHovered.AddDynamic(this, &UAudioOptions::OnHoveredToggleAll);
	MasterSlider->OnValueChanged.AddDynamic(this, &UAudioOptions::OnChangedMasterVolume);

	ToggleMusic->OnClicked.AddDynamic(this, &UAudioOptions::OnClickedToggleMusic);
	ToggleMusic->BackgroundButton->OnHovered.AddDynamic(this, &UAudioOptions::OnHoveredToggleMusic);

	ToggleSFX->OnClicked.AddDynamic(this, &UAudioOptions::OnClickedToggleSFX);
	ToggleSFX->BackgroundButton->OnHovered.AddDynamic(this, &UAudioOptions::OnHoveredToggleSFX);

	ToggleVoice->OnClicked.AddDynamic(this, &UAudioOptions::OnClickedToggleVoice);
	ToggleVoice->BackgroundButton->OnHovered.AddDynamic(this, &UAudioOptions::OnHoveredToggleVoice);

	BackButton->OnClicked.AddDynamic(this, &UAudioOptions::OnClickedBack);

	for (UWidget* child : AudioOptBox->GetAllChildren())
	{
		FAudioOpts audioOpts;

		if (child->IsA<UHorizontalBox>())
		{
			UHorizontalBox* hBox = Cast<UHorizontalBox>(child);

			for (UWidget* secondChild : hBox->GetAllChildren())
			{
				if (secondChild->IsA<USlider>())
				{
					audioOpts.AudioOptSlider = Cast<USlider>(secondChild);
				}
				else if (secondChild->IsA<UWBP_ButtonsNText>()) 
				{
					audioOpts.AudioOptButton = Cast<UWBP_ButtonsNText>(secondChild);
				}
			}
			AudioOpts.Add(audioOpts);
		}
	}
	AudioOptIndex = 0;
	UpdateButtonState();

	if (!HasAnyUserFocus())
	{
		SetFocus();
	}
}

void UAudioOptions::OnClickedToggleAll_Implementation()
{

}

void UAudioOptions::OnHoveredToggleAll()
{
	AudioOptIndex = 0;
	UpdateButtonState();
}

void UAudioOptions::OnChangedMasterVolume_Implementation(float Value)
{

}

void UAudioOptions::OnClickedToggleMusic_Implementation()
{

}

void UAudioOptions::OnHoveredToggleMusic()
{
	AudioOptIndex = 1;
	UpdateButtonState();
}

void UAudioOptions::OnChangedMusicVolume_Implementation(float Value)
{
}

void UAudioOptions::OnClickedToggleSFX_Implementation()
{

}

void UAudioOptions::OnHoveredToggleSFX()
{
	AudioOptIndex = 2;
	UpdateButtonState();
}

void UAudioOptions::OnChangedSFXVolume_Implementation(float Value)
{
}

void UAudioOptions::OnClickedToggleVoice_Implementation()
{

}

void UAudioOptions::OnChangedVoiceVolume_Implementation(float Value)
{

}

void UAudioOptions::OnHoveredToggleVoice()
{
	AudioOptIndex = 3;
	UpdateButtonState();
}

void UAudioOptions::OnClickedBack()
{
	RemoveFromParent();
	SettingsHUD = CreateWidget<USettingsMenu>(GetWorld(), SettingsClass);
	SettingsHUD->AddToViewport();
}

void UAudioOptions::SetAudioLevel_Implementation(float Value)
{
	switch (AudioOptIndex)
	{
	case 0:
	{
		float NewValue = MasterSlider->GetValue() + Value;
		NewValue = FMath::Clamp(NewValue, 0.0f, 1.0f);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("NewValue: %f"), NewValue));
		if (NewValue >= 0.0f && NewValue <= 1.0f)
		{
			MasterSlider->SetValue(NewValue);
		}
		break;
	}

	case 1:
	{
		float NewValue = MusicSlider->GetValue() + Value;
		NewValue = FMath::Clamp(NewValue, 0.0f, 1.0f);
		if (NewValue >= 0.0f && NewValue <= 1.0f)
		{
			MusicSlider->SetValue(NewValue);
		}
		break;
	}

	case 2:
	{
		float NewValue = SFXSlider->GetValue() + Value;
		NewValue = FMath::Clamp(NewValue, 0.0f, 1.0f);
		if (NewValue >= 0.0f && NewValue <= 1.0f)
		{
			SFXSlider->SetValue(NewValue);
		}
		break;
	}

	case 3:
	{
		float NewValue = VoiceSlider->GetValue() + Value;
		NewValue = FMath::Clamp(NewValue, 0.0f, 1.0f);
		if (NewValue >= 0.0f && NewValue <= 1.0f)
		{
			VoiceSlider->SetValue(NewValue);
		}
		break;
	}

	}
}

void UAudioOptions::MoveDownArray()
{
	if (AudioOptIndex < AudioOpts.Num() - 1)
	{
		AudioOptIndex++;
	}
	else
	{
		AudioOptIndex = 0;
	}
	UpdateButtonState();
}

void UAudioOptions::MoveUpArray()
{
	if (AudioOptIndex > 0)
	{
		AudioOptIndex--;
	}
	else
	{
		AudioOptIndex = AudioOpts.Num() - 1;
	}
	UpdateButtonState();
}

void UAudioOptions::UpdateButtonState()
{
	for (int i = 0; i < AudioOpts.Num(); i++)
	{
		if (i == AudioOptIndex)
		{
			AudioOpts[i].AudioOptButton->BackgroundButton->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{
			AudioOpts[i].AudioOptButton->BackgroundButton->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}
