// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "Misc/CoreDelegates.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "BaseFighterGameMode.h"

UBaseGameInstance::UBaseGameInstance() {
	SearchForSessionsCompletedDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UBaseGameInstance::SearchForSessionsCompleted);
}



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
				//GEnigine->AddOnScreenDebugMessage(0, 30.0f, FColor::Cyan, FString::Printf(TEXT("A session has been created!")));
				UE_LOG(LogTemp, Warning, TEXT("A session has been created!"));
			}
			else {
				//GEnigine->AddOnScreenDebugMessage(0, 30.0f, FColor::Cyan, FString::Printf(TEXT("A session has failed to be created!")));
				UE_LOG(LogTemp, Warning, TEXT("A session has failed to be created!"));
			}
		}
	}
}

void UBaseGameInstance::SearchForSessions() {
	if (IOnlineSubsystem* onlineSubsystem = IOnlineSubsystem::Get()) {
		if (IOnlineSessionPtr onlineSessionInterface = onlineSubsystem->GetSessionInterface()) {
			SearchForSessionsCompletedHandle = onlineSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(SearchForSessionsCompletedDelegate);

			searchSettings = MakeShareable(new FOnlineSessionSearch());
			searchSettings->bIsLanQuery = false;
			searchSettings->MaxSearchResults = 5;
			searchSettings->PingBucketSize = 30;
			searchSettings->TimeoutInSeconds = 10.0f;

			const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			if (onlineSessionInterface->FindSessions(*localPlayer->GetPreferredUniqueNetId(), searchSettings.ToSharedRef())) {
				UE_LOG(LogTemp, Warning, TEXT("Search started."));
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Search failed to start."));
			}
		}
	}
}

void UBaseGameInstance::SearchForSessionsCompleted(bool _searchCompleted) {
	if (IOnlineSubsystem* onlineSubsystem = IOnlineSubsystem::Get()) {
		if (IOnlineSessionPtr onlineSessionInterface = onlineSubsystem->GetSessionInterface()) {
			onlineSessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(SearchForSessionsCompletedHandle);
			
			UE_LOG(LogTemp, Warning, TEXT("Search found  sessions after completing search."), searchSettings->SearchResults.Num());

			if (auto gameMode = Cast<A)
		}
	}
}