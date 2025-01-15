// Copyright 2025 Enguerran COBERT. all right reserved.

#pragma once

//--------------------------------- LOG FUNC ---------------------------------//
/*
* Current Class where this is called
*/
#define CURRENT_CLASS (FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))))

/*
*  Current Function Name where this is called
*/
#define CURRENT_FUNC (FString(__FUNCTION__).Right(FString(__FUNCTION__).Len() - FString(__FUNCTION__).Find(TEXT("::")) - 2))

/*
* Current Line Number in the code where this is called
* Could be weird as this state especially on 'if/else' check, if you use it on else it will outlog the line on else not the if condition
*/
#define CURRENT_LINE  (TEXT("Line") + FString::FromInt(__LINE__))

//--------------------------------- LOG ---------------------------------//
#define SH_ERROR_CAT(Category, Format,...) UE_LOG(Category,Error,Format,__VA_ARGS__)
#define SH_WARNING_CAT(Category,Format,...) UE_LOG(Category,Warning,Format,__VA_ARGS__)
#define SH_LOG_CAT(Category,Format,...) UE_LOG(Category,Log,Format,__VA_ARGS__)

//--------------------------------- LOG SCREEN ---------------------------------//
#define SH_LOG_SCREEN(Key, DisplayTime, Color, Format, ...) if(GEngine){\
GEngine->AddOnScreenDebugMessage(Key, DisplayTime, Color, FString::Printf(Format, __VA_ARGS__));\
}

#define SH_LOG_SCREEN_SIMPLE(Format, ...) SH_LOG_SCREEN(-1, 10.0f, FColor::Red, Format, __VA_ARGS__)
