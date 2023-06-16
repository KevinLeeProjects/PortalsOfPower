// Player movement and camera code are from ThirdPerson template from Epic Games. Everything else is my code


#include "Player_PlayerCharacter.h"

#include "GlobalVariables.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "GameplayTagsManager.h"
#include "GameplayTagsModule.h"
#include "GameplayTagContainer.h"
#include "Kismet/KismetSystemLibrary.h"

// Include the necessary headers
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

// Define your custom message struct
struct FMyMessage
{
	FString Data;
	int32 Value;
};

// Sets default values
APlayer_PlayerCharacter::APlayer_PlayerCharacter()
{
 	// Set size for collision capsule
	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 250.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	FName playerTag = FName(TEXT("Player"));
	Tags.AddUnique(playerTag);

	FName playerNameTag = FName(GlobalVariables().GetInstance().GetUsername());
	Tags.AddUnique(playerNameTag);

	FString port = GlobalVariables().GetInstance().GetServerPort();
	int32 portInt = FCString::Atoi(*port);
	SendDataToServer(GlobalVariables().GetInstance().GetServerIP(), portInt);
}

// Function to send data from client to server
void APlayer_PlayerCharacter::SendDataToServer(const FString & ServerIP, int32 ServerPort)
{
	ServerPort = 59091;
	UE_LOG(LogTemp, Warning, TEXT("SERVR: %s"), *ServerIP);
	// Create a socket
	FSocket* Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	// Connect to the server
	FIPv4Address ServerAddress;
	FIPv4Address::Parse(ServerIP, ServerAddress);
	TSharedRef<FInternetAddr> ServerAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	ServerAddr->SetIp(ServerAddress.Value);
	ServerAddr->SetPort(ServerPort);
	UE_LOG(LogTemp, Warning, TEXT("SERVER: %s"), *ServerAddr->ToString(true));

	if (Socket->Connect(*ServerAddr))
	{
		UE_LOG(LogTemp, Warning, TEXT("SERVR2"));
		// Create your message
		FMyMessage MyMessage;
		MyMessage.Data = "Hello Server!";
		MyMessage.Value = 42;

		// Serialize the message
		FString SerializedMessage = FString::Printf(TEXT("%s,%d"), *MyMessage.Data, MyMessage.Value);

		// Convert the serialized message to a byte array
		TArray<uint8> MessageData;
		FTCHARToUTF8 ConvertedMessage(*SerializedMessage);
		MessageData.Append((uint8*)ConvertedMessage.Get(), ConvertedMessage.Length());

		// Send the data to the server
		int32 BytesSent = 0;
		bool bSuccess = Socket->Send(MessageData.GetData(), MessageData.Num(), BytesSent);

		if (bSuccess)
		{
			UE_LOG(LogTemp, Warning, TEXT("Data sent to server!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to send data to server!"));
		}
	}

	// Clean up the socket
	Socket->Close();
	delete Socket;
}

// Called when the game starts or when spawned
void APlayer_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlayer_PlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayer_PlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayer_PlayerCharacter::Look);

	}

}

void APlayer_PlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayer_PlayerCharacter::Look(const FInputActionValue& Value)
{
	// Get the mouse movement
	float DeltaX, DeltaY;
	GetWorld()->GetFirstPlayerController()->GetInputMouseDelta(DeltaX, DeltaY);

	// Calculate the rotation rate
	float RotationRate = 0.25f;

	// Add the rotation input to the controller
	AddControllerYawInput(DeltaX * RotationRate);
	AddControllerPitchInput(-DeltaY * RotationRate);

	// Rotate the SpringArm to match the character's rotation
	USpringArmComponent* SpringArm = FindComponentByClass<USpringArmComponent>();
	// Calculate the desired rotation of the SpringArm
	FRotator DesiredRotation = GetControlRotation() - GetActorRotation();
	// Get the camera rotation
	FRotator CameraRotation = CameraBoom->GetComponentRotation();
	CameraRotation.Pitch = 0.0f;
	CameraRotation.Roll = 0.0f;

	// Set the actor rotation
	SetActorRotation(CameraRotation);
	// Apply the restricted rotation to the SpringArm
	SpringArm->SetRelativeRotation(DesiredRotation);

}

