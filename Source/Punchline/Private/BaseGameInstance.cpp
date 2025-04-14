// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

void UBaseGameInstance::HostSession() {
	if (IOnlineSubsystem* onlineSubsystem = IOnlineSubsystem::Get()) {
		if (IOnlineSessionPtr onlineSessionInterface = onlineSubsystem->GetSessionInterface()) {
			TSharedPtr<FOnlineSessionSettings> sessionSettings = MakeShareable(new FOnlineSessionSettings());
			sessionSettings->bAllowInvites = true;
			sessionSettings->bAllowJoinInProgress = false;
			sessionSettings->bAllowJoinViaPresence = true;
			sessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
			sessionSettings->bIsDedicated = false;
			sessionSettings->bUsesPresence = true;
			sessionSettings->bIsLANMatch = false;
			sessionSettings->bShouldAdvertise = true;
			sessionSettings->NumPrivateConnections = 0;
			sessionSettings->NumPublicConnections = 2;


			const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			if (onlineSessionInterface->CreateSession(*localPlayer->GetPreferredUniqueNetId(), FName("Test Game Session"), *sessionSettings)) { //Switch name to NAME_GameSession or make customizable by player
				UE_LOG(LogTemp, Warning, TEXT("A session has been created!"));
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("A session has failed to be created!"));
			}
		}
	}
}