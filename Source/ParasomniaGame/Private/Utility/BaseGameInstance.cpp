// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/BaseGameInstance.h"
#include "Utility/BaseSaveSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/GameInstance.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Actors/BaseChar.h"
#include "Widgets/WBP_LoadScreen.h"
#include "MoviePlayer.h"

void UBaseGameInstance::LoadLevelOne()
{
	BeginLoadingScreen("TheMainMapForGame");
	LoadLevelSafe(LevelOne);
	LevelCurrent = LevelOne;

	SaveGame(SlotString);
}

void UBaseGameInstance::LoadSelectLevel()
{
	LoadLevelSafe(CharSelectLevel);
}

void UBaseGameInstance::LoadLevelSafe(int32 MapIndex)
{
	if (MapIndex >= 0 && MapIndex < LevelArray.Num())
	{
		LevelCurrent = MapIndex;
		UGameplayStatics::OpenLevel(GetWorld(), LevelArray[LevelCurrent] , true);
	}
}

void UBaseGameInstance::Quit()
{
	if (GetWorld() != nullptr && GetWorld()->GetFirstPlayerController() != nullptr)
	{
		GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	}
}

void UBaseGameInstance::LoadMainMenu()
{
	LoadLevelSafe(LevelMainMenu);
}

void UBaseGameInstance::LoadLevelCurrent()
{
	LoadGame(SlotString);
	if (SaveSystem)
	{
		LevelCurrent = SaveSystem->LevelIndex;
		LoadLevelSafe(LevelCurrent);
	}
}

void UBaseGameInstance::RestartLevel()
{

	bQuitThroughPause = false;
	bHintHUD = false;
	EnergyAmountSaved = 0;
	EnergyCellsCollected = 0;
	RationsSaved = 0;
	PeopleSaved = 0;
	SaveGame(SlotString);
}

void UBaseGameInstance::CalculateFinalScore()
{
	int TotalCellPoints = EnergyCellsCollected * CellPointModifier;
	int TotalRationPoints = RationsSaved * RationPointModifier;
	int TotalPeoplePoints = PeopleSaved * PeoplePointModifier;

	FinalScore = TotalCellPoints + TotalRationPoints + TotalPeoplePoints;
}

void UBaseGameInstance::SaveGame(FString SlotName, bool Setting)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		UGameplayStatics::DeleteGameInSlot(SlotName, 0);
	}

	SaveSystem = Cast<UBaseSaveSystem>(UGameplayStatics::CreateSaveGameObject(UBaseSaveSystem::StaticClass()));
	
	SaveSystem->LevelIndex = LevelCurrent;
	SaveSystem->CharMaterial = CharacterMaterial;
	SaveSystem->bIsNightmare = bIsNightmare;
	SaveSystem->bQuitThroughPause = bQuitThroughPause;
	SaveSystem->EnergyAmountSaved = EnergyAmountSaved;
	SaveSystem->EnergyCellsCollected = EnergyCellsCollected;
	SaveSystem->RationsSaved = RationsSaved;
	SaveSystem->PeopleSaved = PeopleSaved;
	SaveSystem->Minutes = Minutes;
	SaveSystem->Seconds = Seconds;
	SaveSystem->WindowType = WindowType;
	SaveSystem->bToggleCrouch = bIsCrouchChecked;
	SaveSystem->bToggleSprint = bIsSprintChecked;
	SaveSystem->FinalScore = FinalScore;

	UGameplayStatics::SaveGameToSlot(SaveSystem, SlotName, 0);
}

void UBaseGameInstance::LoadGame(FString SlotName, bool Setting)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		SaveSystem = Cast<UBaseSaveSystem>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

		LevelCurrent = SaveSystem->LevelIndex;
		CharacterMaterial = SaveSystem->CharMaterial;
		bIsNightmare = SaveSystem->bIsNightmare;
		bQuitThroughPause = SaveSystem->bQuitThroughPause;
		EnergyAmountSaved = SaveSystem->EnergyAmountSaved;
		EnergyCellsCollected = SaveSystem->EnergyCellsCollected;
		RationsSaved = SaveSystem->RationsSaved;
		PeopleSaved = SaveSystem->PeopleSaved;
		Minutes = SaveSystem->Minutes;
		Seconds = SaveSystem->Seconds;
		WindowType = SaveSystem->WindowType;
		bIsCrouchChecked = SaveSystem->bToggleCrouch;
		bIsSprintChecked = SaveSystem->bToggleSprint;
		FinalScore = SaveSystem->FinalScore;
	}
}

void UBaseGameInstance::Init()
{
	Super::Init();
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UBaseGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UBaseGameInstance::EndLoadingScreen);
}

void UBaseGameInstance::BeginLoadingScreen(const FString& MapName)
{
	if (!IsRunningDedicatedServer())
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;

		LoadingHUD = CreateWidget<UWBP_LoadScreen>(GetWorld(), LoadingClass);
		LoadingScreen.WidgetLoadingScreen = LoadingHUD->TakeWidget();

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

void UBaseGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{

}
